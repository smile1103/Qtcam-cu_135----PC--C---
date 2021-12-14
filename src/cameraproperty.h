/*
 * cameraproperty.h -- enumerate the available cameras and filters the e-con camera connected to the device
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

#ifndef CAMERAPROPERTY_H
#define CAMERAPROPERTY_H
#include <QQuickPaintedItem>
#include <QQuickImageProvider>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDir>
#include <QStringList>
#include <QStringListModel>
#include <QQuickView>
#include <QQmlContext>
#include <QStandardItemModel>
#include <QTimer>
#include <qtquick2applicationviewer.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include "v4l2-api.h"
#include "uvccamera.h"
#include "videostreaming.h"
#include "logger.h"
#include "libudev.h"
#define V4L2_CAP_META_CAPTURE     0x00800000

class Cameraproperty : public QObject, public v4l2
{
    Q_OBJECT
public:
    enum usbPort{
        USB2_0 = 1,
        USB3_0 = 2
    };

    Cameraproperty();
    Cameraproperty(bool enableLog);
    ~Cameraproperty();
    QStringList availableCam;

    uvccamera uvccam;
    Videostreaming vidStr;
    FrameRenderer frmrend;
    logger log;
    void checkforEconDevice(QStringList*);

    static QStringListModel modelCam;
    static bool saveLog;
    static int event_fd;

private:
    QDir qDir;
    struct v4l2_capability m_querycap;
    QMap<int, QString> cameraMap;
    QMap<int, QString> deviceNodeMap;
    QMap<int, QString> libusbNodeMap;


public slots:

    int  getUsbSpeed(QString serialNumber);
    /**
     * @brief Check e-con Cameras
     *  - List all the camera devices detected in the system
     *  - All the camera device name are listed in a QStringlist variable
     *  - E-con camera will be filtered from the available list
     *  - Flitered list is displayed to the view
     */
    void checkforDevice();

    /**
     * @brief Create a log file by passing to Logger class
     *  - A Log file will be created if the user call this function
     */
    void createLogger();

    /**
     * @brief setCurrentDevice
     *  - Used to get device index and pass it to the signals
     * @param
     *  deviceIndex - Selected from the UI, passed to this function
     *  deviceName - Selected from the UI, passed to this function
     */
    void setCurrentDevice(QString,QString);

    /**
     * @brief Write the data into log file by passing the data to Logger class
     *  - Data passed will be written to the log file
     * @param
     * msgType - Message type may debug, critical, warning, fatal
     * @param
     * tmpStr - Data to be written in the file
     */
    void logWriter(QtMsgType,QString);

    /**
     * @brief Write the data into log file by passing the data to Logger class
     *  - Data passed will be written to the log file
     * @param
     * tmpStr - Only Debug message type data to be written in the file
     */
    void logDebugWriter(QString);

    /**
     * @brief Write the data into log file by passing the data to Logger class
     *  - Data passed will be written to the log file
     * @param
     * tmpStr - Only Critical message type data to be written in the file
     */
    void logCriticalWriter(QString);
    /**
     * @brief selectedDeviceEnum - This slot contains the selected camera enum
     * @param selectedCameraEnum - Camera enum name
     */
    void selectedDeviceEnum(CommonEnums::ECameraNames selectedCameraEnum);
    //Added by Dhurka - 17th Oct 2016
    /**
     * @brief openHIDDevice - This slot is used to open HID device
     * @param deviceName - device name
     */
    void openHIDDevice(QString deviceName);

    void closeLibUsbDeviceAscella();

    // Added by Sankari: To notify user about warning : This slot will be called when warning from uvccamera.cpp[Ex: hid access needs sudo ]
    // 07 Dec 2017
    void notifyUser(QString title, QString text);

     // open event node file path  - open device event path file Ex: /dev/input/by-path/pci-0000:00:1a.0-usb-0:1.4:1.0-event
    void openEventNode(QString businfo);


signals:

    void setFirstCamDevice(int);
    void setCamName(QString);
    void logHandle(QtMsgType,QString);

    /**
     * @brief currentlySelectedCameraEnum - This signal is used to emit selected camera enum value to
     * qtcam.qml file
     * @param selectedDevice
     */
    void currentlySelectedCameraEnum(int selectedDevice);
    //Added by Dhurka - 18th Oct 2016
    /**
     * @brief initExtensionUnitSuccess - This signal is used to emit after HID initialization is success
     */
    void initExtensionUnitSuccess();

    // Added by Sankari: To notify user about warning[Ex: hid access from uvccamera.cpp]
    // 07 Dec 2017
    void notifyUserInfo(QString title, QString text);

};


#endif // CAMERAPROPERTY_H
