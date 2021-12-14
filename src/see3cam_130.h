#ifndef SEE3CAM_130_H
#define SEE3CAM_130_H
#include <QObject>
#include "uvccamera.h"
#define DENOISE_MIN 0
#define DENOISE_MAX 15
#define EXPOSURECOMP_MIN 8000
#define EXPOSURECOMP_MAX 1000000

#define SET_DENOISE_CONTROL  0x06
#define GET_DENOISE_CONTROL  0x05

/* SEE3CAM_130 */
#define CAMERA_CONTROL_130              0x7B
#define GET_SCENEMODE_130				0x01
#define SET_SCENEMODE_130				0x02
#define GET_SPECIALEFFECT_130			0x03
#define SET_SPECIALEFFECT_130			0x04
#define GET_DENOISE_130					0x05
#define SET_DENOISE_130					0x06
#define GET_AF_MODE_130					0x07
#define SET_AF_MODE_130					0x08
#define GET_AF_ROI_MODE_130				0x09
#define SET_AF_ROI_MODE_130				0x0A
#define GET_EXP_ROI_MODE_130			0x0B
#define SET_EXP_ROI_MODE_130			0x0C
#define GET_BURST_LENGTH_130			0x0D
#define SET_BURST_LENGTH_130			0x0E
#define GET_HDR_MODE_130				0x0F
#define SET_HDR_MODE_130				0x10
#define GET_Q_FACTOR_130				0x11
#define SET_Q_FACTOR_130				0x12
#define ENABLE_DISABLE_MODE_AF_RECTANGLE_130     0x13
#define GET_AF_RECT_MODE                0x16
#define ENABLE_AF_RECTANGLE_130     0x01
#define DISABLE_AF_RECTANGLE_130     0x00
#define SET_TO_DEFAULT                0x17
#define MANUAL_ROI_AF_130             0x02
#define MANUAL_ROI_EXP_130			  0x02
#define SET_FLIP_MODE_130                 0x19
#define GET_FLIP_MODE_130                 0x18
#define FLIP_ENABLE                   0x01
#define FLIP_DISABLE                  0x00
#define SET_HORZ_FLIP_MODE_130             0x00
#define SET_VERT_FLIP_MODE_130             0x01

#define SET_STREAM_MODE_130               0x15
#define GET_STREAM_MODE_130               0x14

#define ENABLE_DISABLE_MODE_FACE_RECTANGLE_130       0x26
#define ENABLE_FACE_RECTANGLE_130       0x01
#define DISABLE_FACE_RECTANGLE_130      0x00
#define SET_FACE_DETECT_RECT            0x1F
#define GET_FACE_DETECT_RECT            0x1E
#define ENABLE_FACE_RECT                0x01
#define DISABLE_FACE_RECT               0x00
#define ENABLE_EMBED_DATA               0x01
#define DISABLE_EMBED_DATA              0x00
#define ENABLE_SMILE_TRIGGER_130        0x01
#define DISABLE_SMILE_TRIGGER_130        0x00
#define ENABLE_OVERLAY_RECT             0x01
#define DISABLE_OVERLAY_RECT            0x00
#define FACE_RECT_SUCCESS               0x01
#define FACE_RECT_FAIL                  0x00

#define SET_SMILE_DETECTION             0x21
#define GET_SMILE_DETECTION             0x20
#define ENABLE_SMILE_DETECT             0x01
#define DISABLE_SMILE_DETECT            0x00
#define SMILE_DETECT_SUCCESS            0x01
#define SMILE_DETECT_FAIL               0x00

#define SET_EXPOSURE_COMPENSATION       0x23
#define GET_EXPOSURE_COMPENSATION       0x22

#define SET_FRAME_RATE_130              0x25
#define GET_FRAME_RATE_130              0x24

#define SET_FLICKER_DETECTION_130           0x28
#define GET_FLICKER_DETECTION_130           0x27


class See3CAM_130 : public QObject
{
    Q_OBJECT

private:
    unsigned char g_out_packet_buf[BUFFER_LENGTH];
    unsigned char g_in_packet_buf[BUFFER_LENGTH];
    uvccamera uvc;

    void initializeBuffers();

public:
    explicit See3CAM_130(QObject *parent = 0);

    enum sceneModes {
        SCENE_NORMAL = 0x01,
        SCENE_DOCUMENT = 0x0C
    };
    Q_ENUMS(sceneModes)

    enum specialEffects {
        EFFECT_NORMAL = 0x01,        
        EFFECT_BLACK_WHITE = 0x04,
        EFFECT_GREYSCALE = 0x07,
        EFFECT_NEGATIVE = 0x08,
        EFFECT_SKETCH = 0x10
    };

     Q_ENUMS(specialEffects)

    enum camAfMode {
        Continuous = 0x01,
        OneShot = 0x02,
        AfModeDisabled = 0x03
    };
    Q_ENUMS(camAfMode)

