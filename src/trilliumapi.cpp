#include "trilliumapi.h"
#include <QDebug>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

TrilliumApi::TrilliumApi(SettingsManager *settings, QObject *parent)
    : QObject(parent)
    , m_settings(settings)
    , m_nam(new QNetworkAccessManager(this))
    , m_busy(false)
{
}

bool TrilliumApi::busy() const
{
    return m_busy;
}

void TrilliumApi::setBusy(bool busy)
{
    if (m_busy != busy) {
        m_busy = busy;
        emit busyChanged();
    }
}

QNetworkRequest TrilliumApi::createRequest(const QString &endpoint, const QString &overrideUrl, const QString &overrideToken)
{
    QString baseUrl = overrideUrl.isEmpty() ? m_settings->serverUrl() : overrideUrl;
    QString token = overrideToken.isEmpty() ? m_settings->apiToken() : overrideToken;

    if (!baseUrl.endsWith(QStringLiteral("/"))) {
        baseUrl += QStringLiteral("/");
    }

    QUrl url(baseUrl + endpoint);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    
    if (!token.isEmpty()) {
        request.setRawHeader("Authorization", token.toUtf8());
    }

    return request;
}

void TrilliumApi::testConnection(const QString &url, const QString &password, const QString &token)
{
    setBusy(true);

    if (!password.isEmpty()) {
        QNetworkRequest req = createRequest(QStringLiteral("etapi/auth/login"), url, QString());
        QJsonObject body;
        body.insert(QStringLiteral("password"), password);
        QByteArray payload = QJsonDocument(body).toJson();

        QNetworkReply *reply = m_nam->post(req, payload);
        connect(reply, &QNetworkReply::finished, this, [this, url, reply]() {
            int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            QByteArray data = reply->readAll();
            reply->deleteLater();

            if (reply->error() == QNetworkReply::NoError) {
                QJsonDocument doc = QJsonDocument::fromJson(data);
                QString authToken = doc.object().value(QStringLiteral("authToken")).toString();
                if (!authToken.isEmpty()) {
                    // Double check by requesting app info using the obtained token
                    QNetworkRequest infoReq = createRequest(QStringLiteral("etapi/app-info"), url, authToken);
                    QNetworkReply *infoReply = m_nam->get(infoReq);
                    connect(infoReply, &QNetworkReply::finished, this, [this, url, authToken, infoReply]() {
                        infoReply->deleteLater();
                        setBusy(false);

                        if (infoReply->error() == QNetworkReply::NoError) {
                            m_settings->setServerUrl(url);
                            m_settings->setApiToken(authToken);
                            emit connectionTested(true, QString());
                        } else {
                            emit connectionTested(false, tr("App-info verification failed: %1").arg(infoReply->errorString()));
                        }
                    });
                } else {
                    setBusy(false);
                    emit connectionTested(false, tr("Response did not contain authToken"));
                }
            } else {
                setBusy(false);
                QString errorMsg = reply->errorString();
                if (httpStatus == 401) {
                    errorMsg = tr("Unauthorized: Invalid password");
                }
                emit connectionTested(false, errorMsg);
            }
        });
    } else if (!token.isEmpty()) {
        QNetworkRequest infoReq = createRequest(QStringLiteral("etapi/app-info"), url, token);
        QNetworkReply *reply = m_nam->get(infoReq);
        connect(reply, &QNetworkReply::finished, this, [this, url, token, reply]() {
            int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            reply->deleteLater();
            setBusy(false);

            if (reply->error() == QNetworkReply::NoError) {
                m_settings->setServerUrl(url);
                m_settings->setApiToken(token);
                emit connectionTested(true, QString());
            } else {
                QString errorMsg = reply->errorString();
                if (httpStatus == 401) {
                    errorMsg = tr("Unauthorized: Invalid API Token");
                }
                emit connectionTested(false, errorMsg);
            }
        });
    } else {
        setBusy(false);
        emit connectionTested(false, tr("Please provide a password or an API token"));
    }
}

void TrilliumApi::fetchNotes(const QString &parentNoteId)
{
    setBusy(true);
    QNetworkRequest req = createRequest(QStringLiteral("etapi/notes"));
    
    QUrl url = req.url();
    QUrlQuery query;
    QString searchQuery = QStringLiteral("note.parents.noteId = '%1'").arg(parentNoteId);
    query.addQueryItem(QStringLiteral("search"), searchQuery);
    url.setQuery(query);
    req.setUrl(url);

    QNetworkReply *reply = m_nam->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, parentNoteId, reply]() {
        reply->deleteLater();
        setBusy(false);

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            if (doc.isObject()) {
                QJsonObject obj = doc.object();
                QJsonArray results = obj.value(QStringLiteral("results")).toArray();
                emit notesReceived(parentNoteId, results);
            } else {
                qWarning() << "[TrilliumApi] fetchNotes: response is not a JSON object";
                emit notesReceived(parentNoteId, QJsonArray());
            }
        } else {
            qWarning() << "[TrilliumApi] fetchNotes failed:" << reply->errorString();
            emit notesReceived(parentNoteId, QJsonArray());
        }
    });
}

void TrilliumApi::fetchNoteContent(const QString &noteId)
{
    setBusy(true);
    QNetworkRequest req = createRequest(QStringLiteral("etapi/notes/%1/content").arg(noteId));

    QNetworkReply *reply = m_nam->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, noteId, reply]() {
        reply->deleteLater();
        setBusy(false);

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QString content = QString::fromUtf8(data);
            emit noteContentReceived(noteId, content);
        } else {
            qWarning() << "[TrilliumApi] fetchNoteContent failed:" << reply->errorString();
            emit noteContentReceived(noteId, tr("Failed to fetch note content: %1").arg(reply->errorString()));
        }
    });
}
