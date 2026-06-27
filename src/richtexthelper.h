#ifndef RICHTEXTHELPER_H
#define RICHTEXTHELPER_H

#include <QObject>
#include <QQuickTextDocument>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextBlock>
#include <QTextList>
#include <QTextBlockFormat>
#include <QTextListFormat>
#include <QRegularExpression>
#include <QSet>
#include <QImage>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QBuffer>
#include <QMimeDatabase>
#include <QMimeType>
#include <QDebug>
#include "settingsmanager.h"

class RichTextHelper : public QObject
{
    Q_OBJECT
public:
    explicit RichTextHelper(SettingsManager *settings, QObject *parent = nullptr)
        : QObject(parent), m_settings(settings), m_nam(new QNetworkAccessManager(this)) {}

    Q_INVOKABLE void registerDocument(QObject *textDocument, int maxWidth = 0) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (!doc) return;

        connect(doc, &QTextDocument::contentsChange, this, &RichTextHelper::onContentsChange);

        connect(doc, &QTextDocument::contentsChanged, this, [this, doc, maxWidth]() {
            loadImagesInDocument(doc, maxWidth);
        });

        loadImagesInDocument(doc, maxWidth);
    }

    Q_INVOKABLE void loadImages(QObject *textDocument, int maxWidth = 0) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (doc) {
            loadImagesInDocument(doc, maxWidth);
        }
    }

    Q_INVOKABLE void insertImage(QObject *textDocument, int cursorPosition, const QString &imageUrl) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (!doc) return;

        QTextCursor cursor(doc);
        cursor.setPosition(cursorPosition);
        cursor.insertHtml(QStringLiteral("<img src=\"%1\" />").arg(imageUrl));
    }

    Q_INVOKABLE void insertLocalImage(QObject *textDocument, int cursorPosition, const QString &filePath, int maxWidth = 0) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (!doc) return;

        QString path = filePath;
        if (path.startsWith(QLatin1String("file://"))) {
            path = path.mid(7);
        }

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "[RichTextHelper] Failed to open local file:" << path;
            return;
        }

        QByteArray data = file.readAll();
        QImage image = QImage::fromData(data);
        if (image.isNull()) {
            qWarning() << "[RichTextHelper] Failed to parse image data from:" << path;
            return;
        }

        int targetWidth = maxWidth > 0 ? maxWidth : 1080;
        if (image.width() > targetWidth) {
            image = image.scaledToWidth(targetWidth, Qt::SmoothTransformation);
            QByteArray scaledData;
            QBuffer buffer(&scaledData);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PNG");
            data = scaledData;
        }

        QString base64 = QString::fromLatin1(data.toBase64());
        
        QMimeDatabase db;
        QMimeType mime = db.mimeTypeForFile(path);
        QString mimeType = mime.name();
        if (mimeType.isEmpty()) {
            mimeType = QStringLiteral("image/png");
        }

        if (image.width() > targetWidth) {
            mimeType = QStringLiteral("image/png");
        }

        QString dataUrl = QStringLiteral("data:%1;base64,%2").arg(mimeType, base64);

        QTextCursor cursor(doc);
        cursor.setPosition(cursorPosition);
        cursor.insertHtml(QStringLiteral("<img src=\"%1\" />").arg(dataUrl));
        scaleImagesInDocument(doc, maxWidth);
    }

    Q_INVOKABLE void toggleBold(QObject *textDocument, int selectionStart, int selectionEnd) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (!doc) return;

        QTextCursor cursor(doc);
        cursor.setPosition(selectionStart);

        QTextCharFormat format;
        if (selectionStart == selectionEnd) {
            bool isBold = cursor.charFormat().fontWeight() == QFont::Bold;
            format.setFontWeight(isBold ? QFont::Normal : QFont::Bold);
            cursor.insertText(QString(QChar(0x200B)), format);
        } else {
            cursor.setPosition(selectionEnd, QTextCursor::KeepAnchor);
            format.setFontWeight(cursor.charFormat().fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
            cursor.mergeCharFormat(format);
        }
    }

    Q_INVOKABLE void toggleItalic(QObject *textDocument, int selectionStart, int selectionEnd) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (!doc) return;

        QTextCursor cursor(doc);
        cursor.setPosition(selectionStart);

        QTextCharFormat format;
        if (selectionStart == selectionEnd) {
            bool isItalic = cursor.charFormat().fontItalic();
            format.setFontItalic(!isItalic);
            cursor.insertText(QString(QChar(0x200B)), format);
        } else {
            cursor.setPosition(selectionEnd, QTextCursor::KeepAnchor);
            format.setFontItalic(!cursor.charFormat().fontItalic());
            cursor.mergeCharFormat(format);
        }
    }

    Q_INVOKABLE void toggleUnderline(QObject *textDocument, int selectionStart, int selectionEnd) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (!doc) return;

        QTextCursor cursor(doc);
        cursor.setPosition(selectionStart);

        QTextCharFormat format;
        if (selectionStart == selectionEnd) {
            bool isUnderline = cursor.charFormat().fontUnderline();
            format.setFontUnderline(!isUnderline);
            cursor.insertText(QString(QChar(0x200B)), format);
        } else {
            cursor.setPosition(selectionEnd, QTextCursor::KeepAnchor);
            format.setFontUnderline(!cursor.charFormat().fontUnderline());
            cursor.mergeCharFormat(format);
        }
    }

    Q_INVOKABLE void setHeading(QObject *textDocument, int selectionStart, int selectionEnd, int level) {
        QQuickTextDocument *quickDoc = qobject_cast<QQuickTextDocument*>(textDocument);
        if (!quickDoc) return;
        QTextDocument *doc = quickDoc->textDocument();
        if (!doc) return;

        QTextCursor cursor(doc);
        cursor.setPosition(selectionStart);
        cursor.setPosition(selectionEnd, QTextCursor::KeepAnchor);

        cursor.beginEditBlock();

        QTextCharFormat charFormat;
        if (level == 1) {
            charFormat.setFontWeight(QFont::Bold);
            charFormat.setFontPointSize(22);
        }
        else if (level == 2) {
            charFormat.setFontWeight(QFont::Bold);
            charFormat.setFontPointSize(18);
        }
        else if (level == 3) {
            charFormat.setFontWeight(QFont::Bold);
            charFormat.setFontPointSize(14);
        }
        else {
            charFormat.setFontWeight(QFont::Normal);
            charFormat.setFontPointSize(12); // standard size
        }
        cursor.mergeCharFormat(charFormat);

        cursor.endEditBlock();
    }

