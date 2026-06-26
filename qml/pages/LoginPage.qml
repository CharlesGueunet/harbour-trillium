import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: loginPage
    allowedOrientations: defaultAllowedOrientations

    Connections {
        target: trilliumApi
        onConnectionTested: {
            if (success) {
                settingsManager.serverUrl = serverUrlField.text;
                if (tokenField.text !== "") {
                    settingsManager.apiToken = tokenField.text;
                }
                pageStack.replace(Qt.resolvedUrl("NoteOverviewPage.qml"));
            } else {
                errorLabel.text = errorMessage;
            }
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: contentColumn.height + Theme.paddingLarge

        Column {
            id: contentColumn
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Setup Trillium")
            }

            Rectangle {
                width: parent.width - 2 * Theme.paddingLarge
                height: 120
                color: "transparent"
                anchors.horizontalCenter: parent.horizontalCenter

                Image {
                    source: Qt.resolvedUrl("../../icons/sfos-icon.png")
                    width: 96
                    height: 96
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                }
            }

            TextField {
                id: serverUrlField
                width: parent.width - Theme.paddingLarge * 2
                anchors.horizontalCenter: parent.horizontalCenter
                label: qsTr("Server URL")
                placeholderText: "https://trilium.example.com"
                text: settingsManager.serverUrl !== "" ? settingsManager.serverUrl : ""
                inputMethodHints: Qt.ImhUrlCharactersOnly
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: passwordField.focus = true
            }

            TextField {
                id: passwordField
                width: parent.width - Theme.paddingLarge * 2
                anchors.horizontalCenter: parent.horizontalCenter
                label: qsTr("Password")
                placeholderText: qsTr("Enter your Trilium Password")
                echoMode: TextInput.Password
                inputMethodHints: Qt.ImhNoPredictiveText
                EnterKey.enabled: text.length > 0 || tokenField.text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: tokenField.focus = true
            }

            TextField {
                id: tokenField
                width: parent.width - Theme.paddingLarge * 2
                anchors.horizontalCenter: parent.horizontalCenter
                label: qsTr("OR API Token (Optional)")
                placeholderText: qsTr("Pasted pre-generated token")
                text: settingsManager.apiToken
                inputMethodHints: Qt.ImhNoPredictiveText
                EnterKey.enabled: text.length > 0 || passwordField.text.length > 0
                EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                EnterKey.onClicked: loginButton.clicked()
            }

            Label {
                id: errorLabel
                width: parent.width - Theme.paddingLarge * 2
                anchors.horizontalCenter: parent.horizontalCenter
                color: Theme.errorColor
                font.pixelSize: Theme.fontSizeSmall
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.Wrap
            }

            Button {
                id: loginButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: trilliumApi.busy ? qsTr("Connecting...") : qsTr("Connect")
                enabled: !trilliumApi.busy && serverUrlField.text.length > 0 && (passwordField.text.length > 0 || tokenField.text.length > 0)
                
                onClicked: {
                    errorLabel.text = "";
                    trilliumApi.testConnection(serverUrlField.text, passwordField.text, tokenField.text);
                }
            }

            BusyIndicator {
                running: trilliumApi.busy
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
