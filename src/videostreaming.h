/*
 * videostreaming.h -- preview the camera buffer
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


#ifndef VIDEOSTREAMING_H
#define VIDEOSTREAMING_H
#include <QTimer>
#include <QDateTime>
#include <QSocketNotifier>
#include <QStringList>
#include <QStringListModel>
#include <QDir>
#include <sys/mman.h>
#include <libv4l2.h>
#include <QMutex>
#include <QList>
#include <QStandardPaths>
#include <turbojpeg.h>
#include "v4l2-api.h"
#include "videoencoder.h"
#include "h264decoder.h"
#include "audioinput.h"
#include "uvccamera.h"
#include "common_enums.h"
#include"fscam_cu135.h"
#include <linux/uvcvideo.h>

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMutex>
#include <unistd.h>
#include <sys/ioctl.h>

class FrameRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    FrameRenderer();
    ~FrameRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

    /**
     * @brief FrameRenderer::calculateViewportWidth - calculate view port width to maintain aspect ratio
     * @param vidResolutionWidth - video preview resolution width
     * @param vidResolutionHeight - video preview resolution height
     * @param windowHeight - window renderbackground area height
     * @param *x - to store x position
     * @param *y - to store y position
     * @param *destWindowWidth - to store target window viewport width
     * @param *destWindowHeight - to store target window viewport height
     */
    void calculateViewport(int vidResolutionWidth, int  vidResolutionHeight, int windowHeight, int windowWidth, int *x, int *y, int *destWindowWidth, int *destWindowHeight);

    // Draw RGBA buffer
    void drawRGBBUffer();

    // Convert YUYV  to RGB and draw
    void drawYUYVBUffer();
    void drawUYVYBUffer();
    void drawY8BUffer();
    void drawBufferFor360p();
    void clearShader();
    void changeShader();
    void shaderRGB();
    void shaderYUYV();
    void shaderUYVY();
    void shaderY8();
    void getDisplayRenderArea(int *displayX, int *displayY, int *destWidth, int *destHeight);
    void updateBuffer();

    // opengl context
    QOpenGLContext *m_context;

    // yuv buffers
    uint8_t *yBuffer;
    uint8_t *uBuffer;
    uint8_t *vBuffer;
    uint8_t *yuvBuffer,*greyBuffer;
      __u32 xcord,ycord;
    unsigned frame;

    // rgba buffer
    unsigned char *rgbaDestBuffer;
    uint8_t renderBufferFormat;
    uint viewportHeight;

    __u32 videoResolutionwidth;
    __u32 videoResolutionHeight;
    __u32 width,height;
     __u32 x1,y1;
    bool gotFrame;
    bool triggermodeFlag;
    bool copied;
    unsigned fps;

    QMutex renderMutex; // mutex to use in rendering - rgba
    QMutex renderyuyvMutex; // mutex to use in rendering yuyv   

    bool  m_formatChange;
    bool  m_videoResolnChange;
    bool sidebarStateChanged;
    bool windowStatusChanged;
    int glViewPortX;
    int glViewPortY;
    int glViewPortWidth;
    int glViewPortHeight;
    __u32 m_pixelformat;
    bool y16BayerFormat;

signals:
     void ybufferchanged(uint8_t);

public slots:
    void paint();

    // spilit yuyv buffer to y,u,v buffer
    void selectedCameraEnum(CommonEnums::ECameraNames selectedDeviceEnum);

public:
    QSize m_viewportSize;
    int previewBgrdAreaHeight;
    int previewBgrdAreaWidth;

    bool sidebarAvailable; // left sidebar items [settings] availability in UI
    int sidebarWidth;      // left side bar width
    bool updateStop;
    bool getPreviewFrameWindow;

    // shader program
    QOpenGLShaderProgram *m_shaderProgram;
    QOpenGLShaderProgram *m_programYUYV;

private:    
    qreal m_t;

    QQuickWindow *m_window;

    // texture coodinates
    int mPositionLoc;
    int mTexCoordLoc;

    GLint samplerLocY;
    GLint samplerLocU;
    GLint samplerLocV;
    GLint samplerLocYUYV;
    GLint samplerLocUYVY;
    GLint samplerLocRGB;
    GLint samplerLocGREY;

     static CommonEnums::ECameraNames currentlySelectedEnumValue;
};

