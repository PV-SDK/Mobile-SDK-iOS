//
//  PVFlightControllerState.h
//  PVSDK
//
//  Created by Layne on 16/4/22.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef NS_ENUM(NSUInteger,PVFlightConnectState){
    /**
     *  链路连接中
     */
    PVFlightConnectStateTCPConnecting=0,
    
    //链路连接成功
    PVFlightConnectStateTCPSuccess=1,
    
    //链路连接断开
    PVFlightConnectStateTCPDisConnect=2,
    
    //链路连接超时
    PVFlightConnectStateTCPTimeOut=3,
    
    //链路连接失败
    PVFlightConnectStateTCPFailed=4,
    
    //心跳超时
    PVFlightConnectStateHeartTimeout=5,

    //标准遥控器已连接
    PVFlightConnectRemoteConnected =6,
    
    //体感遥控器已连接
    PVFlightConnectStateTGConnected=7,
    
    //飞机连接中
    PVFlightConnectStateConnecting=8,
    
    //飞机已连接
    PVFlightConnectStateConnected=9,
    
    //飞行器连接断开
    PVFlightConnectStateDisConnected=10,
    
    //飞机连接超时
    PVFlightConnectStateTimeout = 11,
    
    //飞机连接失败
    PVFlightConnectStateFailed=12,
    
    //水下机器人已连接
    PVFlightStateRayConnected=13,
    
    //心跳恢复
    PVFlightConnectStateHeartTimeoutReply=14,
    
    //水下基站连接失败
    PVFlightConnectStateRayBaseStationConnectFailed=15,
};

typedef NS_ENUM(NSUInteger,PVFlighParamSetState){
    /**
     *  设置成功
     */
    PVFlighParamSetStateSuccess,
    /**
     *  设置失败
     */
    PVFlighParamSetStateFail,
};

typedef NS_ENUM (NSUInteger, PVFlightMode){
    /**
     *  Manual mode.手动模式
     */
    PVFlightModeManual = 1,
    /**
     *  Alt ctl mode.定高模式（暂时不用）
     */
    PVFlightModeAltCtl = 2,
    /**
     *  Post ctl mode.定点模式
     */
    PVFlightModePostCtl = 3,
    /**
     *  Mission mode.航线飞行
     */
    PVFlightModeMission = 4,
    /**
     *  Auto takeoff mode.自动起飞
     */
    PVFlightModeTakeOff = 5,
    /**
     *  Auto landing mode.自动降落
     */
    PVFlightModeAutoLand = 6,
    /**
     *  Auto rtl mode.自动返航
     */
    PVFlightModeAutoRtl = 7,
    /**
     *  Super simple mode.极简模式
     */
    PVFlightModeSuperSimple = 8,
    /**
     *  Auto circle mode.环绕模式
     */
    PVFlightModeAutoCirCle = 9,
    /**
     *  Auto follow mode.跟随模式
     */
    PVFlightModeAutoFollow = 10,
    /**
     *  Auto loiter mode.自动悬停（暂时不用）
     */
    PVFlightModeAutoLoiter = 11,
    /**
     *  航线飞行执行完成
     */
    PVFlightModeMissionFinished=12,
    /**
     *  环绕模式暂停
     */
    PVFlightModeAutoCirClePause=13,
};

/**
 *  航线飞行状态提醒
 */
typedef NS_ENUM(NSInteger,PVAutoMissionState) {
    /**
     *  未执行航线
     */
    PVAutoMissionStateNoDo,
    /**
     *  航线飞行中
     */
    PVAutoMissionStateRunning,
    /**
     *  航线飞行完成
     */
    PVAutoMissionStateFinish,
};

/**
 *  飞机报警信息
 */
