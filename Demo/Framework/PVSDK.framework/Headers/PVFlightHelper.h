//
//  PVFlightHelper.h
//  PVSDK
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import <PVSDK/PVSDK.h>
#import <CoreLocation/CoreLocation.h>

typedef struct{
    double pitch;       ///< Aircraft's pitch attitude value.
    double roll;        ///< Aircraft's roll attitude value.
    double yaw;         ///< Aircraft's yaw attitude value.
    double pitchSpeed;  ///< Aircraft's pitch speed attitude value.
    double rollSpeed;   ///< Aircraft's roll speed attitude value.
    double yawSpeed;    ///< Aircraft's yaw speed attitude value.
} PVFlightAttitude;

/**
 *  航线飞行状态提醒
 */
typedef NS_ENUM(NSInteger,PVFlightAutoMissionState) {
    /**
     *  未执行航线
     */
    PVFlightAutoMissionStateNoDo,
    /**
     *  航线飞行中
     */
    PVFlightAutoMissionStateRunning,
    /**
     *  航线飞行完成
     */
    PVFlightAutoMissionStateFinish,
};

typedef NS_ENUM (NSUInteger, PVSDK_Mode_Changed){
    PVSDK_Mode_Changed_Timeout      = -1,   ///< Time out
    PVSDK_Mode_Changed_             = 0,    ///< Change
    PVSDK_Mode_Changed_MANUAL       = 1,    ///< Manual mode
    PVSDK_Mode_Changed_ALTCTL       = 2,    ///< Altctl mode
    PVSDK_Mode_Changed_POSCTL       = 3,    ///< Posctl mode
    PVSDK_Mode_Changed_AUTOMISSION  = 4,    ///< Auto mission mode
    PVSDK_Mode_Changed_AUTOTAKEOFF  = 5,    ///< Auto takeoff mode
    PVSDK_Mode_Changed_AUTOLAND     = 6,    ///< Auto land mode
    PVSDK_Mode_Changed_AUTORTL      = 7,    ///< Auto rtl mode
    PVSDK_Mode_Changed_SUPERSIMPLE  = 8,    ///< Super simple mode
    PVSDK_Mode_Changed_AUTOCIRCLE   = 9,    ///< Auto circle mode
    PVSDK_Mode_Changed_FOLLOWME     = 10,   ///< Follow me mode
    PVSDK_Mode_Changed_AUTOLOITER   = 11    ///< Auto loiter mode
};

@interface PVFlightHelper : NSObject

+ (PVFlightHelper *)shareHelper;

/**
 *  当前模式
 */
@property(nonatomic, assign) PVSDK_Mode_Changed flightMode;

/**
 *  当前模式名称（返回字符串）
 */
@property(nonatomic, copy) NSString *flightModeName;

/**
 当前姿态信息
 */
@property(nonatomic, assign) PVFlightAttitude attitude;

/**
 航线状态
 */
@property (nonatomic, assign) PVFlightAutoMissionState autoMissionState;

/**
 卫星颗数
 */
@property (nonatomic, assign) int satelliteCount;

/**
 地速
 */
@property(nonatomic, assign) float groundspeed;
/**
 爬升速度
 */
@property(nonatomic, assign) float climb;
/**
 当前地理坐标
 */
@property(nonatomic, assign) CLLocationCoordinate2D aircraftLocation;
/**
 海拔高度
 */
@property(nonatomic, assign) float altitude;
/**
 对地高度
 */
@property(nonatomic, assign) float groundHeight;

/**
 大地坐标X轴速度
 */
@property(nonatomic, assign) float xSpeed;

/**
 大地坐标Y轴速度
 */
@property(nonatomic, assign) float ySpeed;

/**
 大地坐标Z轴速度
 */
@property(nonatomic, assign) float zSpeed;

@end
