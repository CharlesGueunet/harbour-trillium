#ifndef TRILLIUMAPI_H
#define TRILLIUMAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "settingsmanager.h"

class TrilliumApi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:
    explicit TrilliumApi(SettingsManager *settings, QObject *parent = nullptr);

    bool busy() const;

    Q_INVOKABLE void testConnection(const QString &url, const QString &password, const QString &token);
    Q_INVOKABLE void fetchNotes(const QString &parentNoteId = QStringLiteral("root"));
    Q_INVOKABLE void fetchNoteContent(const QString &noteId);
    Q_INVOKABLE void updateNoteContent(const QString &noteId, const QString &content);
    Q_INVOKABLE void createNote(const QString &parentNoteId, const QString &title, const QString &content);

signals:
    void busyChanged();
    void connectionTested(bool success, const QString &errorMessage);
    void notesReceived(const QString &parentNoteId, const QJsonArray &notes);
    void noteContentReceived(const QString &noteId, const QString &content);
    void noteContentUpdated(const QString &noteId, bool success, const QString &errorMessage);
    void noteCreated(const QString &parentNoteId, bool success, const QString &errorMessage);

private:
    QNetworkRequest createRequest(const QString &endpoint, const QString &overrideUrl = QString(), const QString &overrideToken = QString());
    void setBusy(bool busy);

    SettingsManager *m_settings;
    QNetworkAccessManager *m_nam;
    bool m_busy;
};

#endif // TRILLIUMAPI_H
