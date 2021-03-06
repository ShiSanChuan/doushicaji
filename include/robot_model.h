#ifndef RMDEMO_ROBOT_MODEL_H
#define RMDEMO_ROBOT_MODEL_H

#include "serial_port.h"
#include "serial_packet.h"
#include "serial_interface.h"
#include "usb_capture_with_thread.h"
#include "basic_tool.h"
// DJI OSDK includes
#include "dji_status.hpp"
#include <dji_vehicle.hpp>

// Helpers
#include <dji_linux_helpers.hpp>
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

class RobotModel {
public:
    RobotModel();
    ~RobotModel();
public:
    int init(int argc, char** argv);

private://硬件资源
    UsbCaptureWithThread mUsbCapture;
    SerialInterface mSerialInterface;
    

private://机器人数据模型
    pthread_mutex_t dataMutex = PTHREAD_MUTEX_INITIALIZER; //互斥变量锁
    unsigned char mRobotId;//机器人id
    RobotMode mCurrentMode;//机器人当前运行模式
    float mCurrentPitch=0;//当前云台pitch角度
    float mCurrentYaw=0;//当前云台yaw角度
    TypeMap<TOPIC_STATUS_FLIGHT>::type     mFlightStatus;
    TypeMap<TOPIC_GPS_FUSED>::type         mLatLon;
    TypeMap<TOPIC_ALTITUDE_FUSIONED>::type mAltitude;
    TypeMap<TOPIC_RC>::type                mRc;
    TypeMap<TOPIC_VELOCITY>::type          mVelocity;
    TypeMap<TOPIC_QUATERNION>::type        mQuaternion;
    BasicTool basictool;
public://硬件资源获取函数接口
    UsbCaptureWithThread* getpUsbCapture();
    SerialInterface* getpSerialInterface();

public://机器人具体数据读写函数接口
    /*******系统框架调用接口，机器人数据更新*****/
    void mcuDataUpdate(float pitch,float yaw);
    void DataUpdate(SerialPacket recv_packet)
    /**************用户接口****************/
    Point3f getCurrentVelocity();
    Point3f getCurrentAngle();
    unsigned char getRobotId();
    RobotMode getCurrentMode();
};

#endif //RMDEMO_ROBOT_MODEL_H
