#ifndef SEE3CAM_20CUG
#define SEE3CAM_20CUG

#include "uvccamera.h"
#include <QObject>

#define CAMERA_CONTROL_SEE3CAM_20CUG    0xA1
#define SET_SUCCESS                     0x01
#define SET_FAILURE                     0x00

#define SET_STREAM_MODE_20CUG                 0x02
#define GET_STREAM_MODE_20CUG                 0x01

#define GET_SUCCESS                     0x01
#define GET_FAILURE                     0x00

#define SET_FLASH_MODE_20CUG                   0x04
#define GET_FLASH_MODE_20CUG                   0x03

#define SET_FLIP_CONTROLS_20CUG                0x06
#define GET_FLIP_CONTROLS_20CUG                0x05

#define SET_DEFAULT_20CUG                      0xFF

#define READ_FIRMWARE_VERSION_20CUG            0x40

#define READ_UNIQUE_ID_20CUG                   0x41

class See3CAM_20CUG : public QObject
{
    Q_OBJECT

 private:
    unsigned char g_out_packet_buf[BUFFER_LENGTH];
    unsigned char g_in_packet_buf[BUFFER_LENGTH];
    uvccamera uvc;
    QString _title;
    QString _text;

    void initializeBuffers();
public :
     explicit See3CAM_20CUG(QObject *parent = 0);

    enum streamModes {
       MODE_MASTER =0x00,
       MODE_TRIGGER =0x01
    };

    Q_ENUMS(streamModes)


    enum flashModes {
       MODE_OFF =0x01,
       MODE_ON =0x02,
    };

    Q_ENUMS(flashModes)

    enum flipControls {
       FLIP_NORMAL =0x01,
       FLIP_HORIZONTAL =0x02,
       FLIP_VERTICAL =0x03,
       FLIP_BOTH =0x04
    };
    Q_ENUMS(flipControls)

signals:
        void streamModeValue(uint streamMode);
        void flashModeValue (uint flashMode);
        void flipCtrlValue (uint flipValue);
        void titleTextChanged(QString _title,QString _text);

public slots:

         bool setStreamMode(streamModes streamMode);
         bool getStreamMode();

         bool setFlashMode(flashModes flashMode);
         bool getFlashMode();

         bool setFlipCtrlValue(bool hFlip,bool vFlip);
         bool getFlipCtrlValue();

         bool setToDefault();
};
#endif // SEE3CAM_20CUG

