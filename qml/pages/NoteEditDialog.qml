import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Dialog {
    id: editDialog
    property string noteId
    property string noteTitle
    property string initialContent
    property bool isNewNote: false
    property string parentNoteId

    property alias noteContent: editTextArea.text

    canAccept: true

    onAccepted: {
        if (isNewNote) {
            trilliumApi.createNote(parentNoteId, noteTitle, editTextArea.text);
        } else {
            trilliumApi.updateNoteContent(noteId, editTextArea.text);
        }
    }

    Component.onCompleted: {
        richTextHelper.registerDocument(editTextArea.textDocument, editTextArea.width);
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: contentColumn.height + Theme.paddingLarge

        Column {
            id: contentColumn
            width: parent.width
            spacing: Theme.paddingMedium

            DialogHeader {
                title: isNewNote ? qsTr("Create Note: %1").arg(noteTitle) : qsTr("Edit Note")
            }

            // Toolbar Row for text styling (scrollable horizontally if needed, or wrapped)
            Flow {
                id: formatToolbar
                width: parent.width - 2 * Theme.horizontalPageMargin
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingSmall

                Rectangle {
                    width: 70
                    height: 60
                    color: boldMouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "B"
                        font.bold: true
                        font.pixelSize: Theme.fontSizeMedium
                        color: boldMouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: boldMouse
                        anchors.fill: parent
                        onClicked: richTextHelper.toggleBold(editTextArea.textDocument, editTextArea.selectionStart, editTextArea.selectionEnd)
                    }
                }

                Rectangle {
                    width: 70
                    height: 60
                    color: italicMouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "I"
                        font.italic: true
                        font.pixelSize: Theme.fontSizeMedium
                        color: italicMouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: italicMouse
                        anchors.fill: parent
                        onClicked: richTextHelper.toggleItalic(editTextArea.textDocument, editTextArea.selectionStart, editTextArea.selectionEnd)
                    }
                }

                Rectangle {
                    width: 70
                    height: 60
                    color: underlineMouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "U"
                        font.underline: true
                        font.pixelSize: Theme.fontSizeMedium
                        color: underlineMouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: underlineMouse
                        anchors.fill: parent
                        onClicked: richTextHelper.toggleUnderline(editTextArea.textDocument, editTextArea.selectionStart, editTextArea.selectionEnd)
                    }
                }

                Rectangle {
                    width: 70
                    height: 60
                    color: h1Mouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "H1"
                        font.bold: true
                        font.pixelSize: Theme.fontSizeMedium
                        color: h1Mouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: h1Mouse
                        anchors.fill: parent
                        onClicked: richTextHelper.setHeading(editTextArea.textDocument, editTextArea.selectionStart, editTextArea.selectionEnd, 1)
                    }
                }

                Rectangle {
                    width: 70
                    height: 60
                    color: h2Mouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "H2"
                        font.bold: true
                        font.pixelSize: Theme.fontSizeMedium
                        color: h2Mouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: h2Mouse
                        anchors.fill: parent
                        onClicked: richTextHelper.setHeading(editTextArea.textDocument, editTextArea.selectionStart, editTextArea.selectionEnd, 2)
                    }
                }

                Rectangle {
                    width: 70
                    height: 60
                    color: h3Mouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "H3"
                        font.bold: true
                        font.pixelSize: Theme.fontSizeMedium
                        color: h3Mouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: h3Mouse
                        anchors.fill: parent
                        onClicked: richTextHelper.setHeading(editTextArea.textDocument, editTextArea.selectionStart, editTextArea.selectionEnd, 3)
                    }
                }

                Rectangle {
                    width: 70
                    height: 60
                    color: normalMouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "Txt"
                        font.pixelSize: Theme.fontSizeMedium
                        color: normalMouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: normalMouse
                        anchors.fill: parent
                        onClicked: richTextHelper.setHeading(editTextArea.textDocument, editTextArea.selectionStart, editTextArea.selectionEnd, 0)
                    }
                }

                Rectangle {
                    width: 70
                    height: 60
                    color: imgMouse.pressed ? Theme.rgba(Theme.highlightColor, 0.2) : Theme.rgba(Theme.primaryColor, 0.1)
                    radius: Theme.paddingSmall
                    Text {
                        anchors.centerIn: parent
                        text: "Img"
                        font.pixelSize: Theme.fontSizeMedium
                        color: imgMouse.pressed ? Theme.highlightColor : Theme.primaryColor
                    }
                    MouseArea {
                        id: imgMouse
                        anchors.fill: parent
                        onClicked: {
                            pageStack.push(imagePickerComponent);
                        }
                    }
                }
            }

            // Styled container for TextEdit
            Rectangle {
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: Math.max(400, editTextArea.implicitHeight + 2 * Theme.paddingMedium)
                anchors.horizontalCenter: parent.horizontalCenter
                color: Theme.rgba(Theme.primaryColor, 0.05)
                radius: Theme.paddingSmall
                border.color: editTextArea.focus ? Theme.highlightColor : Theme.rgba(Theme.primaryColor, 0.1)
                border.width: 1

                TextEdit {
                    id: editTextArea
                    anchors.fill: parent
                    anchors.margins: Theme.paddingMedium
                    text: initialContent
                    textFormat: TextEdit.RichText
                    wrapMode: TextEdit.Wrap
                    color: Theme.primaryColor
                    focus: true
                    selectByMouse: true
                    persistentSelection: true

                    onTextChanged: {
                        richTextHelper.loadImages(editTextArea.textDocument, editTextArea.width);
                    }

                    // Placeholder text
                    Text {
                        text: qsTr("Note content")
                        color: Theme.rgba(Theme.primaryColor, 0.4)
                        font.pixelSize: Theme.fontSizeMedium
                        visible: editTextArea.text.length === 0 && !editTextArea.focus
                        anchors.fill: parent
                        anchors.margins: Theme.paddingMedium
                    }
                }
            }
        }
    }

    Component {
        id: imagePickerComponent
        ImagePickerPage {
            onSelectedContentPropertiesChanged: {
                if (selectedContentProperties.filePath) {
                    richTextHelper.insertLocalImage(editTextArea.textDocument, editTextArea.cursorPosition, selectedContentProperties.filePath, editTextArea.width);
                }
            }
        }
    }
}
