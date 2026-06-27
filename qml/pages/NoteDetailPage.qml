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
        onNoteDownloaded: {
            if (noteId === detailPage.noteId) {
                statusLabel.text = message;
                statusLabel.color = success ? Theme.primaryColor : Theme.errorColor;
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
        if (noteType === "text" || noteType === "code") {
            trilliumApi.fetchNoteContent(noteId);
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: contentColumn.height + Theme.paddingLarge

        PullDownMenu {
            MenuItem {
                text: qsTr("Edit")
                visible: noteType === "text" || noteType === "code"
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
                visible: noteType === "text" || noteType === "code"
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
                text: noteContent !== "" ? noteContent : (trilliumApi.busy ? qsTr("Loading note content...") : qsTr("No content"))
                textFormat: TextEdit.RichText
                wrapMode: TextEdit.Wrap
                color: Theme.primaryColor
                readOnly: true
                selectByMouse: false
                visible: noteType === "text" || noteType === "code"

                onTextChanged: {
                    richTextHelper.loadImages(contentLabel.textDocument, contentLabel.width);
                }

                Component.onCompleted: {
                    richTextHelper.registerDocument(contentLabel.textDocument, contentLabel.width);
                }
            }

            Column {
                width: parent.width - 2 * Theme.horizontalPageMargin
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingLarge
                visible: noteType !== "text" && noteType !== "code"

                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: noteType === "image" ? "image://theme/icon-l-image" : "image://theme/icon-l-document"
                    width: Theme.iconSizeLarge
                    height: Theme.iconSizeLarge
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("This is a binary file note. Press the button below to download it to your device.")
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                    wrapMode: Text.Wrap
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: trilliumApi.busy ? qsTr("Downloading...") : qsTr("Download File")
                    enabled: !trilliumApi.busy
                    onClicked: {
                        statusLabel.text = qsTr("Starting download...");
                        statusLabel.color = Theme.secondaryColor;
                        trilliumApi.downloadNote(noteId, noteTitle);
                    }
                }

                Label {
                    id: statusLabel
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.Wrap
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                }
            }
        }
    }
}
