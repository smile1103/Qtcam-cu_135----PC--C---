/*
 * uvc_cu30.qml -- extension settings for other cameras
 * Copyright © 2015  e-con Systems India Pvt. Limited
 *
 * This file is part of Qtcam.
 *
 * Qtcam is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Qtcam is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qtcam. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.0
import QtQuick.Dialogs 1.1
import econ.camera.uvcsettings 1.0
import econ.camera.see3camcu38 1.0
import QtQuick.Layouts 1.1
import cameraenum 1.0

Item {
    width:240
    height:720
    property int defaultNoiseVal: 8
    property int denoiseMin: 0
    property int denoiseMax: 15
    property int qFactorMin: 10
    property int qFactorMax: 96
    property int frameRateMin: 1
    property int frameRateMax: 120
    property int expoCompMin: 8000
    property int expoCompMax: 1000000
    property bool skipUpdateUIOnExpWindowSize: false
    property bool skipUpdateUIOnBurstLength: false
    property bool skipUpdateUIQFactor : false
    property bool skipUpdateUIFrameRate: false
    property bool setButtonClicked: false

    Connections
    {
        target: root
        onTakeScreenShot:
        {
             if(see3camcu38.enableDisableFaceRectangle(false)) {
                root.imageCapture(CommonEnums.BURST_SHOT);
            }
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

    Timer {
         id: burstShotTimer
         interval: 1000
         onTriggered: {
             root.imageCapture(CommonEnums.BURST_SHOT);
             stop()
         }
     }

    // Used when selecting auto exposure in image Quality settings menu
    Timer {
        id: getAutoExpsoureControlValues
        interval: 500
        onTriggered: {
            see3camcu38.getAutoExpROIModeAndWindowSize()
            stop()
        }
    }

    Timer {
        id: getexposureCompFrameRateCtrlTimer
        interval: 500
        onTriggered: {
            see3camcu38.getExposureCompensation()
            see3camcu38.getFrameRateCtrlValue()
            stop()
        }
    }

    Action {
    id: firmwareVersion
    onTriggered:
        {
            getFirmwareVersion()
        }
    }

    Action {
        id: serialNumber
        onTriggered: {
            getSerialNumber()
        }
    }

    ScrollView{
        id: scrollview
        x: 10
        y: 189.5
        width: 257
        height: 500
        style: econscrollViewStyle
        ColumnLayout{
            x:2
            y:5
            spacing:20

            Text {
            id: scene_mode
            text: "--- Scene Mode ---"
            font.pixelSize: 14
            font.family: "Ubuntu"
            color: "#ffffff"
            smooth: true
            Layout.alignment: Qt.AlignCenter
            opacity: 0.50196078431373
            }

            Grid {
                columns: 2
                spacing: 50

                ExclusiveGroup { id: sceneInputGroup }
                RadioButton {
                    id: sceneNormal
                    style:  econRadioButtonStyle
                    text:   qsTr("Normal")                   
                    exclusiveGroup: sceneInputGroup
                    activeFocusOnPress: true
                    onClicked: {
                        see3camcu38.setSceneMode(See3Camcu38.SCENE_NORMAL)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setSceneMode(See3Camcu38.SCENE_NORMAL)
                    }
                }
                RadioButton {
                    id: sceneDoc
                    style:  econRadioButtonStyle
                    text: qsTr("Document")                 
                    exclusiveGroup: sceneInputGroup
                    activeFocusOnPress: true
                    onClicked: {                        
                        see3camcu38.setSceneMode(See3Camcu38.SCENE_DOCUMENT)
                    }
                    Keys.onReturnPressed: {                        
                        see3camcu38.setSceneMode(See3Camcu38.SCENE_DOCUMENT)
                    }

                }

            }
            Row{
                Layout.alignment: Qt.AlignCenter
                Text {
                   id: special_effects
                   text: "--- Special Effects ---"
                   font.pixelSize: 14
                   font.family: "Ubuntu"
                   color: "#ffffff"
                   smooth: true
                   opacity: 0.50196078431373
               }
            }
            Grid {
                x: 23
                y: 235

                columns: 2
                spacing: 15

                ExclusiveGroup { id: effectInputGroup }
                RadioButton {
                    id: rdoEffectNormal
                    style:  econRadioButtonStyle
                    text:   qsTr("Normal")
                    exclusiveGroup: effectInputGroup
                    activeFocusOnPress: true
                    onClicked: {
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_NORMAL)
                    }
                    Keys.onReturnPressed:  {
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_NORMAL)
                    }
                }
                RadioButton {
                    id: rdoEffectBW
                    style:  econRadioButtonStyle
                    text: qsTr("Black and White")                  
                    exclusiveGroup: effectInputGroup
                    activeFocusOnPress: true
                    onClicked: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_BLACK_WHITE)
                    }
                    Keys.onReturnPressed: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_BLACK_WHITE)
                    }
                }
                RadioButton {
                    id: rdoEffectGreyScale
                    style:  econRadioButtonStyle
                    text: qsTr("GreyScale")                  
                    exclusiveGroup: effectInputGroup
                    activeFocusOnPress: true
                    onClicked: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_GREYSCALE)
                    }
                    Keys.onReturnPressed: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_GREYSCALE)
                    }
                }
                RadioButton {
                    id: rdoEffectSketch
                    style:  econRadioButtonStyle
                    text: qsTr("Sketch")                  
                    exclusiveGroup: effectInputGroup
                    activeFocusOnPress: true
                    onClicked: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_SKETCH)
                    }
                    Keys.onReturnPressed: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_SKETCH)
                    }
                }
                RadioButton {
                    id: rdoEffectNegative
                    style:  econRadioButtonStyle
                    text: qsTr("Negative")
                    exclusiveGroup: effectInputGroup
                    activeFocusOnPress: true
                    onClicked: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_NEGATIVE)
                    }
                    Keys.onReturnPressed: {                        
                        see3camcu38.setEffectMode(See3Camcu38.EFFECT_NEGATIVE)
                    }
                }
            }
            Row{
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: roiAutoExpMode
                    text: "--- ROI - Auto Exposure ---"
                    font.pixelSize: 14
                    font.family: "Ubuntu"
                    color: "#ffffff"
                    smooth: true
                    Layout.alignment: Qt.AlignCenter
                    opacity: 0.50196078431373
                }
            }

            Row{
                spacing:38
                ExclusiveGroup { id: roiExpogroup }

                  RadioButton {
                      exclusiveGroup: roiExpogroup
                      id: autoexpFull
                      text: "Full"
                      activeFocusOnPress: true
                      style: econRadioButtonStyle
                      opacity: enabled ? 1 : 0.1
                      // setROIAutoExposure() args:  mode, videoresolnWidth, videoresolnHeight, mouseXCord, mouseYCord, WinSize]
                      // videoresolnWidth, videoresolnHeight, mouseXCord, mouseYCord - these parameters are required only when click in preview]
                      // winSize is required only for manual mode
                      onClicked: {
                          see3camcu38.setROIAutoExposure(See3Camcu38.AutoExpFull, 0, 0, 0, 0, 0);
                          autoExpoWinSizeCombo.enabled = false
                      }
                      Keys.onReturnPressed: {
                          see3camcu38.setROIAutoExposure(See3Camcu38.AutoExpFull, 0, 0, 0, 0, 0);
                          autoExpoWinSizeCombo.enabled = false
                      }
                  }
                  RadioButton {
                      exclusiveGroup: roiExpogroup
                      id: autoexpManual
                      text: "Manual"
                      activeFocusOnPress: true
                      style: econRadioButtonStyle
                      opacity: enabled ? 1 : 0.1
                      onClicked: {                          
                          see3camcu38.setROIAutoExposure(See3Camcu38.AutoExpManual, 0, 0, 0, 0, autoExpoWinSizeCombo.currentText);
                          autoExpoWinSizeCombo.enabled = true
                      }
                      Keys.onReturnPressed: {                          
                          see3camcu38.setROIAutoExposure(See3Camcu38.AutoExpManual, 0, 0, 0, 0, autoExpoWinSizeCombo.currentText);
                          autoExpoWinSizeCombo.enabled = true
                      }
                  }
            }

            ComboBox
            {
                id: autoExpoWinSizeCombo
                enabled: (autoexpManual.enabled && autoexpManual.checked) ? true : false
                opacity: (autoexpManual.enabled && autoexpManual.checked) ? 1 : 0.1
                model: ListModel {
                    ListElement { text: "1" }
                    ListElement { text: "2" }
                    ListElement { text: "3" }
                    ListElement { text: "4" }
                    ListElement { text: "5" }
                    ListElement { text: "6" }
                    ListElement { text: "7" }
                    ListElement { text: "8" }
                }
                activeFocusOnPress: true
                style: econComboBoxStyle
                onCurrentIndexChanged: {                    
                    if(skipUpdateUIOnExpWindowSize){
                        see3camcu38.setROIAutoExposure(See3Camcu38.AutoExpManual, 0, 0, 0, 0, autoExpoWinSizeCombo.currentText)
                    }
                    skipUpdateUIOnExpWindowSize = true
                }
            }            

            Text {
                    id: exposureCompTextTitle
                    text: "--- Exposure Compensation ---"
                    font.pixelSize: 14
                    font.family: "Ubuntu"
                    color: "#ffffff"
                    smooth: true
                    Layout.alignment: Qt.AlignCenter
                    opacity: 0.50196078431373
                }
            Row{
                    spacing: 9
                    Text {
                        id: exposureCompText
                        text: "value(µs)[8000 - 1000000]"
                        font.pixelSize: 14
                        font.family: "Ubuntu"
                        color: "#ffffff"
                        smooth: true
                        width: 80
                        wrapMode: Text.WordWrap
                        opacity: 1
                    }
                    TextField {
                        id: exposureCompValue
                        font.pixelSize: 10
                        font.family: "Ubuntu"
                        smooth: true
                        horizontalAlignment: TextInput.AlignHCenter
                        opacity: 1
                        style: econTextFieldStyle
                        implicitHeight: 25
                        implicitWidth: 80
                        validator: IntValidator {bottom: expoCompMin; top: expoCompMax}
                    }
                    Button {
                        id: exposureCompSet
                        activeFocusOnPress : true
                        text: "Set"
                        style: econButtonStyle
                        enabled: true
                        opacity: 1
                        implicitHeight: 25
                        implicitWidth: 60
                        onClicked: {
                            exposureCompSetButtonClicked()
                        }
                        Keys.onReturnPressed: {
                            exposureCompSetButtonClicked()
                        }
                    }
            }
            Row{
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: denoiseText
                    text: "--- De-Noise Control ---"
                    font.pixelSize: 14
                    font.family: "Ubuntu"
                    color: "#ffffff"
                    smooth: true
                    opacity: 0.50196078431373
                }
            }

            Row{
                spacing: 30
                Slider {
                    activeFocusOnPress: true
                    updateValueWhileDragging: false
                    id: deNoiseSlider
                    width: 150
                    stepSize: 1
                    style:econSliderStyle
                    minimumValue: denoiseMin
                    maximumValue: denoiseMax
                    onValueChanged:  {
                        deNoiseTextField.text = deNoiseSlider.value
                        see3camcu38.setDenoiseValue(deNoiseSlider.value)
                    }
                }
                TextField {
                    id: deNoiseTextField
                    text: deNoiseSlider.value
                    font.pixelSize: 10
                    font.family: "Ubuntu"
                    smooth: true
                    horizontalAlignment: TextInput.AlignHCenter
                    style: econTextFieldStyle
                    validator: IntValidator {bottom: deNoiseSlider.minimumValue; top: deNoiseSlider.maximumValue}
                    onTextChanged: {
                        if(text.length > 0){
                            deNoiseSlider.value = deNoiseTextField.text                            
                        }
                    }
                }
            }
            Row{
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: imgCapText
                    text: "--- Image Capture ---"
                    font.pixelSize: 14
                    font.family: "Ubuntu"
                    color: "#ffffff"
                    smooth: true
                    Layout.alignment: Qt.AlignCenter
                    opacity: 0.50196078431373
                }
            }
            Text {
                id: burstLength
                text: "Burst Length :"
                font.pixelSize: 14
                font.family: "Ubuntu"
                color: "#ffffff"
                smooth: true
                opacity: 1
            }
            ComboBox
            {
                id: burstLengthCombo
                opacity: 1
                enabled: true
                model: ListModel {
                    ListElement { text: "1" }
                    ListElement { text: "2" }
                    ListElement { text: "3" }
                    ListElement { text: "4" }
                    ListElement { text: "5" }
                }
                activeFocusOnPress: true
                style: econComboBoxStyle
                onCurrentIndexChanged: {
                    root.stillBurstLength(burstLengthCombo.currentIndex + 1) // combobox index starts from 0
                    if(skipUpdateUIOnBurstLength){
                        see3camcu38.setBurstLength(burstLengthCombo.currentText)
                    }
                    skipUpdateUIOnBurstLength = true                    
                }
            }
            Row{
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: qFactorText
                    text: "--- Q Factor ---"
                    font.pixelSize: 14
                    font.family: "Ubuntu"
                    color: "#ffffff"
                    smooth: true
                    Layout.alignment: Qt.AlignCenter
                    opacity: 0.50196078431373
                }
            }

            Row{
                spacing: 35
                Slider {
                    activeFocusOnPress: true
                    updateValueWhileDragging: false
                    id: qFactorSlider
                    width: 150
                    stepSize: 1
                    style:econSliderStyle
                    minimumValue: qFactorMin
                    maximumValue: qFactorMax
                    onValueChanged:  {
                        qFactorTextField.text = qFactorSlider.value                        
                        if(skipUpdateUIQFactor){
                            see3camcu38.setQFactor(qFactorSlider.value)
                        }
                        skipUpdateUIQFactor = true
                    }
                }
                TextField {
                    id: qFactorTextField
                    text: qFactorSlider.value
                    font.pixelSize: 10
                    font.family: "Ubuntu"
                    smooth: true
                    horizontalAlignment: TextInput.AlignHCenter
                    style: econTextFieldStyle
                    validator: IntValidator {bottom: qFactorSlider.minimumValue; top: qFactorSlider.maximumValue}
                    onTextChanged: {
                        if(text.length > 0){
                            qFactorSlider.value = qFactorTextField.text                            
                        }
                    }
                }
            }
            Row{
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: frameRateText
                    text: "--- Frame Rate Control ---"
                    font.pixelSize: 14
                    font.family: "Ubuntu"
                    color: "#ffffff"
                    smooth: true
                    Layout.alignment: Qt.AlignCenter
                    opacity: 0.50196078431373
                }
            }
            Row{
                spacing: 35
                Slider {
                    activeFocusOnPress: true
                    updateValueWhileDragging: false
                    id: frameRateSlider
                    width: 150
                    stepSize: 1
                    style:econSliderStyle
                    minimumValue: frameRateMin
                    maximumValue: frameRateMax
                    onValueChanged:  {
                        frameRateTextField.text = frameRateSlider.value
                        if(skipUpdateUIFrameRate){
                            see3camcu38.setFrameRateCtrlValue(frameRateSlider.value)
                        }
                        skipUpdateUIFrameRate = true                        
                    }
                }
                TextField {
                    id: frameRateTextField
                    text: frameRateSlider.value
                    font.pixelSize: 10
                    font.family: "Ubuntu"
                    smooth: true
                    horizontalAlignment: TextInput.AlignHCenter
                    style: econTextFieldStyle
                    validator: IntValidator {bottom: frameRateSlider.minimumValue; top: frameRateSlider.maximumValue}
                    onTextChanged: {
                        if(text.length > 0){
                            frameRateSlider.value = frameRateTextField.text                            
                        }
                    }
                }
            }

            Row{
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: flipText
                    text: "--- Flip Control ---"
                    font.pixelSize: 14
                    font.family: "Ubuntu"
                    color: "#ffffff"
                    smooth: true
                    opacity: 0.50196078431373
                }
            }
            Row{
                spacing: 55
                CheckBox {
                    id: flipCtrlHorizotal
                    activeFocusOnPress : true
                    text: "Horizontal"
                    style: econCheckBoxStyle
                    onClicked:{
                        see3camcu38.setOrientation(flipCtrlHorizotal.checked, flipCtrlVertical.checked)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setOrientation(flipCtrlHorizotal.checked, flipCtrlVertical.checked)
                    }
                }
                CheckBox {
                    id: flipCtrlVertical
                    activeFocusOnPress : true
                    text: "Vertical"
                    style: econCheckBoxStyle
                    onClicked:{
                        see3camcu38.setOrientation(flipCtrlHorizotal.checked, flipCtrlVertical.checked)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setOrientation(flipCtrlHorizotal.checked, flipCtrlVertical.checked)
                    }
                }
            }
            Text {
                id: faceDetectionText
                text: "--- Face Detection ---"
                font.pixelSize: 14
                font.family: "Ubuntu"
                color: "#ffffff"
                smooth: true
                Layout.alignment: Qt.AlignCenter
                opacity: 0.50196078431373
            }

            Row{
                spacing: 62
                ExclusiveGroup { id: faceRectGroup }
                RadioButton {
                    exclusiveGroup: faceRectGroup
                    id: faceRectEnable
                    text: "Enable"
                    activeFocusOnPress: true
                    style: econRadioButtonStyle
                    onClicked:{
                        see3camcu38.setFaceDetectionRect(true, faceDetectEmbedData.checked, overlayRect.checked)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setFaceDetectionRect(true, faceDetectEmbedData.checked, overlayRect.checked)
                    }
                }
                RadioButton {
                    exclusiveGroup: faceRectGroup
                    id:faceRectDisable
                    text: "Disable"
                    activeFocusOnPress: true
                    style: econRadioButtonStyle
                    onClicked: {
                        see3camcu38.setFaceDetectionRect(false, faceDetectEmbedData.checked, overlayRect.checked)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setFaceDetectionRect(false, faceDetectEmbedData.checked, overlayRect.checked)
                    }
                }
            }
            Row{
                spacing: 5
                CheckBox {
                    id: faceDetectEmbedData
                    activeFocusOnPress : true
                    text: "Embed Data"                  
                    style: econCheckBoxTextWrapModeStyle
                    enabled: faceRectEnable.checked ? true : false
                    opacity: enabled ? 1 : 0.1
                    onClicked:{
                        enableFaceDetectEmbedData()
                    }
                    Keys.onReturnPressed: {
                        enableFaceDetectEmbedData()                        
                    }
                }
                CheckBox {
                    id: overlayRect
                    activeFocusOnPress : true
                    text: "Overlay Rectangle"
                    style: econCheckBoxTextWrapModeStyle
                    enabled: faceRectEnable.checked ? true : false
                    opacity: enabled ? 1 : 0.1
                    onClicked:{
                        see3camcu38.setFaceDetectionRect(faceRectEnable.checked, faceDetectEmbedData.checked, checked)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setFaceDetectionRect(faceRectEnable.checked, faceDetectEmbedData.checked, checked)
                    }
                }
            }
            Text {
                id: smileDetectionText
                text: "--- Smile Detection ---"
                font.pixelSize: 14
                font.family: "Ubuntu"
                color: "#ffffff"
                smooth: true
                Layout.alignment: Qt.AlignCenter
                opacity: 0.50196078431373
            }
            Row{
                spacing: 62
                ExclusiveGroup { id: smileDetectGroup }
                RadioButton {
                    exclusiveGroup: smileDetectGroup
                    id: smileDetectEnable
                    text: "Enable"
                    activeFocusOnPress: true
                    style: econRadioButtonStyle
                    onClicked:{
                        see3camcu38.setSmileDetection(true, smileDetectEmbedData.checked)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setSmileDetection(true, smileDetectEmbedData.checked)
                    }
                }
                RadioButton {
                    exclusiveGroup: smileDetectGroup
                    id:smileDetectDisable
                    text: "Disable"
                    activeFocusOnPress: true
                    style: econRadioButtonStyle
                    onClicked: {
                        see3camcu38.setSmileDetection(false, smileDetectEmbedData.checked)
                    }
                    Keys.onReturnPressed: {
                        see3camcu38.setSmileDetection(false, smileDetectEmbedData.checked)
                    }
                }
            }
            Row{
                spacing: 5
                CheckBox {
                    id: smileDetectEmbedData
                    activeFocusOnPress : true
                    text: "Embed Data"                  
                    style: econCheckBoxStyle
                    enabled: smileDetectEnable.checked ? true : false
                    opacity: enabled ? 1 : 0.1
                    onClicked:{
                        enableSmileDetectEmbedData()
                    }
                    Keys.onReturnPressed: {
                        enableSmileDetectEmbedData()
                    }
                }
            }
            Text{
                id: flashCtrlText
                x: 85
                y: 200
                text: "--- Flash Control ---"
                font.pixelSize: 14
                font.family: "Ubuntu"
                color: "#ffffff"
                smooth: true
                Layout.alignment: Qt.AlignCenter
                opacity: 0.50196078431373
            }

            RowLayout{
                x:25
                y:230
                spacing: 25
                ExclusiveGroup { id: flashGrp }
                Column{
                    RadioButton {
                        exclusiveGroup: flashGrp
                        checked: false
                        id: flashModeStrobe
                        text: "Strobe"
                        activeFocusOnPress: true
                        style: econRadioButtonStyle
                        onClicked: {
                            see3camcu38.setFlashState(See3Camcu38.FLASHMODE_STROBE)
                        }
                        Keys.onReturnPressed: {
                            see3camcu38.setFlashState(See3Camcu38.FLASHMODE_STROBE)
                        }
                    }
                }
                Column{
                    RadioButton {
                        exclusiveGroup: flashGrp
                        checked: false
                        id: flashModeTorch
                        text: "Torch"
                        activeFocusOnPress: true
                        style: econRadioButtonStyle
                        onClicked: {
                            see3camcu38.setFlashState(See3Camcu38.FLASHMODE_TORCH)
                        }
                        Keys.onReturnPressed: {
                            see3camcu38.setFlashState(See3Camcu38.FLASHMODE_TORCH)
                        }
                    }
                }
                Column{
                    RadioButton {
                        exclusiveGroup: flashGrp
                        checked: false
                        id: flashModeOff
                        text: "OFF"
                        activeFocusOnPress: true
                        style: econRadioButtonStyle
                        onClicked: {
                            see3camcu38.setFlashState(See3Camcu38.FLASHMODE_OFF)
                        }
                        Keys.onReturnPressed: {
                            see3camcu38.setFlashState(See3Camcu38.FLASHMODE_OFF)
                        }
                    }
                }
            }
            Row{
                Layout.alignment: Qt.AlignCenter
                Button {
                    id: defaultValue
                    opacity: 1
                    activeFocusOnPress : true
                    text: "Default"
                    tooltip: "Click to set default values"
                    style: econButtonStyle
                    onClicked: {
                        setDefaultValues()
                    }
                    Keys.onReturnPressed: {
                        setDefaultValues()
                    }
                }
            }
            Row{
                Button {
                    id: f_wversion_selected130
                    opacity: 1
                    action: firmwareVersion
                    activeFocusOnPress : true
                    tooltip: "Click to view the firmware version of the camera"
                    style: ButtonStyle {
                        background: Rectangle {
                        border.width: control.activeFocus ? 3 :0
                        color: "#222021"
                        border.color: control.activeFocus ? "#ffffff" : "#222021"
                        radius: 5
                        }
                        label: Image {
                        source: "images/f_wversion_selected.png"
                        }
                    }
                    Keys.onReturnPressed: {
                    getFirmwareVersion()
                    }
                }
                Button {
                    id: serial_no_selected
                    opacity: 1
                    action: serialNumber
                    activeFocusOnPress : true
                    tooltip: "Click to view the Serial Number"
                    style: ButtonStyle {
                        background: Rectangle {
                        border.width: control.activeFocus ? 3 :0
                        color: "#222021"
                        border.color: control.activeFocus ? "#ffffff" : "#222021"
                        radius: 5
                        }
                        label: Image {
                        source: "images/serial_no_selected.png"
                        }
                    }
                    Keys.onReturnPressed: {
                    getSerialNumber()
                    }
                }
            }
	    Row{
                Layout.alignment: Qt.AlignCenter
                Button {
                    id: dummybutton
                    opacity: 0
		    enabled: false
                }
            }
        }
    }

    Uvccamera {
        id: uvccamera
        onTitleTextChanged: {
            messageDialog.title = _title.toString()
            messageDialog.text = _text.toString()
            messageDialog.open()
        }
        onSerialNumber:{
            messageDialog.title = qsTr("Serial Number")
            messageDialog.text = serialNumber;
        }
    }

    Component {
        id: econCheckBoxStyle
        CheckBoxStyle {
            label: Text {
                text: control.text
                font.pixelSize: 14
                font.family: "Ubuntu"
                color: "#ffffff"
                smooth: true
                opacity: 1
            }
            background: Rectangle {
                color: "#222021"
                border.color: control.activeFocus ? "#ffffff" : "#222021"
            }
        }
    }

    Component {
        id: econComboBoxStyle
        ComboBoxStyle {
            background: Image {
                id: burstLengthCombo_bkgrnd
                source: "../../Views/images/device_box.png"
                Rectangle {
                    width: burstLengthCombo_bkgrnd.sourceSize.width  - 28
                    height: burstLengthCombo_bkgrnd.sourceSize.height
                    color: "#222021"
                    border.color: "white"
                    border.width: control.activeFocus ? 3 : 1
                    radius: control.activeFocus ? 5 : 0
                }
            }
            label:  Text{
                anchors.fill: parent
                color: "#ffffff"
                elide: Text.ElideRight
                text: control.currentText
                verticalAlignment: Text.AlignVCenter
                maximumLineCount: 1
                font.family: "Ubuntu"
                font.pixelSize: 14
            }
        }
    }

    Component {
        id: econRadioButtonStyle
        RadioButtonStyle {
            label: Text {
                text: control.text
                font.pixelSize: 14
                font.family: "Ubuntu"
                color: "#ffffff"
                smooth: true
                opacity: 1
            }
            background: Rectangle {
                color: "#222021"
                border.color: control.activeFocus ? "#ffffff" : "#222021"
            }
        }
    }

    Component {
        id: econTextFieldStyle
        TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 2
                implicitWidth: 50
                implicitHeight: 20
                border.color: "#333"
                border.width: 2
                y: 1
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
    }}

    Component {
        id: econButtonStyle
        ButtonStyle {
            background: Rectangle {
                implicitHeight: 38
                implicitWidth: 104
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
        id: econCheckBoxTextWrapModeStyle
        CheckBoxStyle {
            label: Text {
                text: control.text
                font.pixelSize: 14
                font.family: "Ubuntu"
                color: "#ffffff"
                smooth: true
                opacity: 1
                width: 100
                wrapMode: Text.WordWrap
            }
            background: Rectangle {
                color: "#222021"
                border.color: control.activeFocus ? "#ffffff" : "#222021"
            }
        }
    }


    See3Camcu38 {
        id: see3camcu38
        onFlashModeValue:{
            currentFlashMode(flashMode)
        }
        onSendEffectMode:{
            switch(effectMode){
            case See3Camcu38.EFFECT_NORMAL:
                rdoEffectNormal.checked = true
                break;
            case See3Camcu38.EFFECT_BLACK_WHITE:
                rdoEffectBW.checked = true
                break;
            case See3Camcu38.EFFECT_GREYSCALE:
                rdoEffectGreyScale.checked = true
                break;
            case See3Camcu38.EFFECT_SKETCH:
                rdoEffectSketch.checked = true
                break;
            case See3Camcu38.EFFECT_NEGATIVE:
                rdoEffectNegative.checked = true
                break;
            }
        }
        onBurstLengthValue:{
            skipUpdateUIOnBurstLength = false
            burstLengthCombo.currentIndex = burstLength - 1
        }
        onSendDenoiseValue:{
            deNoiseSlider.value = denoiseValue
        }
        onSceneModeValue: {
            currentSceneMode(sceneMode)
        }
        onQFactorValue:{
          skipUpdateUIQFactor = false
          qFactorSlider.value = qFactor
          skipUpdateUIQFactor = true
        }
        onRoiAutoExpModeValue:{
            currentROIAutoExposureMode(roiMode, winSize)
        }

        onFaceDetectModeValue:{
            updateFaceDetectModeUI(faceDetectMode, faceDetectEmbedDataValue, faceDetectOverlayRect)
        }

        onSmileDetectModeValue:{
            updateSmileDetectModeUI(smileDetectMode, smileDetectEmbedDataValue)
        }

        onFlipMirrorModeChanged:{
            currentFlipMirrorMode(flipMirrorMode)
        }
        onExposureCompValueReceived:{
            exposureCompValue.text = exposureCompensation
        }
        onFrameRateCtrlValueReceived:{
            skipUpdateUIFrameRate = false
            frameRateSlider.value = frameRateCtrlValue
            skipUpdateUIFrameRate = true
        }
        onIndicateCommandStatus:{
            if(setButtonClicked){
                displayMessageBox(title, text)
                setButtonClicked = false
            }
        }

        onIndicateExposureValueRangeFailure:{
            if(setButtonClicked){
                displayMessageBox(title, text)
                setButtonClicked = false
                see3camcu38.getExposureCompensation()
            }
        }      
    }


    Component.onCompleted:{        
        getCameraValues()
    }

    function displayMessageBox(title, text){
        messageDialog.title = qsTr(title)
        messageDialog.text = qsTr(text)
        messageDialog.open()
    }
    // current ROI auto exposure mode
    function currentROIAutoExposureMode(roiMode, winSize){       
        switch(roiMode){
            case See3Camcu38.AutoExpFull:
                autoexpFull.checked = true
                autoExpoWinSizeCombo.enabled = false
                break
            case See3Camcu38.AutoExpManual:
                skipUpdateUIOnExpWindowSize = false
                autoexpManual.checked = true
                // If window size is got from camera is 0 then set window size to 1 in UI
                if(winSize == 0){
                    autoExpoWinSizeCombo.currentIndex = 0
                }else
                    autoExpoWinSizeCombo.currentIndex = winSize-1
                break
            case See3Camcu38.AutoExpDisabled:
                autoexpFull.enabled = false
                autoexpManual.enabled = false
                autoExpoWinSizeCombo.enabled = false
                break
        }
    }

    function currentFlashMode(mode){
        switch(mode){
        case See3Camcu38.FLASHMODE_TORCH:
            flashModeTorch.checked = true
            break;
        case See3Camcu38.FLASHMODE_STROBE:
            flashModeStrobe.checked = true
            break;
        case See3Camcu38.FLASHMODE_OFF:
            flashModeOff.checked = true
            break;
        }
    }

    function currentFlipMirrorMode(mode)
    {
        switch(mode)
        {
            case See3Camcu38.FLIP_ON_MIRROR_ON:
                 flipCtrlVertical.checked = true
                 flipCtrlHorizotal.checked = true
                break;
            case See3Camcu38.FLIP_OFF_MIRROR_ON:
                flipCtrlVertical.checked = true
                flipCtrlHorizotal.checked = false
                break;
            case See3Camcu38.FLIP_ON_MIRROR_OFF:
                 flipCtrlVertical.checked = false
                 flipCtrlHorizotal.checked = true
                break;
            case See3Camcu38.FLIP_OFF_MIRROR_OFF:
                flipCtrlVertical.checked = false
                flipCtrlHorizotal.checked = false
                break;
        }
    }


    function updateFaceDetectModeUI(faceDetectMode, faceDetectEmbedDataValue, faceDetectOverlayRect){        
        if(faceDetectMode == See3Camcu38.FaceRectEnable){
            faceRectEnable.checked = true
            if(faceDetectEmbedDataValue == See3Camcu38.FaceDetectEmbedDataEnable){
                faceDetectEmbedData.checked = true
            }
            if(faceDetectOverlayRect == See3Camcu38.FaceDetectOverlayRectEnable){
                overlayRect.checked = true
            }
        }else if(faceDetectMode == See3Camcu38.FaceRectDisable){
            faceRectDisable.checked = true
            if(faceDetectEmbedDataValue == See3Camcu38.FaceDetectEmbedDataEnable){
                faceDetectEmbedData.checked = true
            }else{
                faceDetectEmbedData.checked = false
            }
            if(faceDetectOverlayRect == See3Camcu38.FaceDetectOverlayRectEnable){
                overlayRect.checked = true
            }else{
                overlayRect.checked = false
            }
        }
    }

    function updateSmileDetectModeUI(smileDetectMode, smileDetectEmbedDataValue){
        if(smileDetectMode == See3Camcu38.SmileDetectEnable){
            smileDetectEnable.checked = true
            if(smileDetectEmbedDataValue == See3Camcu38.SmileDetectEmbedDataEnable){
                smileDetectEmbedData.checked = true
            }else{
                smileDetectEmbedData.checked = false
            }
        }else if(smileDetectMode == See3Camcu38.SmileDetectDisable){
            smileDetectDisable.checked = true
            if(smileDetectEmbedDataValue == See3Camcu38.SmileDetectEmbedDataEnable){
                smileDetectEmbedData.checked = true
            }else{
                smileDetectEmbedData.checked = false
            }
        }
    }

    function enableFaceDetectEmbedData(){
        if(see3camcu38.setFaceDetectionRect(faceRectEnable.checked, faceDetectEmbedData.checked, overlayRect.checked)){
            if(faceDetectEmbedData.checked){
                displayMessageBox(qsTr("Status"),qsTr("The last part of the frame will be replaced by face data.Refer document See3CAM_CU38_Conversa_FaceDetection for more details"))
            }
        }        
    }

    function exposureCompSetButtonClicked(){
        exposureCompSet.enabled = false
        setButtonClicked = true
        see3camcu38.setExposureCompensation(exposureCompValue.text)
        exposureCompSet.enabled = true        
    }

    function enableSmileDetectEmbedData(){
        setButtonClicked = false
        if(see3camcu38.setSmileDetection(true, smileDetectEmbedData.checked)){
            if(smileDetectEmbedData.checked){
                messageDialog.title = qsTr("Status")
                messageDialog.text = qsTr("The last part of the frame will be replaced by smile data.Refer document See3CAM_CU38_Conversa_Face_and_Smile_Detection for more details")
                messageDialog.open()
            }
        }
    }

    function enableDisableAutoExposureControls(autoExposureSelect){
        if(autoExposureSelect){
            autoexpManual.enabled = true
            autoexpFull.enabled = true           
            if(autoexpManual.checked)
                autoExpoWinSizeCombo.enabled = true
            if(autoexpFull.checked)
                autoExpoWinSizeCombo.enabled = false
            autoexpManual.opacity = 1
            autoexpFull.opacity = 1            
            exposureCompValue.enabled = true
            exposureCompValue.opacity = 1
            exposureCompSet.enabled = true
            exposureCompSet.opacity = 1
            exposureCompText.opacity = 1
        }else{
            autoexpManual.enabled = false
            autoexpFull.enabled = false            
            autoExpoWinSizeCombo.enabled = false
            autoexpManual.opacity = 0.1
            autoexpFull.opacity = 0.1            
            exposureCompValue.enabled = false
            exposureCompValue.opacity = 0.1
            exposureCompSet.enabled = false
            exposureCompSet.opacity = 0.1
            exposureCompText.opacity = 0.1
        }
        getAutoExpsoureControlValues.start()
    }

    function currentSceneMode(mode)
    {
        switch(mode)
        {
            case See3Camcu38.SCENE_NORMAL:
                sceneNormal.checked = true
                break;
            case See3Camcu38.SCENE_DOCUMENT:
                sceneDoc.checked = true
                break;
        }
    }

    function getFirmwareVersion() {
        uvccamera.getFirmWareVersion()
    }

    function getSerialNumber() {
        uvccamera.getSerialNumber()
        messageDialog.open()
    }

    function setDefaultValues(){
        defaultValue.enabled = false //To avoid multiple clicks over Default button
        see3camcu38.setToDefault()
        getCameraValues()
        defaultValue.enabled = true
    }

    function getCameraValues(){
        see3camcu38.getEffectMode()
        see3camcu38.getDenoiseValue()
        see3camcu38.getSceneMode()
        see3camcu38.getAutoExpROIModeAndWindowSize()
        see3camcu38.getBurstLength()
        see3camcu38.getQFactor()
        see3camcu38.getOrientation()
        see3camcu38.getFrameRateCtrlValue()
        see3camcu38.getExposureCompensation()
        see3camcu38.getFaceDetectMode()
        see3camcu38.getSmileDetectMode()
        see3camcu38.getFlashState()
    }

    Connections{
         target: root
         onMouseRightClicked:{
             if(autoexpManual.enabled && autoexpManual.checked){
                see3camcu38.setROIAutoExposure(See3Camcu38.AutoExpManual, width, height, x, y, autoExpoWinSizeCombo.currentText)
             }
         }
         onAutoExposureSelected:{
             enableDisableAutoExposureControls(autoExposureSelect)
         }
         onEnableFaceRectafterBurst:{
           see3camcu38.enableDisableFaceRectangle(true)
         }
         onBeforeRecordVideo:{
            see3camcu38.enableDisableFaceRectangle(false)
         }
         onAfterRecordVideo:{
            see3camcu38.enableDisableFaceRectangle(true)
         }
         onVideoResolutionChanged:{
             getexposureCompFrameRateCtrlTimer.start()
         }
         onPreviewFPSChanged:{
             getexposureCompFrameRateCtrlTimer.start()
         }
         onVideoColorSpaceChanged:{
             getexposureCompFrameRateCtrlTimer.start()
         }
    }
}



