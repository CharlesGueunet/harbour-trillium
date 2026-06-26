import QtQuick 2.0
import Sailfish.Silica 1.0

ApplicationWindow {
    id: appWindow
    property string activeNoteTitle: "Trillium"
    property string activeNoteId: "root"
    initialPage: (settingsManager.apiToken === "" || settingsManager.serverUrl === "")
                 ? Qt.resolvedUrl("pages/LoginPage.qml")
                 : Qt.resolvedUrl("pages/NoteOverviewPage.qml")
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
}
