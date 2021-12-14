import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import cameraenum 1.0
import econ.camera.ecam82_usb 1.0

Item {

    Connections
    {
        target: root
        onTakeScreenShot:
        {
            root.imageCapture(CommonEnums.SNAP_SHOT);
        }
        onGetVideoPinStatus:
        {
            root.enableVideoPin(true);
        }
        onGetStillImageFormats:
        {
            var stillImageFormat = []
            stillImageFormat.push("jpg")
            stillImageFormat.push("bmp")
            stillImageFormat.push("raw")
            stillImageFormat.push("png")
            root.insertStillImageFormat(stillImageFormat);
        }
    }
    ScrollView
    {
        id: scrollview
        x: 10
        y: 189.5
        width: 257
        height: 500
        style: econscrollViewStyle
        ColumnLayout
        {
            x:2
            y:5
            spacing:20
            Row{
                spacing: 25
                Button{
                        id: dummy
                        opacity: 0
                }
                Button
                {
                    id: f_wversion_selected
                    opacity: 1
                    activeFocusOnPress : true
                    text: "F/W Version"
                    tooltip: "Click to view the firmware version of the camera"
                    style: econButtonStyle
                    onClicked:
                    {
                        ecam82USBId.readFirmwareVersion()
                    }
                    Keys.onReturnPressed:
                    {
                        ecam82USBId.readFirmwareVersion()
                    }
                }//END of firmware Button
            }
        }
    }

    function displayMessageBox(title, text)
    {
        messageDialog.title = qsTr(title)
        messageDialog.text = qsTr(text)
        messageDialog.open()
    }

    Ecam82USB {
        id:ecam82USBId

        onTitleTextChanged:
        {
            displayMessageBox(qsTr(_title), qsTr(_text))
        }
    }

    Component {
        id: econButtonStyle
        ButtonStyle {
            background: Rectangle {
                implicitHeight: 38
                implicitWidth: 154
                border.width: control.activeFocus ? 3 :0
                color: "#e76943"
                border.color: control.activeFocus ? "#ffffff" : "#222021"
                radius: control.activeFocus ? 5 : 0
            }
            label: Text {
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Ubuntu"
                font.pointSize: 10
                text: control.text
            }
        }
    }

    Component {
        id: econscrollViewStyle
        ScrollViewStyle {
            scrollToClickedPosition: true
            handle: Image {
                id: scrollhandle
                source: "images/scroller.png"
            }
            scrollBarBackground: Image {
                id: scrollStyle
                source: "images/Scroller_bg.png"
            }
            incrementControl: Image {
                id: increment
                source: "images/down_arrow.png"
            }
            decrementControl: Image {
                id: decrement
                source: "images/up_arrow.png"
            }
        }
    }

    Component.onCompleted:
    {
        ecam82USBId.initUVCExtensionUnit(root.vidstreamObj)
    }
    Component.onDestruction:{
        ecam82USBId.deInitUVCExtensionUnit()
    }
}