class Videostreaming :  public QQuickItem, public v4l2
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    struct buffer {
        unsigned planes;
        void   *start[VIDEO_MAX_PLANES];
        size_t  length[VIDEO_MAX_PLANES];
    };
    Videostreaming();
    ~Videostreaming();   
    
    qreal t() const { return m_t; }
    void setT(qreal t);
    void updateBuffer();

    QString fileName;

    static QStringListModel resolution;
    static QStringListModel stillOutputFormat;
    static QStringListModel videoOutputFormat;
    static QStringListModel fpsList;    
    static QStringListModel encoderList;
     QTimer m_timer;

    void displayFrame();

   unsigned char *tempSrcBuffer;


    // prepare target buffer for rendering from input buffer.
    bool prepareBuffer(__u32 pixformat, void *inputbuffer, __u32 bytesUsed);

    // save captured image files
    bool saveRawFile(void *inputBuffer, int buffersize);    
    bool saveIRImage();


    static int jpegDecode(Videostreaming *obj, unsigned char **pic, unsigned char *buf, unsigned long bytesUsed);
    static int decomp(Videostreaming *obj, unsigned char **jpegbuf,
                                   unsigned long *jpegsize, unsigned char *dstbuf, int w, int h,
                                   int jpegqual, int tilew, int tileh,unsigned char **pic);

    // Added by Sankari: 25 Apr 2019. To avoid preview hang while recording video.
    static void captureVideoInThread(Videostreaming *obj);
    double getTimeInSecs(void);
    void freeBuffer(unsigned char *ptr);

    /* cu40 IR image capture */
    bool extractIRImage(unsigned short int *srcBuffer, unsigned char *irBuffer);

    bool findNativeFormat(__u32 format, QImage::Format &dstFmt);
    bool startCapture();
    bool retrieveFrame;

    bool getPreviewWindow;
    bool frameArrives,frameMjpeg;

    // get current resoution set in v4l2
    QString getResoultion();

    // Things need to do after change FPS and take shot
    void doAfterChangeFPSAndShot();

    v4l2_format fmt;
    QString _title;
    QString _text;
    QString lastPreviewSize;
    QString lastFormat;
    bool OnMouseClick;
    // Added by Sankari - To maintain last set framerate
    QString lastFPSValue;

    VideoEncoder  *videoEncoder;
    VideoEncoder  videoEncoderObj;
    H264Decoder *h264Decode;
    AudioInput audioinput;
    audio_buff_t *audio_buffer_data;
    bool audiorecordStart;
    bool SkipIfPreviewFrame;
    QMutex recordMutex;

   FSCAM_CU135 Fscamcu135;


    /* Jpeg decode */
    int doyuv;
    int dotile;
    int pf;
    int yuvpad;
    int warmup;
    int flags;
    tjscalingfactor sf;

    uint frameToSkip;
    int frame;
    uint previewFrameSkipCount;
    uint previewFrameToSkip;
    bool skippingPreviewFrame;
    bool changefps;
    enum fpsChange {
        FPS_30 = 0x00,
        FPS_60 = 0x01,
        FPS_DEFAULT =0x02
    };
    Q_ENUMS(fpsChange)

