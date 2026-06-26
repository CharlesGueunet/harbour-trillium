#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QTranslator>
#include <QLoggingCategory>
#include <cstdio>
#include "settingsmanager.h"
#include "trilliumapi.h"
#include "notemodel.h"

static void trilliumMessageHandler(QtMsgType type, const QMessageLogContext &ctx, const QString &msg)
{
    Q_UNUSED(ctx)
    const char *level = "[D]";
    switch (type) {
    case QtWarningMsg:  level = "[W]"; break;
    case QtCriticalMsg: level = "[C]"; break;
    case QtFatalMsg:    level = "[F]"; break;
    default: break;
    }
    fprintf(stderr, "%s %s\n", level, qPrintable(msg));
    fflush(stderr);
}

int main(int argc, char *argv[])
{
    qputenv("QT_LOGGING_RULES", "*.debug=true");
    qInstallMessageHandler(trilliumMessageHandler);

    QGuiApplication *app = SailfishApp::application(argc, argv);
    app->setOrganizationName("mezmerize");
    app->setApplicationName("harbour-trillium");

    QQuickView *view = SailfishApp::createView();

    SettingsManager *settingsManager = new SettingsManager(app);
    TrilliumApi *trilliumApi = new TrilliumApi(settingsManager, app);
    NoteModel *noteModel = new NoteModel(app);

    // Connect Trillium API notes receipt to local note model
    QObject::connect(trilliumApi, &TrilliumApi::notesReceived, [noteModel](const QString &parentNoteId, const QJsonArray &notes) {
        Q_UNUSED(parentNoteId)
        noteModel->loadNotes(notes);
    });

    // Translations
    QTranslator *translator = new QTranslator(app);
    const QString translationsDir = SailfishApp::pathTo("translations").toLocalFile();
    if (!translator->load(QLocale::system(), QStringLiteral("harbour-trillium"), QStringLiteral("-"), translationsDir)) {
        translator->load(QStringLiteral("harbour-trillium-en"), translationsDir);
    }
    app->installTranslator(translator);

    view->rootContext()->setContextProperty(QStringLiteral("settingsManager"), settingsManager);
    view->rootContext()->setContextProperty(QStringLiteral("trilliumApi"), trilliumApi);
    view->rootContext()->setContextProperty(QStringLiteral("noteModel"), noteModel);

    view->setSource(SailfishApp::pathTo("qml/harbour-trillium.qml"));
    view->show();

    return app->exec();
}