private slots:
    void onContentsChange(int position, int charsRemoved, int charsAdded) {
        Q_UNUSED(charsRemoved)
        QTextDocument *doc = qobject_cast<QTextDocument*>(sender());
        if (!doc || charsAdded != 1) return;

        QTextCursor cursor(doc);
        cursor.setPosition(position + charsAdded);

        cursor.setPosition(position, QTextCursor::KeepAnchor);
        if (cursor.selectedText() != QLatin1String(" ")) return;

        QTextBlock block = cursor.block();
        QString text = block.text();

        if (text.startsWith(QLatin1String("* "))) {
            doc->blockSignals(true);

            QTextCursor editCursor(doc);
            editCursor.beginEditBlock();
            editCursor.setPosition(block.position());
            editCursor.setPosition(block.position() + 2, QTextCursor::KeepAnchor);
            editCursor.removeSelectedText();

            QTextListFormat listFormat;
            listFormat.setStyle(QTextListFormat::ListDisc);
            editCursor.insertList(listFormat);

            editCursor.endEditBlock();

            doc->blockSignals(false);
        }
    }

private:
    void scaleImagesInDocument(QTextDocument *doc, int maxWidth) {
        if (!doc || maxWidth <= 0) return;

        doc->blockSignals(true);
        QTextCursor cursor(doc);

        for (QTextBlock block = doc->begin(); block != doc->end(); block = block.next()) {
            for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
                QTextFragment fragment = it.fragment();
                if (fragment.isValid()) {
                    QTextCharFormat format = fragment.charFormat();
                    if (format.isImageFormat()) {
                        QTextImageFormat imgFormat = format.toImageFormat();
                        qreal w = imgFormat.width();
                        qreal h = imgFormat.height();

                        QUrl resolvedUrl = doc->baseUrl().resolved(QUrl(imgFormat.name()));
                        QVariant resource = doc->resource(QTextDocument::ImageResource, resolvedUrl);
                        QImage img;
                        if (resource.isValid()) {
                            img = resource.value<QImage>();
                        }

                        qreal actualWidth = w > 0 ? w : (img.isNull() ? 0 : img.width());
                        qreal actualHeight = h > 0 ? h : (img.isNull() ? 0 : img.height());

                        if (actualWidth > maxWidth) {
                            qreal ratio = actualWidth > 0 ? (actualHeight / actualWidth) : 1.0;
                            qreal newWidth = maxWidth;
                            qreal newHeight = maxWidth * ratio;

                            imgFormat.setWidth(newWidth);
                            imgFormat.setHeight(newHeight);

                            cursor.setPosition(fragment.position());
                            cursor.setPosition(fragment.position() + fragment.length(), QTextCursor::KeepAnchor);
                            cursor.setCharFormat(imgFormat);
                        }
                    }
                }
            }
        }
        doc->blockSignals(false);
        doc->markContentsDirty(0, doc->characterCount());
    }

    void loadImagesInDocument(QTextDocument *doc, int maxWidth) {
        if (!doc) return;
        QString html = doc->toHtml();
        QUrl docBase = doc->baseUrl();

        QRegularExpression rx(QStringLiteral("src=['\"](?:https?://[^/]+)?/?(api/(?:images|attachments)/[^'\"]+)['\"]"));
        QRegularExpressionMatchIterator i = rx.globalMatch(html);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            QString relativePath = match.captured(1);

            QUrl resolvedUrl = docBase.resolved(QUrl(relativePath));
            QVariant cached = doc->resource(QTextDocument::ImageResource, resolvedUrl);
            if (cached.isValid()) {
                QImage img = cached.value<QImage>();
                QPixmap pix = cached.value<QPixmap>();
                if (!img.isNull() || !pix.isNull()) {
                    continue;
                }
            }

            if (m_loadingUrls.contains(relativePath)) {
                continue;
            }
            m_loadingUrls.insert(relativePath);

            downloadImage(doc, relativePath, maxWidth);
        }
        scaleImagesInDocument(doc, maxWidth);
    }

    void downloadImage(QTextDocument *doc, const QString &relativePath, int maxWidth) {
        QStringList parts = relativePath.split(QLatin1Char('/'));
        if (parts.size() < 3) {
            m_loadingUrls.remove(relativePath);
            return;
        }
        QString type = parts[1];
        QString id = parts[2];

        QString endpoint;
        if (type == QLatin1String("images")) {
            endpoint = QStringLiteral("etapi/notes/%1/content").arg(id);
        } else if (type == QLatin1String("attachments")) {
            endpoint = QStringLiteral("etapi/attachments/%1/content").arg(id);
        } else {
            m_loadingUrls.remove(relativePath);
            return;
        }

        QNetworkRequest req = createRequest(endpoint);
        QNetworkReply *reply = m_nam->get(req);

        connect(reply, &QNetworkReply::finished, this, [this, doc, relativePath, reply, maxWidth]() {
            reply->deleteLater();
            m_loadingUrls.remove(relativePath);

            if (reply->error() == QNetworkReply::NoError) {
                QByteArray data = reply->readAll();
                QImage image = QImage::fromData(data);
                if (!image.isNull()) {
                    if (maxWidth > 0 && image.width() > maxWidth) {
                        image = image.scaledToWidth(maxWidth, Qt::SmoothTransformation);
                    }
                    QUrl resolvedUrl = doc->baseUrl().resolved(QUrl(relativePath));
                    doc->addResource(QTextDocument::ImageResource, resolvedUrl, image);
                    doc->markContentsDirty(0, doc->characterCount());
                    scaleImagesInDocument(doc, maxWidth);
                }
            }
        });
    }

    QNetworkRequest createRequest(const QString &endpoint) {
        QString baseUrl = m_settings->serverUrl();
        QString token = m_settings->apiToken();

        if (!baseUrl.endsWith(QStringLiteral("/"))) {
            baseUrl += QStringLiteral("/");
        }

        QUrl url(baseUrl + endpoint);
        QNetworkRequest request(url);

        if (!token.isEmpty()) {
            request.setRawHeader("Authorization", token.toUtf8());
        }

        return request;
    }

    SettingsManager *m_settings;
    QNetworkAccessManager *m_nam;
    QSet<QString> m_loadingUrls;
};

#endif // RICHTEXTHELPER_H
