/*
 * see3cam_cu38.h -- Handling special feature of seecamcu130 camera
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
#ifndef SEE3CAM_CU38_H
#define SEE3CAM_CU38_H

#include <QObject>
#include "uvccamera.h"

#define CAMERA_CONTROL_CU38     0x9A

#define EXPOSURECOMP_MIN 8000
#define EXPOSURECOMP_MAX 1000000

#define SMILE_THRESHOLD_MIN 40
#define SMILE_THRESHOLD_MAX 75
#define DEFAULT_SMILE_THRESHOLD 40

#define GET_SPECIAL_EFFECT_CU38 0x03
#define SET_SPECIAL_EFFECT_CU38 0x04

#define SET_ORIENTATION_CU38    0x0E
#define GET_ORIENTATION_CU38    0x0D
#define SET_ORIENTATION_BOTHFLIP_ENABLE_CU38    0x03
#define SET_ORIENTATION_HORZFLIP_CU38           0x01
#define SET_ORIENTATION_VERTFLIP_CU38           0x02
#define SET_ORIENTATION_BOTHFLIP_DISABLE_CU38   0x00

#define SPECIAL_EFFECT_NORMAL       0x01
#define SPECIAL_EFFECT_BW           0x04
#define SPECIAL_EFFECT_GRAYSCALE    0x07
#define SPECIAL_EFFECT_NEGATIVE     0x08
#define SPECIAL_EFFECT_SKETCH       0x10

#define SET_BURST_LENGTH_CU38       0x0A
#define GET_BURST_LENGTH_CU38      0x09

#define GET_SCENEMODE_CU38          0x01
#define SET_SCENEMODE_CU38          0x02

#define GET_Q_FACTOR_CU38           0x0B
#define SET_Q_FACTOR_CU38          0x0C

#define SET_FRAME_RATE_CU38         0x16
#define GET_FRAME_RATE_CU38         0x15

#define SET_EXPOSURE_COMPENSATION_CU38  0x14
#define GET_EXPOSURE_COMPENSATION_CU38  0x13

#define SET_DENOISE_CONTROL_CU38  0x06
#define GET_DENOISE_CONTROL_CU38  0x05

#define SET_EXP_ROI_MODE_CU38       0x08
#define GET_EXP_ROI_MODE_CU38       0x07

#define SET_FACE_DETECT_RECT_CU38            0x10
#define GET_FACE_DETECT_RECT_CU38           0x0F
#define ENABLE_FACE_RECT_CU38                0x01
#define DISABLE_FACE_RECT_CU38              0x00
#define ENABLE_EMBED_DATA_CU38               0x01
#define DISABLE_EMBED_DATA_CU38              0x00
#define ENABLE_OVERLAY_RECT_CU38             0x01
#define DISABLE_OVERLAY_RECT_CU38            0x00

#define SET_SMILE_DETECTION_CU38             0x12
#define GET_SMILE_DETECTION_CU38             0x11
#define ENABLE_SMILE_DETECT_CU38             0x01
#define DISABLE_SMILE_DETECT_CU38            0x00


#define SET_TO_DEFAULT_CU38                  0xFF

#define ENABLE_DISABLE_MODE_FACE_RECTANGLE_CU38 0x17
#define ENABLE_FACE_RECTANGLE_CU38             0x01
#define DISABLE_FACE_RECTANGLE_CU38             0x00

#define SETFLASH_STATUS_CU38 0x19
#define GETFLASH_STATUS_CU38 0x18


class See3CAM_CU38 : public QObject
{
    Q_OBJECT

private:
    unsigned char g_out_packet_buf[BUFFER_LENGTH];
    unsigned char g_in_packet_buf[BUFFER_LENGTH];
    uvccamera uvc;

    void initializeBuffers();

public:
    explicit See3CAM_CU38(QObject *parent = 0);

    enum specialEffects {
        EFFECT_NORMAL = 0x01,
        EFFECT_BLACK_WHITE = 0x04,
        EFFECT_GREYSCALE = 0x07,
        EFFECT_SKETCH = 0x10,
        EFFECT_NEGATIVE = 0x08
    };

    Q_ENUMS(specialEffects)

    enum sceneModes {
        SCENE_NORMAL = 0x01,
        SCENE_DOCUMENT = 0x0C
    };
    Q_ENUMS(sceneModes)

    enum camROIAutoExpMode {
        AutoExpFace = 0x00,
        AutoExpFull = 0x01,
        AutoExpManual = 0x02,
        AutoExpDisabled = 0x03
    };
    Q_ENUMS(camROIAutoExpMode)

    enum flipMirrorControls{
        FLIP_OFF_MIRROR_OFF = 0x00,
        FLIP_ON_MIRROR_OFF  = 0x01,
        FLIP_OFF_MIRROR_ON  = 0x02,
        FLIP_ON_MIRROR_ON   = 0x03
    };
    Q_ENUMS(flipMirrorControls)

    enum camFaceRectMode {
        FaceRectEnable = 0x01,
        FaceRectDisable = 0x00
    };
    Q_ENUMS(camFaceRectMode)

    enum camFaceDetectEmbedDataMode {
        FaceDetectEmbedDataEnable = 0x01,
        FaceDetectEmbedDataDisable = 0x00
    };
    Q_ENUMS(camFaceDetectEmbedDataMode)

    enum camFaceDetectOverlayRect {
        FaceDetectOverlayRectEnable = 0x01,
        FaceDetectOverlayRectDisable = 0x00
    };
    Q_ENUMS(camFaceDetectOverlayRect)

   enum flashStateValues{
        FLASHMODE_OFF = 0x00,
        FLASHMODE_TORCH = 0x01,
        FLASHMODE_STROBE = 0x02,
    };
    Q_ENUMS(flashStateValues)

   enum camSmileDetectMode {
       SmileDetectEnable = 0x01,
       SmileDetectDisable = 0x00
   };
   Q_ENUMS(camSmileDetectMode)

   enum camSmileDetectEmbedDataMode {
       SmileDetectEmbedDataEnable = 0x01,
       SmileDetectEmbedDataDisable = 0x00
   };
   Q_ENUMS(camSmileDetectEmbedDataMode)

signals:
    void sendEffectMode(uint effectMode);
    void sendDenoiseValue(uint denoiseValue);
    void sceneModeValue(uint sceneMode);
    void roiAutoExpModeValue(uint roiMode, uint winSize);
    void burstLengthValue(uint burstLength);
    void qFactorValue(uint qFactor);
    void flipMirrorModeChanged(uint flipMirrorMode);
    void frameRateCtrlValueReceived(uint frameRateCtrlValue);
    void indicateCommandStatus(QString title, QString text);    
    void indicateExposureValueRangeFailure(QString title, QString text);
    void exposureCompValueReceived(uint exposureCompensation);
    void faceDetectModeValue(uint faceDetectMode, uint faceDetectEmbedDataValue, uint faceDetectOverlayRect);    
    void flashModeValue(uint flashMode);
    void smileDetectModeValue(uint smileDetectMode, uint smileDetectEmbedDataValue);

public slots:
    bool setEffectMode(const specialEffects &specialEffect);
    bool getEffectMode();

    bool setDenoiseValue(int deNoiseVal);
    bool getDenoiseValue();

    bool setSceneMode(const sceneModes &sceneMode);
    bool getSceneMode();

    bool setROIAutoExposure(camROIAutoExpMode see3camAutoexpROIMode, uint vidResolnWidth, uint vidResolnHeight, uint xCord, uint yCord, QString winSize);
    bool getAutoExpROIModeAndWindowSize();

    bool setBurstLength(uint burstLength);
    bool getBurstLength();

    bool setQFactor(uint qFactor);
    bool getQFactor();

    bool setOrientation(bool horzModeSel, bool vertiModeSel);
    bool getOrientation();

    bool setFrameRateCtrlValue(uint frameRate);
    bool getFrameRateCtrlValue();

    bool setExposureCompensation(unsigned int exposureCompValue);
    bool getExposureCompensation();

    bool setFaceDetectionRect(bool enableFaceDetectRect, bool embedData, bool overlayRect);
    bool getFaceDetectMode();

    bool enableDisableFaceRectangle(bool enableFaceRect);

    bool setFlashState(flashStateValues flashMode);
    bool getFlashState();

    bool setSmileDetection(bool enableSmileDetect, bool embedData);
    bool getSmileDetectMode();

    bool setToDefault();
};
#endif // SEE3CAM_CU38_H
