import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
Window {
    visible: true
    width: 800
    height: 600
    color: "#121213"
    title: qsTr("Wordle")

    Component.onCompleted: {
           wordle.setTargetWord("close");
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        // Title
        Text {
            text: qsTr("Wordle")
            color: "white"
            font.bold: true
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Display guessed words
        Repeater {
            id: guesses
            model: Math.min(wordle.guessedWords.length, 6)
            anchors.horizontalCenter: parent.horizontalCenter
            Row {
                spacing: 5
                property int outerindex: index
                anchors.horizontalCenter: parent.horizontalCenter
                Repeater {
                    model: 5
                    Rectangle {
                        width: 30
                        height: 30
                        radius:4
                        color: {
                            var letter = wordle.feedbacks[outerindex][model.index];
                            if (letter === "-") {
                                return "gray";
                            } else if (letter === "+") {
                                return "#FFC425";
                            } else {
                                return "#008000";
                            }
                        }
                        Text {
                            anchors.centerIn: parent
                            text: {
                                if (wordle.guessedWords[outerindex] !== undefined) {
                                    return wordle.guessedWords[outerindex][model.index];
                                }
                                return "";
                            }
                            font.pixelSize: 20
                            color: "white"
                        }
                    }
                }
            }
        }


        // Input field for guesses
        TextField {
            id: inputField
            width: 200
            placeholderText: qsTr("Enter your guess")
            anchors.horizontalCenter: parent.horizontalCenter
            enabled: !gameManager.isGameOver()
            onAccepted: {
                if (gameManager.isGameOver()){
                    message.text = "Game Over"
                    return;
                }
                if (text.length === wordle.targetWord.length) {
                    if (wordle.checkGuess(text)) {
                        message.color = "green"
                        message.text = qsTr("Correct!")
                        gameManager.setGameOver(true)
                    }else if(!wordle.isValidGuess(text)){
                        message.color = "red"
                        message.text = qsTr("Not in word list!")
                    }

                    else {
                        message.color = "red"
                        message.text = qsTr("Try again!")
                    }
                    text = ""
                } else {
                    message.color = "red"
                    message.text = qsTr("Guess must be ") + wordle.targetWord.length + qsTr(" letters long!")
                }
            }

        }

        // Message to display feedback
        Text {
            id: message
            text: ""
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            width: 300

            height: 100
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter

            Column {
                spacing: 4
                anchors.centerIn: parent
                Row{
                    spacing: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                    Repeater {
                        model: ["Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"]
                        Button {
                            width:  Math.max(30, children.width)
                            height:  30
                            contentItem: Text {
                                color: "white"
                                text: modelData
                                font.bold: true
                            }

                            background: Rectangle{
                                color: wordle.keyColors[modelData]
                                radius: 4
                            }

                            property color buttonColor: "darkgray"

                            onClicked: {
                                if(modelData == "Del"){
                                    inputField.text = inputField.text.slice(0, -1);
                                }else if(modelData == "Enter"){
                                    inputField.onAccepted();
                                }else{
                                    inputField.text += modelData;
                                }
                            }
                        }
                    }
                }


                Row{

                    spacing: 4

                    anchors.horizontalCenter: parent.horizontalCenter
                    Repeater {
                        model: ["A", "S", "D", "F", "G", "H", "J", "K", "L", "Del"]
                        Button {
                            width:  Math.max(30, children.width)
                            height:  30
                            contentItem: Text {
                                color: "white"
                                text: modelData
                                font.bold: true
                            }

                            background: Rectangle{
                                color: wordle.keyColors[modelData]
                                radius: 4
                            }

                            property color buttonColor: "darkgray"

                            onClicked: {
                                if(modelData == "Del"){
                                    inputField.text = inputField.text.slice(0, -1);
                                }else if(modelData == "Enter"){
                                    inputField.onAccepted();
                                }else{
                                    inputField.text += modelData;
                                }
                            }
                        }
                    }
                }


                Row{
                    spacing: 4

                    anchors.horizontalCenter: parent.horizontalCenter
                    Repeater {
                        model: ["Z", "X", "C", "V", "B", "N", "M", "Enter"]
                        Button {
                            width:  Math.max(30, children.width)
                            height:  30
                            contentItem: Text {
                                color: "white"
                                text: modelData
                                font.bold: true
                            }

                            background: Rectangle{
                                color: wordle.keyColors[modelData]
                                radius: 4
                            }

                            property color buttonColor: "darkgray"

                            onClicked: {
                                if(modelData == "Del"){
                                    inputField.text = inputField.text.slice(0, -1);
                                }else if(modelData == "Enter"){
                                    inputField.onAccepted();
                                }else{
                                    inputField.text += modelData;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Button to start a new game
        Button {
            text: qsTr("New Game")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                wordle.clearGuesses()
                wordle.setTargetWord("")
                message.text = ""
                gameManager.setGameOver(false)
            }
        }
    }
}