private:
    QFuture <int >threadMonitor;        //Added by M.Vishnu Murali:In order to moitor functions running in seperate thread.
    qreal m_t;
    __u8 m_bufReqCount;
    FrameRenderer *m_renderer;

    uint8_t *yuyvBuffer ,*yuyvBuffer_Y12;
    uint8_t *yuv420pdestBuffer;
    unsigned short int *bayerIRBuffer;

    __u32 _bytesUsed;
    __u32 m_pixelformat;
    __u32 m_width, m_height;
    __u32 m_buftype;
    __u32 width, height, pixfmt;
    __u32 resWidth,resHeight;
     __u32 x,y;
    QString m_filePath;
    QString m_imgFormatType;

    fd_set fds;
    struct timeval                  tv;
    int                             r;
    unsigned int                    n_buffers;

    QMutex mutex;
    QTime captureTime;

    unsigned m_frame;
    unsigned m_lastFrame;

    unsigned m_fps;
    struct timeval m_tv;

    char header[50];

    bool m_supportedFormat;
    bool openSuccess;
    bool updateOnce;
    bool m_snapShot;
    bool startFrame;

    bool updateStop;
    bool makeSnapShot;
    bool changeFpsAndShot; // To change fps and take shot
    bool fpsChangedForStill;
    bool m_burstShot;
    bool triggerShot;
    bool m_has_interval;
    bool tempMsgBoxValue;
    bool m_VideoRecord;
    bool previewStop;
    bool trigger_mode;
    int triggermode_skipframes;
    int skipImageCapture;

    QSocketNotifier *m_capNotifier;

    struct v4l2_fract m_interval;
    struct v4l2_fract interval;
    struct v4l2_format m_capSrcFormat;
    struct v4l2_format m_capDestFormat;
    v4l2_format copy;

    struct v4lconvert_data *m_convertData;
    struct buffer *m_buffers;

    QImage *m_capImage;   
  

    QString ctrlName, ctrlType, ctrlID, ctrlStepSize, ctrlMaxValue, ctrlMinValue,ctrlDefaultValue;
    QString stillSize;
    QString stillOutFormat;
    QString formatType;
    QString filename;
    QString ubuntuVersion;
    QStringList availableFPS; // Moved from funtion updateFrameInterval() in videostreaming.c to here

    QMap<QString,QString> pixFormat;

    QMutex pixmapMutex;

    unsigned char *m_data;
    unsigned char *m_frameData;

    unsigned char *m_buf;
    unsigned m_size;

    uint m_nbuffers;    
    static int deviceNumber;
    static QString camDeviceName;

    unsigned char  *y16BayerDestBuffer;
    bool y16BayerFormat,y16FormatFor20CUG;
    unsigned char* rgb_image;
 /**
     * @brief currentlySelectedCameraEnum - This contains currently selected camera enum value
     */
    static CommonEnums::ECameraNames currentlySelectedCameraEnum;

    uint m_burstLength;
    uint m_burstNumber;

    // Added by Sankari  - 10 Nov 2016 - To decide whether display pop up dialog will appear in while capturing image
    bool m_displayCaptureDialog;

    // Added by Sankari  - 10 Nov 2016 - To decide whether to save image or not
    bool m_saveImage;
    unsigned int imgSaveSuccessCount;

    bool frameSkip;

    QString getSettings(unsigned int);
    void getFrameRates();
    void updateVidOutFormat();
    void tmpMsgBox(QString);
    bool getInterval(struct v4l2_fract &interval);

    int findMax(QList<int> *llist);
    void freeBuffers(unsigned char *destBuffer,unsigned char *copyBuffer);
    void allocBuffers();
    void getFileName(QString filePath,QString imgFormatType);
    void setFilePath(QString filePath);
    QString getFilePath();
    void setImageFormatType(QString imgFormatType);
    QString getImageFormatType();
    bool retrieveframeStoreCam;
    bool retrieveframeStoreCamInCross;
    bool retrieveShot;
    bool stopRenderOnMakeShot;
    bool onY12Format;
    bool windowResized;
    uint resizedWidth,resizedHeight,changeFPSForHyperyon;
    bool check_jpeg_header(void *inputbuffer, __u32 bytesUsed);

private slots:
    void handleWindowChanged(QQuickWindow *win); 

