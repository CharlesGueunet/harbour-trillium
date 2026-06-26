import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: overviewPage
    allowedOrientations: defaultAllowedOrientations

    property string currentNoteId: "root"
    property string currentNoteTitle: qsTr("Root Notes")

    Connections {
        target: trilliumApi
        onNoteCreated: {
            if (success && parentNoteId === currentNoteId) {
                trilliumApi.fetchNotes(currentNoteId);
            }
        }
        onNoteDeleted: {
            if (success) {
                trilliumApi.fetchNotes(currentNoteId);
            }
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Activating) {
            noteModel.clear();
            trilliumApi.fetchNotes(currentNoteId);
        }
    }

    SilicaListView {
        id: noteListView
        anchors.fill: parent
        model: noteModel

        VerticalScrollDecorator {}

        PullDownMenu {
            MenuItem {
                text: qsTr("Disconnect")
                onClicked: {
                    settingsManager.clear();
                    pageStack.replace(Qt.resolvedUrl("LoginPage.qml"));
                }
            }

            MenuItem {
                text: qsTr("Add Note")
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("NoteCreateDialog.qml"));
                    dialog.accepted.connect(function() {
                        pageStack.replace(Qt.resolvedUrl("NoteEditDialog.qml"), {
                            "isNewNote": true,
                            "parentNoteId": currentNoteId,
                            "noteTitle": dialog.noteTitle,
                            "initialContent": ""
                        });
                    });
                }
            }

            MenuItem {
                text: qsTr("Refresh")
                onClicked: trilliumApi.fetchNotes(currentNoteId)
            }
        }

        header: PageHeader {
            title: currentNoteTitle
            extraContent.children: [
                BusyIndicator {
                    running: trilliumApi.busy
                    size: BusyIndicatorSize.Small
                    anchors.verticalCenter: parent.verticalCenter
                }
            ]
        }

        delegate: ListItem {
            id: noteDelegate
            width: noteListView.width
            contentHeight: Theme.itemSizeSmall

            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Open Sub-notes")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("NoteOverviewPage.qml"), {
                            "currentNoteId": noteId,
                            "currentNoteTitle": title
                        });
                    }
                }
                MenuItem {
                    text: qsTr("View Details")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("NoteDetailPage.qml"), {
                            "noteId": noteId,
                            "noteTitle": title,
                            "noteType": type
                        });
                    }
                }
                MenuItem {
                    text: qsTr("Delete")
                    onClicked: {
                        trilliumApi.deleteNote(noteId);
                    }
                }
            }

            onClicked: {
                pageStack.push(Qt.resolvedUrl("NoteDetailPage.qml"), {
                    "noteId": noteId,
                    "noteTitle": title,
                    "noteType": type
                });
            }

            IconButton {
                id: typeIcon
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                icon.source: {
                    if (type === "text") return "image://theme/icon-m-file-document";
                    if (type === "image") return "image://theme/icon-m-image";
                    if (type === "code") return "image://theme/icon-m-file-formatted";
                    return "image://theme/icon-m-file-other";
                }
                enabled: false
            }

            Label {
                id: titleLabel
                text: title
                textFormat: Text.PlainText
                anchors.left: typeIcon.right
                anchors.leftMargin: Theme.paddingMedium
                anchors.right: parent.right
                anchors.rightMargin: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
                elide: Text.ElideRight
            }
        }

        ViewPlaceholder {
            enabled: noteListView.count === 0 && !trilliumApi.busy
            text: qsTr("No notes found")
            hintText: qsTr("Pull down to refresh or make sure your server is online")
        }
    }
}
