#ifndef SEE3CAM_CU81_H
#define SEE3CAM_CU81_H

#include <QObject>
#include <QtConcurrentRun>
#include "uvccamera.h"

#define CAMERA_CONTROL_CU81			0xAC

#define EXPOSURECOMP_MIN 8000
#define EXPOSURECOMP_MAX 1000000

#define GET_CAMERA_MODE_CU81        0x01
#define SET_CAMERA_MODE_CU81        0x02
#define GET_SPECIALEFFECT_CU81      0x03
#define SET_SPECIALEFFECT_CU81      0x04
#define GET_DENOISE_CU81            0x05
#define SET_DENOISE_CU81            0x06
#define GET_ROIEXPMODE_CU81         0x07
#define SET_ROIEXPMODE_CU81         0x08
#define GET_BURSTLENGTH_CU81        0x09
#define SET_BURSTLENGTH_CU81        0x0A
#define GET_QFACTOR_CU81            0x0B
#define SET_QFACTOR_CU81            0x0C
#define GET_ORIENTATION_CU81        0x0D
#define SET_ORIENTATION_CU81        0x0E
#define GET_EXPCOMPENSATION_CU81    0x10
#define SET_EXPCOMPENSATION_CU81    0x11
#define GET_FRAMERATE_CU81          0x12
#define SET_FRAMERATE_CU81          0x13
#define GET_ANTIFLICKER_CU81        0x16
#define SET_ANTIFLICKER_CU81        0x17
#define SET_DEFAULTS_CU81           0xFF
class See3CAM_CU81 : public QObject
{
    Q_OBJECT
private:
        uvccamera uvc;
        unsigned char g_out_packet_buf[BUFFER_LENGTH];
        unsigned char g_in_packet_buf[BUFFER_LENGTH];
        void initializeBuffers();
public:
        See3CAM_CU81();
        ~See3CAM_CU81();

        enum cameraModes
        {
            DAY_HDR_MODE = 0x00,
            NIGHT_HDR_MODE = 0x01,
            LINEAR_MODE =0x02
        };
        Q_ENUMS(cameraModes)

        enum specialEffects
        {
            EFFECT_NORMAL = 0x01,
            EFFECT_BLACK_WHITE = 0x04,
            EFFECT_GREYSCALE = 0x07,
            EFFECT_NEGATIVE = 0x08,
            EFFECT_SKETCH = 0x10
        };
        Q_ENUMS(specialEffects)

        enum camROIAutoExpMode
        {
            AutoExpFull = 0x01,
            AutoExpManual = 0x02,
            AutoExpDisabled = 0x03
        };
        Q_ENUMS(camROIAutoExpMode)

        enum camFlipMode {
            FLIP_BOTHFLIP_ENABLE =0x03,
            FLIP_HORZFLIP = 0x01,
            FLIP_VERTFLIP =0x02 ,
            FLIP_BOTHFLIP_DISABLE =0x00
        };
        Q_ENUMS(camFlipMode)

        enum camAntiFlickerMode {
            AntiFlickerAuto = 0x00,
            AntiFlicker50Hz = 0x01,
            AntiFlicker60Hz = 0x02
        };
        Q_ENUMS(camAntiFlickerMode)

signals:
        void sendCameraModeValue(uint cameraMode);
        void sentEffectMode(uint effectMode);
        void sendDenoiseValue(uint denoise);
        void roiAutoExpModeValue(uint roiMode, uint winSize);
        void burstLengthValue(uint burstLength);
        void qFactorValue(uint qFactor);
        void flipMirrorModeChanged(uint flipMirrorMode);
        void frameRateCtrlValueReceived(uint frameRateCtrlValue);
        void antiFlickerModeChanged(uint flickerMode);

        void indicateCommandStatus(QString title, QString text);
        void indicateExposureValueRangeFailure(QString title, QString text);
        void exposureCompValueReceived(uint exposureCompensation);

public slots:
        bool getCameraMode();
        bool setCameraMode(const See3CAM_CU81::cameraModes &cameraMode);

        bool getEffect();
        bool setEffect(const specialEffects &specialEffect);

        bool getDenoise();
        bool setDenoise(int deNoiseValue);

        bool getAutoExpROIModeAndWindowSize();
        bool setROIAutoExposure(camROIAutoExpMode see3camAutoexpROIMode, uint vidResolnWidth, uint vidResolnHeight, uint xCord, uint yCord, QString winSize);

        bool getBurstLength();
        bool setBurstLength(uint burstLength);

        bool getQFactor();
        bool setQFactor(uint qFactor);

        bool getFlipMode();
        bool setFlipMode(bool horzModeSel, bool vertiModeSel);

        bool getExposureCompensation();
        bool setExposureCompensation(unsigned int exposureCompValue);

        bool getFrameRateCtrlValue();
        bool setFrameRateCtrlValue(uint frameRate);

        bool getAntiFlickerMode();
        bool setAntiFlickerMode(camAntiFlickerMode antiFlickerMode);

        bool setToDefault();
};
#endif // SEE3CAM_CU81_H