public slots:
     void switchToStillPreviewSettings(bool stillSettings);
     void retrieveFrameFromStoreCam();
    void sync();
    void cleanup();   
    void setPreviewBgrndArea(int width, int height, bool sidebarAvailable);
    // Added by Sankari: 21 May 2019, Called this when sidebar opened/closed
    void sidebarStateChanged();
    void enumerateAudioProperties();
    void setChannelCount(uint index);
    void setSampleRate(uint index);
    void stopUpdatePreview();
    void doCaptureFrameTimeout();
    void stopFrameTimeoutTimer();
    void enableTimer(bool timerstatus);
    void retrieveShotFromStoreCam(QString filePath,QString imgFormatType);
    void previewWindow();
    void widthChangedEvent(int width);
    void heightChangedEvent(int height);
     // Added by Sankari : 10 Dec 2016
    // To Disable image capture dialog when taking trigger shot in trigger mode for 12cunir camera
    void disableImageCaptureDialog();

    // Added by Sankari : 10 Dec 2016
    // Disable saving image when focus is changed from trigger mode to master mode
    // or changing to any other camera if it is m_saveImage flag set as true to avoid displaying unnecessary pop up dialog.
    // It is used in 12cunir camera. It can be used for other cameras also.
    void disableSavingImage();

    /**
     * @brief Query buffer and Deque buffer
     *  -
     */
    void capFrame();

    /**
     * @brief Still Capture the image preview [In Default/Master Mode]
     * @param filePath - Captured still will be saved in this location
     * @param imgFormatType - Image formats is of four typede
     * 1. JPG
     * 2. BMP
     * 3. RAW
     * 4. PNG
     */
    void makeShot(QString filePath,QString imgFormatType);

    /**
     * @brief Make burst shot preview
     * @param filePath - Captured still will be saved in this location
     * @param imgFormatType - Image formats is of four typede
     * @param burstLength - Number of images to take in a single click
     * 1. JPG
     * 2. BMP
     * 3. RAW
     * 4. PNG
     */
    void makeBurstShot(QString filePath,QString imgFormatType, uint burstLength);

    /**
     * @brief changeFPSandTakeShot - change fps and take still
     * @param filePath
     * @param imgFormatType
     */
    void  changeFPSandTakeShot(QString filePath,QString imgFormatType, uint fpsIndex);

    /**
     * @brief Still Capture the image preview [In Trigger Mode]
     * @param filePath - Captured still will be saved in this location
     * @param imgFormatType - Image formats is of four typede
     * 1. JPG
     * 2. BMP
     * 3. RAW
     * 4. PNG
     */
    void triggerModeShot(QString filePath,QString imgFormatType);

    /**
     * @brief To stop the camera preview
     */
    void stopCapture();
    void resolnSwitch();

    /**
     * @brief To start the camera preview
     */
    void startAgain();

    /**
     * @brief To set the camera resolution.
     * @param resolution - Actual resolution set to the camera.  For example, 640x480.
     */
    void setResoultion(QString resolution);

    /**
     * @brief To open the camera device(video node).
     * @param deviceName - Its the video node name (/dev/video)
     */
    void setDevice(QString deviceName);

    /**
     * @brief Close the last instance opened camera device.  User should call stopCapture() before calling this function.
     */
    void closeDevice();

    /**
     * @brief Emulate the available colorspace supported by the camera.
     */
    void displayOutputFormat();

    /**
     * @brief Emulate the available resolution for still capturing supported by the camera.
     */
    void displayStillResolution();


    /**
     * @brief Emulate the available resolution for video streaming supported by the camera.
     */
    void displayVideoResolution();

    /**
     * @brief To set the camera device node number to setDevice() function
     * @param deviceNode - Device node number.  Must be 0 or greater than 0.
     */
    void getFirstDevice(int deviceNode);

    /**
     * @brief To set the camera name
     * @param deviceName - Camera name
     */
    void getCameraName(QString deviceName);

    /**
     * @brief To get the available camera controls of the current device(Brightness, contrast...)
     * @param actualValue
     * 1. true - To get the last saved values of the controls.  On First plug last saved values will be default values.
     * 2. false - To get the default values of the controls.
     */
    void cameraFilterControls(bool actualValue = true);

    /**
     * @brief To change the values of the camera controls
     * @param id - Id of any one of the camera control
     * @param value - Value to be set the for the camera control based on the ID.  Value should be with in the maximum
     * and minimum value.
     */
    void changeSettings(unsigned int id,QString value);

    /**
     * @brief selectMenuIndex
     * @param id
     * @param value
     */
    void selectMenuIndex(unsigned int id, int value);

    void setFpsOnCheckingFormat(QString stillFmt);
    void vidCapFormatChanged(QString idx);
    void setStillVideoSize(QString stillValue,QString stillFormat);
    void lastPreviewResolution(QString resolution,QString format);
    // Added by Sankari - To maintain last set framerate
    void lastFPS(QString fps);
    void formatSaveSuccess(bool burstFlag);
    void updateFrameInterval(QString pixelFormat, QString frameSize);

    /**
     * @brief frameIntervalChanged
     * @param idx
     */
    void frameIntervalChanged(int idx ,uint fpsSetForHyperyon);

    void recordVideo();
      /**
     * @brief To begin video recording this function should be called
     * @param videoEncoderType - Encoder types are video codecs, Currently four codecs are used as follows
     * 1. RAW VIDEO
     * 2. MJPEG
     * 3. H264     
     * @param videoFormatType - Format type is the container used to record the video.  Currently two containers are used as follows
     * 1. avi
     *
     * @param fileLocation - Location where the recorded file is saved
     * @param - audioDeviceIndex  - audio device index
     */
    void recordBegin(int videoEncoderType, QString videoFormatType, QString fileLocation, int audioDeviceIndex, unsigned sampleRate, int channels);

    /**
     * @brief This function should be called to stop the video recording
     */
    void recordStop();

    /**
     * @brief To stop updating the preview in the trigger Mode
     */
    void triggerModeEnabled();

    /**
     * @brief Preview will be continously updating in this mode
     */
    void masterModeEnabled();

    int getMenuIndex(unsigned int,int);

    void displayEncoderList();
 /**
     * @brief selectedCameraEnum - This slot contains selected camera enum value
     * @param selectedDeviceEnum - Camera enum value
     */
    void selectedCameraEnum(CommonEnums::ECameraNames selectedDeviceEnum);

    void updateFrameToSkip(uint stillSkip);

    void updatePreviewFrameSkip(uint previewSkip);
    void setSkipPreviewFrame(bool skipFrame);


    void enumerateFPSList();

    // Set the uvc extension control value
    bool setUvcExtControlValue(struct uvc_xu_control_query xquery);

    void doEncodeAudio();
    void triggerModeSkipframes();
    void updatepreview();

