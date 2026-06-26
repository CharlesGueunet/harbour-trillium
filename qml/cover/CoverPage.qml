import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    id: cover

    ListModel {
        id: coverNoteModel
    }

    function updateCoverNotes() {
        coverNoteModel.clear();
        var count = 0;
        for (var i = 0; i < noteModel.count; ++i) {
            var note = noteModel.getNote(i);
            if (note) {
                coverNoteModel.append({
                    "title": note.title,
                    "type": note.type
                });
                count++;
                if (count >= 5) {
                    break;
                }
            }
        }
    }

    Connections {
        target: noteModel
        onDataChanged: cover.updateCoverNotes()
        onModelReset: cover.updateCoverNotes()
        onRowsInserted: cover.updateCoverNotes()
        onRowsRemoved: cover.updateCoverNotes()
    }

    Connections {
        target: appWindow
        onActiveNoteIdChanged: cover.updateCoverNotes()
    }

    Component.onCompleted: updateCoverNotes()

    CoverPlaceholder {
        text: qsTr("Trillium")
        icon.source: "../../icons/sfos-icon.png"
        visible: coverNoteModel.count === 0
    }

    Column {
        anchors {
            fill: parent
            margins: Theme.paddingMedium
        }
        spacing: Theme.paddingSmall
        visible: coverNoteModel.count > 0

        Label {
            text: appWindow.activeNoteTitle
            font.bold: true
            color: Theme.primaryColor
            anchors.horizontalCenter: parent.horizontalCenter
            elide: Text.ElideRight
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }

        Separator {
            width: parent.width
            color: Theme.highlightColor
        }

        Repeater {
            model: coverNoteModel
            delegate: Label {
                width: parent.width
                text: {
                    var prefix = "• ";
                    if (type === "text") prefix = "📄 ";
                    else if (type === "image") prefix = "🖼️ ";
                    else if (type === "code") prefix = "💻 ";
                    return prefix + title;
                }
                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeExtraSmall
                truncationMode: TruncationMode.Fade
            }
        }
    }
}
