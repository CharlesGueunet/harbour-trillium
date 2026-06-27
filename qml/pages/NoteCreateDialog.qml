import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: createDialog
    property string noteTitle

    canAccept: noteTitleField.text.trim().length > 0

    onAccepted: {
        noteTitle = noteTitleField.text.trim();
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: contentColumn.height + Theme.paddingLarge

        Column {
            id: contentColumn
            width: parent.width
            spacing: Theme.paddingLarge

            DialogHeader {
                title: qsTr("New Note Title")
                acceptText: qsTr("Create")
            }

            TextField {
                id: noteTitleField
                width: parent.width - Theme.paddingLarge * 2
                anchors.horizontalCenter: parent.horizontalCenter
                label: qsTr("Title")
                placeholderText: qsTr("Enter note title")
                focus: true
                EnterKey.enabled: text.trim().length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                EnterKey.onClicked: {
                    if (canAccept) {
                        createDialog.accept();
                    }
                }
            }
        }
    }
}