signals:
    void   triggerShotCap();


    // from qml file , rendering animation duration t changed
    void tChanged();

    void captureVideo();

    // Added by Sankari: 12 Feb 2018
    // Get the bus info details and send to qml for selected camera
    void pciDeviceBus(QString businfo);
    void setWindowSize(uint win_width,uint win_height);
    void logDebugHandle(QString _text);
    void logCriticalHandle(QString _text);
    void titleTextChanged(QString _title,QString _text);
    void enableCaptureAndRecord();
    void newControlAdded(QString ctrlName,QString ctrlType,QString ctrlID,QString ctrlStepSize = "0",QString ctrlMinValue= "0", QString ctrlMaxValue = "0",QString ctrlDefaultValue="0", QString ctrlHardwareDefault="0");
    void deviceUnplugged(QString _title,QString _text);    
    void averageFPS(unsigned fps);
    void defaultStillFrameSize(unsigned int outputIndexValue);
    void defaultFrameSize(unsigned int outputIndexValue, unsigned int  defaultWidth, unsigned int defaultHeight);
    void defaultOutputFormat(unsigned int formatIndexValue);
    void defaultFrameInterval(unsigned int frameInterval);
    void captureSaveTime(QString saveTime);
    void refreshDevice();
    void addControls();
    void rcdStop(QString recordFail);
    void videoRecordInvalid(QString noVideo);
    void videoRecord(QString fileName);
    void enableRfRectBackInPreview();
    void enableFactRectInPreview();
    void capFrameTimeout();
    void signalForPreviewWindow(int resWidth,int resHeight,int x,int y);

    // Added by Sankari: 02 Dec 2017
    void stillSkipCount(QString stillResoln, QString videoResoln, QString stillOutFormat);

    void stillSkipCountWhenFPSChange(bool fpsChange);

    void requestToChangeFPSandTakeShot();

    // To get FPS list
    void sendFPSlist(QString fpsList);
     void signalTograbPreviewFrame(bool retrieveframe,bool InFailureCase);
     void signalToSwitchResoln(bool switchResoln);
};

#endif // VIDEOSTREAMING_H