typedef NS_ENUM(NSInteger,PVAlarmMessage) {
    /**
     *  飞机起飞
     */
    PVAlarmMessageTakeOff=1,
    /**
     *  起飞完成
     */
    PVAlarmMessageTakeOffFinish,
    /**
     *  飞机降落
     */
    PVAlarmMessageLand,
    /**
     *  降落完成
     */
    PVAlarmMessageLandFinish,
    /**
     *  飞行器进入极简模式保护圈，请您向圈外移动
     */
    PVAlarmMessageInSuperRadius=5,
    /**
     *  遥控器位置(飞机会广播遥控器位置,不用播报)
     */
    PVAlarmMessageRCPos=6,
    /**
     *  返航点位置(飞机会广播返航点器位置,不用播报)
     */
    PVAlarmMessageRTLPos=7,
    /**
     *  飞行器电量达到返航阈值，是否返航--
     */
    PVAlarmMessageLowBatRTL=8,
    /**
     *  飞行器电量过低，开始自动降落
     */
    PVAlarmMessageLandAuto=9,
    /**
     *  飞行器电量过低，开始自动降落
     */
    PVAlarmMessageLandAutoOther=10,
    /**
     *  IMU传感器温度异常
     */
    PVAlarmMessageIMUTemWarn=11,
    /**
     *  传感器初始化失败,无法解锁
     */
    PVAlarmMessageSenrosNoInit=12,
    /**
     *  当前处于新手模式下,GPS信号较差无法解锁飞机
     */
    PVAlarmMessageNewUserNoGPS=13,
    /**
     *  当前飞机处于禁飞内区,无法解锁
     */
    PVAlarmMessageInGROVE=14,
    /**
     *  当前飞机电量过低,无法解锁,请先对电池充电
     */
    PVAlarmMessageSuperLowBattery=15,
    /**
     *  飞机未插入SD卡,无法解锁
     */
    PVAlarmMessageNoScard=16,
    /**
     *  极简模式下,飞行器GPS信号较差无法解锁 +++++
     */
    PVAlarmMessageSuperSimpleLowGPS=17,
    /**
     *  极简模式下遥控器GPS信号差,无法解锁飞机,请检查遥控器连接是否正常
     */
    PVAlarmMessageSuperSimpleNoRCLoc=18,
    /**
     *  飞行器水平无法定位,无法切换到定点模式
     */
    PVAlarmMessageLowGPSInvalidPosCtl=19,
    /**
     *  飞机GPS信号较差,无法切换到跟随模式
     */
    PVAlarmMessageLowGPSInvalidFollow=20,
    /**
     *  飞机GPS信号较差,无法切换到环绕模式
     */
    PVAlarmMessageLowGPSInvalidCycle=21,
    /**
     *  飞机GPS信号较差,无法切换到极简模式
     */
    PVAlarmMessageLowGPSInvalidSuperSimple=22,
    /**
     *  飞机GPS信号较差,无法切换到返航模式
     */
    PVAlarmMessageLowGPSInvalidRTL=23,
    /**
     *  飞机GPS信号较差,无法切换到悬停模式
     */
    PVAlarmMessageLowGPSInvalidLoiter=24,
    /**
     *  飞机GPS信号较差,无法进行航线规划
     */
    PVAlarmMessageLowGPSInvalidMission=25,
    /**
     *  未获取到遥控器位置,拒绝切换到跟随模式
     */
    PVAlarmMessageNoRCPosInvalidFollow=26,
    /**
     *  未获取到遥控器位置,拒绝切换到环绕模式
     */
    PVAlarmMessageNoRCPosInvalidCycle=27,
    /**
     *  未获取遥控器位置,拒绝切换到极简模式
     */
    PVAlarmMessageNoRCPosInvalidSuperSimple=28,
    /**
     *  未获取到起飞点位置,飞机无法自动返航,请手动将飞机拉回
     */
    PVAlarmMessageNoHomePosInvalidAutoRtl=29,
    /**
     *  未获取到起飞点位置,无法执行航线规划
     */
    PVAlarmMessageNoHomePosInvalidMission=30,
    /**
     *  无法获得高度信息
     */
    PVAlarmMessageNoAltInvalidAutoTakeOff=31,
    /**
     *  飞行器水平无法定位,无法自动起飞
     */
    PVAlarmMessageLowPosInvalidAutoTakeOff=32,
    /**
     *  飞行器水平无法定位,无法自动降落
     */
    PVAlarmMessageLowPosInvalidAutoLand=33,
    /**
     *  水平无法定位,已切换到手动模式,请谨慎操控飞机
     */
    PVAlarmMessageLowPosChangeMan=34,
    /**
     *  遥控器信号丢失
     */
    PVAlarmMessageLostRC=35,
    /**
     *  遥控器信号已获得
     */
    PVAlarmMessageConnectRC=36,
    /**
     *    超声异常，无法解锁
     */
    PVAlarmMessageLostRCChangeLoiter=37,
    /**
     *   光流异常，无法解锁
     */
    PVAlarmMessageLostRCChangeRTL=38,
    /**
     *      GPS异常，无法解锁
     */
    PVAlarmMessageLostRCChangeLand=39,
    /**
     *  磁传感器异常，无法解锁
     */
    PVAlarmMessageNoGPSLand=40,
    /**
     *  加速度计异常，无法解锁
     */
    PVAlarmMessageOpenFail=41,
    /**
     *  陀螺仪异常，无法解锁
     */
    PVAlarmMessageCloseFail=42,
    /**
     *  遥控器电量过低,请及时对遥控器充电
     */
    PVAlarmMessageRCLowBatttery=43,
    /**
     *  飞机到达安全区域边界,即将返航
     */
    PVAlarmMessageNearFence=44,
    /**
     *  飞行器GPS信号丢失，切换到定点模式
     */
    PVAlarmMessageNOGPSPosctl=45,
    /**
     *  遥控器GPS信号差，切换到定点模式  --------
     */
    PVAlarmMessageLostRCGPSPosctl=46,
    /**
     *  光流失效，无法切换到定点模式
     */
    PVAlarmMessageLoseFollowNOPosctl=47,
    /**
     *  高度超出超声范围，无法切换到定点模式
     */
    PVAlarmMessageBeyondSoundNOPosctl=48,
    /**
     *  光流失效，切换到手动模式
     */
    PVAlarmMessageLostFollowManual=49,
    /**
     *  高度超出超声范围，切换到手动模式
     */
    PVAlarmMessageBeyondSoundManual=50,
    /**
     *  光流失效
     */
    PVAlarmMessageLostFollow=51,
    /**
     *  高度超出超声范围
     */
    PVAlarmMessageBeyondSound=52,
    /**
     *  遥控器下行链路中断
     */
    PVAlarmMessageRCDownLinkBreak=53,
    /**
     *  飞行器闯入禁飞区，请将飞行器拉回
     */
    PVAlarmMessageTriggerFence=54,
    /**
     *  当前模式下无法解锁,等待GPS搜索卫星或切换到手动模式解锁（无法切换到当前模式）--------
     */
    PVAlarmMessageNOCurrentModeNOArm=55,
    /**
     *   遥控器GPS信号差，无法设置返航点为用户位置  ------
     */
    PVAlarmMessageNORCPosNOPersonRTL=56,
    /**
     *   气压计异常，无法解锁
     */
    PVAlarmMessageBarometerErrorNOArm=57,
    /**
     *   无法获取到电池电量，无法解锁
     */
    PVAlarmMessageNOBatteryNOArm=58,
    
    /**
     *   电池通信异常，建议降落飞行器
     */
    PVAlarmMessageBatteryError=59,
    /**
     *   飞行器闯入禁飞区，即将返航
     */
    PVAlarmMessageInGroveRTL=61,
    /**
     *   飞行器闯入禁飞区，即将原地降落
     */
    PVAlarmMessageInGroveLand=62,
    /**
     *   到达禁飞区边缘，飞机即将悬停，请将飞机拉回
     */
    PVAlarmMessageInGroveWait=63,
};

