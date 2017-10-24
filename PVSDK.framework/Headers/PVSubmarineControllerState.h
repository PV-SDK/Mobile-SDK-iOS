//
//  PVSubmarineControllerState.h
//  PVSDK
//
//  Created by Layne on 2017/3/14.
//  Copyright © 2017年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  船体警报
 */
typedef NS_ENUM (NSInteger,PVRayAlarm){
    /**
     *  电池电量过低百分之10报警
     */
    PVRayAlarmLowBattery_10=0,
    /**
     *  电池电量过低百分之20报警
     */
    PVRayAlarmLowBattery_20=1,
    /**
     *  船体潜水过深
     */
    PVRayAlarmTooDeep,
    /**
     *  电机停转报警
     */
    PVRayAlarmMotorStall,
    /**
     *  左侧电机停转
     */
    PVRayAlarmMotorStallLeft,
    /**
     *  右侧电机停转
     */
    PVRayAlarmMotorStallleftRight,
    /**
     *  垂直电机停转
     */
    PVRayAlarmMotorStallleftVertical,
    /**
     *  船体未入水不能解锁
     */
    PVRayAlarmNotInfoWater,
    /**
     *  船体未激活不能解锁
     */
    PVRayAlarmNotActivated,
    /**
     *  船体碰撞报警
     */
    PVRayAlarmImpactDetected,
    /**
     *  船体出水报警
     */
    PVRayAlarmOutOfWater
    
    
    
};

/**
 *  Ray自检状态信息
 */
typedef struct
{
    /**
     *  水深计
     */
    BOOL isWaterDeepMeterWorking;
    /**
     *  电池
     */
    BOOL isBatteryWorking;
    /**
     *  罗盘
     */
    BOOL isCompassWorking;
    /**
     *  加速度计
     */
    BOOL isAccelerometerWorking;
    /**
     *  陀螺仪
     */
    BOOL isGyroscopeWorking;
}PVSubmarineSelfCheckingState;

/**
 *  速度模式
 */
typedef NS_ENUM(NSInteger,PVRaySpeedMode) {
    /**
     *  低
     */
    PVRaySpeedModeLow =1,
    /**
     *  中
     */
    PVRaySpeedModeMiddle,
    /**
     *  高
     */
    PVRaySpeedModeHigh
};
/**
 *  Ray姿态
 */
typedef struct
{
    /**
     *  俯仰角
     */
    double pitch;
    /**
     *  横滚角
     */
    double roll;
    /**
     *  偏航角
     */
    double yaw;
}PVSubmarineAttitudeState;

//////////////////////////////////////////////////
/// @brief 水下电机相关参数
///
/// 定义关于水下电机的相关参数
//////////////////////////////////////////////////
typedef struct RAY_ESC_PARAM {
    float voltage; ///< 电机电压
    float current; ///< 电机电流
    float phasecurrent; ///< ESC phase current
    unsigned int revocount; ///< 电机旋转总圈数
    unsigned int data1; ///< reserved1
    unsigned int data2; ///< reserved2
    unsigned int data3; ///< reserved3
    unsigned short rxthr; ///< 输入油门
    unsigned short realthr; ///< 输出油门
    unsigned short rpm; ///< 转速
    unsigned short mostemp; ///< 温度
    unsigned short statuscode; ///< 状态码
    unsigned char port; ///< 电机编号
    unsigned char direction; ///< 转向
} RAY_ESC_PARAM;

//////////////////////////////////////////////////
/// @brief 水下寻鱼器配对时的状态
///
/// 定义了水下寻鱼器配对时的状态
//////////////////////////////////////////////////
typedef enum PowerRay_PAIR_FISH_FINDER_STATE {
    PowerRay_PAIR_FISH_FINDER_STATE_CONNECT_ERROR = 0, //连接失败
    PowerRay_PAIR_FISH_FINDER_STATE_CURRENT_OK = 1, //当前配对的ssid与要配对的ssid相同
    PowerRay_PAIR_FISH_FINDER_STATE_SET_OK = 2, //设置寻鱼器ssid成功
    PowerRay_PAIR_FISH_FINDER_STATE_SAVE_OK = 3, //保存寻鱼器ssid成功
    PowerRay_PAIR_FISH_FINDER_STATE_SET_FAIL = 4, //设置ssid失败
    PowerRay_PAIR_FISH_FINDER_STATE_CONNECT_BREAK = 5 //链接断开
} PowerRay_PAIR_FISH_FINDER_STATE;


/**
 *  当前鱼钩状态
 */
typedef NS_ENUM(NSInteger,PVFishHookState) {
    /**
     *  放钩
     */
    PVFishHookStateON = 0,
    /**
     *  收钩
     */
    PVFishHookStateOFF
};


/**
 *  速度模式
 */
typedef NS_ENUM(NSInteger,PVRayDepthState) {
    /**
     *  定深关
     */
    PVRayDepthStateOFF =1,
    /**
     *  定深开
     */
    PVRayDepthStateON,
};


@interface PVSubmarineControllerState : NSObject

/**
 *  亮度
 */
@property (nonatomic,assign) int lightValue;

/**
 *  主副控状态
 */
@property (nonatomic,assign) BOOL isMasterControl;

/**
 *  深度
 */
@property (nonatomic,assign) float depth;

/**
 *  电量百分比
 */
@property (nonatomic,assign) int currentBattery;

/**
 *  电压
 */
@property (nonatomic,assign) float batteryVoltage;

/**
 *  当前基站电量
 */
@property (nonatomic,assign) int baseStationBattery;


/**
 当前船体解锁状态  YES为解锁，NO为加锁
 */
@property (nonatomic,assign) BOOL isArmRay;

/**
 *  水下报警信息
 */
@property (nonatomic,assign) PVRayAlarm rayAlarm;

/**
 *  是否是定深模式
 */
@property (nonatomic,assign) PVRayDepthState depthMode;

/**
 *  速度模式
 */
@property (nonatomic,assign) PVRaySpeedMode raySpeedMode;

/**
 电机旋转总圈数
 */
@property (nonatomic,assign) int electronicRevoCount;

/**
 电机编号
 */
@property (nonatomic,assign) int electronicPort;

/**
 *  鱼钩当前状态
 */
@property (nonatomic,assign) PVFishHookState fishHookState;

/**
 当前Ray姿态
 */
@property (nonatomic,assign) PVSubmarineAttitudeState rayAttituState;


@end
