TARGET = harbour-trillium

CONFIG += sailfishapp link_pkgconfig
QT += network
PKGCONFIG += sailfishapp sailfishsecrets

CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += src/main.cpp \
    src/settingsmanager.cpp \
    src/trilliumapi.cpp \
    src/notemodel.cpp

HEADERS += \
    src/settingsmanager.h \
    src/trilliumapi.h \
    src/notemodel.h

icons.files = icons/cover-icon.png
icons.path = $$PREFIX/share/$${TARGET}/icons
INSTALLS += icons

DISTFILES += qml/harbour-trillium.qml \
    qml/cover/CoverPage.qml \
    qml/pages/LoginPage.qml \
    qml/pages/NoteOverviewPage.qml \
    qml/pages/NoteDetailPage.qml \
    icons/cover-icon.png \
    icons/sfos-icon.png \
    rpm/harbour-trillium.spec \
    translations/*.ts \
    harbour-trillium.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += sailfishapp_i18n sailfishapp_i18n_idbased

TRANSLATIONS += translations/harbour-trillium.ts \
                translations/harbour-trillium-en.ts

lupdate_only {
    SOURCES += qml/*.qml \
               qml/pages/*.qml \
               qml/cover/*.qml
}
