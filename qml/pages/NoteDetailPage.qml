import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: detailPage
    allowedOrientations: defaultAllowedOrientations

    property string noteId
    property string noteTitle
    property string noteType
    property string noteContent: ""

    Connections {
        target: trilliumApi
        onNoteContentReceived: {
            if (noteId === detailPage.noteId) {
                detailPage.noteContent = content;
            }
        }
        onNoteContentUpdated: {
            if (noteId === detailPage.noteId && success) {
                trilliumApi.fetchNoteContent(noteId);
            }
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {
            pageStack.pushAttached(Qt.resolvedUrl("NoteOverviewPage.qml"), {
                "currentNoteId": noteId,
                "currentNoteTitle": noteTitle
            });
        }
    }

    Component.onCompleted: {
        trilliumApi.fetchNoteContent(noteId);
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: contentColumn.height + Theme.paddingLarge

        PullDownMenu {
            MenuItem {
                text: qsTr("Edit")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("NoteEditDialog.qml"), {
                        "noteId": noteId,
                        "noteTitle": noteTitle,
                        "initialContent": noteContent
                    });
                }
            }

            MenuItem {
                text: qsTr("Refresh Content")
                onClicked: trilliumApi.fetchNoteContent(noteId)
            }
        }

        Column {
            id: contentColumn
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: noteTitle
            }

            Row {
                width: parent.width - 2 * Theme.horizontalPageMargin
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingSmall
                visible: noteType !== ""

                Label {
                    text: qsTr("Type: %1").arg(noteType)
                    font.pixelSize: Theme.fontSizeTiny
                    color: Theme.secondaryColor
                }

                BusyIndicator {
                    running: trilliumApi.busy
                    size: BusyIndicatorSize.Small
                    visible: trilliumApi.busy
                }
            }

            TextEdit {
                id: contentLabel
                width: parent.width - 2 * Theme.horizontalPageMargin
                anchors.horizontalCenter: parent.horizontalCenter
                text: noteContent !== "" ? noteContent : (trilliumApi.busy ? qsTr("Loading note content...") : qsTr("No content or unsupported note type"))
                textFormat: TextEdit.RichText
                wrapMode: TextEdit.Wrap
                color: Theme.primaryColor
                readOnly: true
                selectByMouse: false

                onTextChanged: {
                    richTextHelper.loadImages(contentLabel.textDocument, contentLabel.width);
                }

                Component.onCompleted: {
                    richTextHelper.registerDocument(contentLabel.textDocument, contentLabel.width);
                }
            }
        }
    }
}