/**
 *  飞行器定位方式
 */
typedef NS_ENUM(NSInteger,PVFlightLocatingType) {
    /**
     *  GPS定位
     */
    PVFlightLocatingTypeGPS,
    /**
     *  光流定位
     */
    PVFlightLocatingTypeFollow,
};

typedef struct
{
    /**
     *  Aircraft's pitch attitude value.
     */
    double pitch;
    /**
     *  Aircraft's roll attitude value.
     */
    double roll;
    /**
     *  Aircraft's yaw attitude value.
     */
    double yaw;
} PVAttitude;

/**
 *  飞机自检状态信息
 */
typedef struct
{
    /**
     *  GPS
     */
    BOOL isGPSWorking;
    /**
     *  气压计
     */
    BOOL isBarometerWorking;
    /**
     *  陀螺仪
     */
    BOOL isGyroWorking;
    /**
     *  磁力计
     */
    BOOL isMagnetometerWorking;
    /**
     *  加速度计
     */
    BOOL isAccelerometerWorking;
    /**
     *  IMU
     */
    BOOL isIMUWorking;
    /**
     *  光流
     */
    BOOL isOpticalFlow;
    /**
     *  超声
     */
    BOOL isSonar;
    /**
     *  电池
     */
    BOOL isBatteryWorking;
    /**
     *  RC
     */
    BOOL isRCWorking;
    /**
     *  相机SD卡
     */
    BOOL isCameraSDWorking;
    /**
     *  云台
     */
    BOOL isGimabalWorking;
    /**
     *  飞行器模式
     */
    PVFlightMode flightMode;
}PVSelfCheckingState;

@interface PVFlightControllerState : NSObject

/**
 *  飞机连接状态
 */
@property (nonatomic,assign) PVFlightConnectState flightConnectState;
/**
 *  参数设置状态
 */
@property (nonatomic,assign) PVFlighParamSetState flightParamSetState;
/**
 *  卫星颗数
 */
@property (nonatomic,assign) int satelliteCount;
/**
 *  home点地理坐标
 */
@property(nonatomic, assign) CLLocationCoordinate2D homeLocation;
/**
 *  返航点地理坐标
 */
@property(nonatomic, assign) CLLocationCoordinate2D returnLandLocation;
/**
 *  飞机当前地理坐标
 */
@property(nonatomic, assign) CLLocationCoordinate2D aircraftLocation;
/**
 *  飞机当前高度
 */
@property(nonatomic, assign) float altitude;
/**
 *  飞机当前电量
 */
@property(nonatomic,assign) int currentBattery;
/**
 *  飞机当前电压
 */
@property(nonatomic,assign) float batteryVoltage;
/**
 *  飞机空速
 */
@property(nonatomic, assign) float airspeed;
/**
 *  飞机地速
 */
@property(nonatomic,assign) float groundspeed;
/**
 *  飞机爬升速度
 */
@property(nonatomic,assign) float climb;
/**
 *  飞机当前姿态信息
 */
@property(nonatomic,assign) PVAttitude attitude;
/**
 *  飞机当前模式
 */
@property(nonatomic,assign)PVFlightMode flightMode;
/**
 *  飞机当前模式名称（返回字符串）
 */
@property(nonatomic,copy)NSString *flightModeName;

/**
 *  航线飞行状态
 */
@property(nonatomic,assign)PVAutoMissionState autoMissionState;

/**
 *  飞机警报信息
 */
@property(nonatomic,assign)PVAlarmMessage alarmMessage;

/**
 *  飞机器定位方式
 */
@property(nonatomic,assign)PVFlightLocatingType locatingType;

@end
