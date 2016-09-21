import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.2

Window {
    id: contact
    visible: true
    width: 800
    height: 500
    color: "orange"

    Text {
        anchors {
            top: parent.top
            topMargin: 10
            margins: 10
            left: parent.left
            leftMargin: 180
        }

        id: txt2
        text: "Ekstension" + " \t\t\t " + "Nama"
        font.pointSize: 18
        font.family: "Helvetica"
        color: "white"
    }

    Rectangle{
        id: border1
        anchors {
            top: txt2.bottom
            topMargin: 4
            left: parent.left
            leftMargin: 120
        }

        height: 2
        width: 500
        color: "blue"
    }

    ListView {
        id: listContact
        width: 500;
        height: 350
        anchors {
            top: border1.bottom
            topMargin: 10;
            left: parent.left;
            leftMargin: 120
        }
        spacing: 5

        Component {
            id: contactsDelegate
            Rectangle {
                id: wrapper
                width: 500
                height: 30
                color: ListView.isCurrentItem ? "blue" : "orange"
                Text {
                    id: contactInfo
                    text: '\t' + number + ' \t\t\t ' + name
                    color: wrapper.ListView.isCurrentItem ? "orange" : "blue"
                    font.pointSize: 16

                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        parent.ListView.view.currentIndex = index;
                        inputSIP.text = number;
                    }
                }
            }
        }

        model:sqlModel
        delegate: contactsDelegate
        focus: true
    }

    Rectangle{
        id: border2
        anchors {
            top: listContact.bottom
            topMargin: 35
            left: parent.left
            leftMargin: 120
        }

        height: 2
        width: 500
        color: "blue"
    }

    Button{
        id: addContact
        width: 150
        height: 40
        anchors{
            top: border2.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 120
        }

        Text {
            id: okebutton
            anchors.centerIn: parent
            text: "UPDATE"
            font.pointSize: 18
            font.bold: true
            font.family: "Helvetica"
        }
    }

    Text {
        id: inputSIP
        anchors{
            top: border2.bottom
            topMargin: 6
            left: addContact.right
            leftMargin: 10
        }
        text: "db"
        font.pointSize: 18
        color: "white"
    }
}