    enum camiHDRMode {
        HdrOff = 0x01,
        HdrAuto = 0x02,
        HdrManual = 0x03
    };
    Q_ENUMS(camiHDRMode)

    enum camROIAfMode {
        AFCentered = 0x01,
        AFManual = 0x02,
        AFDisabled = 0x03
    };
    Q_ENUMS(camROIAfMode)

    enum camROIAutoExpMode {
        AutoExpFace = 0x00,
        AutoExpFull = 0x01,
        AutoExpManual = 0x02,
        AutoExpDisabled = 0x03
    };
    Q_ENUMS(camROIAutoExpMode)

    enum camAFRectMode {
        AFRectEnable = 0x01,
        AFRectDisable = 0x00
    };
    Q_ENUMS(camAFRectMode)

    enum camFlipMode {
        FlipHorizontal = 0x00,
        FlipVertical = 0x01,
        FlipBoth = 0x02
    };
    Q_ENUMS(camFlipMode)

    enum camFlipEnableDisableMode {
        FlipEnable = 0x01,
        FlipDisable = 0x00
    };
    Q_ENUMS(camFlipEnableDisableMode)

    enum camStreamMode {
        STREAM_MASTER = 0x00,
        STREAM_TRIGGER = 0x01
    };
    Q_ENUMS(camStreamMode)

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

    enum camFlickerMode {
         MODE_AUTO = 0x00,
         MODE_50Hz =0x01,
         MODE_60Hz =0x02,
         MODE_DISABLE =0x03
       };
       Q_ENUMS(camFlickerMode)

   
signals:
     void sceneModeValue(uint sceneMode);
     void effectModeValue(uint effectMode);
     void afModeValue(uint afMode);
     void hDRModeValueReceived(uint hdrMode, uint hdrValue);
     void denoiseValueReceived(uint denoiseValue);
     void burstLengthValue(uint burstLength);
     void qFactorValue(uint qFactor);
     void roiAfModeValue(uint roiMode, uint winSize);
     void roiAutoExpModeValue(uint roiMode, uint winSize);
     void afRectModeValue(uint afRectMode);
     void flipModeValue(uint flipMode, uint flipEnableDisableMode);
     void streamModeValue(uint streamMode);
     void faceDetectModeValue(uint faceDetectMode, uint faceDetectEmbedDataValue, uint faceDetectOverlayRect);
     void smileDetectModeValue(uint smileDetectMode, uint smileDetectEmbedDataValue);
     void exposureCompValueReceived(uint exposureCompensation);
     void frameRateCtrlValueReceived(uint frameRateCtrlValue);
     void indicateCommandStatus(QString title, QString text);
     void indicateExposureValueRangeFailure(QString title, QString text);
     void flickerDetectionMode(uint flickerMode);

public slots:
    bool getSceneMode();
    bool setSceneMode(const sceneModes& sceneMode);

    bool getEffectMode();
    bool setEffectMode(const specialEffects& specialEffect);

    bool setDenoiseValue(int deNoiseVal);
    bool getDenoiseValue();

    bool setAutoFocusMode(camAfMode afMode);
    bool getAutoFocusMode();

    bool setiHDRMode(camiHDRMode iHDRMode, uint iHDRValue);
    bool getiHDRMode();    

    bool setROIAutoFoucs(camROIAfMode see3camAfROIMode, uint vidResolnWidth, uint vidResolnHeight, uint xCord, uint yCord, QString winSize);
    bool setROIAutoExposure(camROIAutoExpMode see3camAutoexpROIMode, uint vidResolnWidth, uint vidResolnHeight, uint xCord, uint yCord, QString winSize);

    bool getAutoFocusROIModeAndWindowSize();
    bool getAutoExpROIModeAndWindowSize();

    bool setBurstLength(uint burstLength);
    bool getBurstLength();

    bool setQFactor(uint qFactor);
    bool getQFactor();

    bool enableDisableAFRectangle(bool enableRFRect);    
    bool getAFRectMode();

    bool setToDefault();

    bool setFlipHorzMode(bool horizModeSel);
    bool setFlipVertiMode(bool vertiModeSel);
    bool getFlipMode();

    bool setStreamMode(camStreamMode streamMode);
    bool getStreamMode();

    bool setFlickerDetection(camFlickerMode flickerMode);
    bool getFlickerDetection();

    bool setFaceDetectionRect(bool enableFaceDetectRect, bool embedData, bool overlayRect);
    bool getFaceDetectMode();

    bool setSmileDetection(bool enableSmileDetect, bool embedData);
    bool getSmileDetectMode();

    bool setExposureCompensation(unsigned int exposureCompValue);
    bool getExposureCompensation();

    bool setFrameRateCtrlValue(uint frameRate);
    bool getFrameRateCtrlValue();

    bool enableDisableFaceRectangle(bool enableFaceRect);

};
#endif // SEE3CAM_130_H
