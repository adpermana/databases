import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.2

Window {
    id: latihan
    visible: true
    width: 800; height: 500
    color: "orange"

    Column{
        id: row1
        spacing: 10
        anchors{
            horizontalCenter: parent.horizontalCenter;
            top: parent.top;
            topMargin: 50;
            left: parent.left;
            leftMargin: 50
        }
        Text {
            id: txt1
            text: "Masukkan Teks :"
            font.pointSize: 24
            font.family: "Helvetica"
            color: "white"
        }
        TextField{
            id: data
            width: 650
            height: 60
            font.family: "Courier"
            font.pointSize: 24
            style: TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    radius: 2
                    border.color: "red"
                    border.width: 3
                }
            }
        }
        TextField{
            id: data2
            width: 650
            height: 60
            font.family: "Courier"
            font.pointSize: 24
            style: TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    radius: 2
                    border.color: "red"
                    border.width: 3
                }
            }
        }
        Text {
            id: txt2
            text: "Get data db : "
            font.pointSize: 24
            font.family: "Helvetica"
            color: "white"
        }
        Text {
            id: outText
            text: ""
            font.pointSize: 24
            font.family: "Helvetica"
            color: "white"
        }

        Button{
            id: btnOke
            width: 170
            height: 60
            Text {
                id: okebutton
                anchors.centerIn: parent
                text: "UPDATE"
                font.pointSize: 18
                font.bold: true
                font.family: "Helvetica"
            }
            onClicked: {
                db.update(data.getText(0, data.text.length),
                          data2.getText(0, data.text.length));
                db.read();
            }
        }
        Connections{
            target: db
            onDataFromCpp:{
                outText.text = dataCpp1 + " " +dataCpp2
            }
        }

        Component.onCompleted: db.read()

    }
}

