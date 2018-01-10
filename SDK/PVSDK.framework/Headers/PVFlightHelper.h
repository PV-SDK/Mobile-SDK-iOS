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
 *  Flight status alerts
 */
typedef NS_ENUM(NSInteger,PVFlightAutoMissionState) {
    /**
     *  Unexecuted
     */
    PVFlightAutoMissionStateNoDo,
    /**
     *  Flying in route
     */
    PVFlightAutoMissionStateRunning,
    /**
     *  Complete the flight
     */
    PVFlightAutoMissionStateFinish,
};

typedef NS_ENUM (NSUInteger, PVSDK_Mode_Changed){
    PVSDK_Mode_Changed_Timeout      = -1,   ///< Time out
    PVSDK_Mode_Changed_             = 0,    ///< Change
    PVSDK_Mode_Changed_Manual       = 1,    ///< Manual mode
    PVSDK_Mode_Changed_Altctl       = 2,    ///< Altctl mode
    PVSDK_Mode_Changed_Posctl       = 3,    ///< Posctl mode
    PVSDK_Mode_Changed_Automission  = 4,    ///< Auto mission mode
    PVSDK_Mode_Changed_Autotakeoff  = 5,    ///< Auto takeoff mode
    PVSDK_Mode_Changed_Autoland     = 6,    ///< Auto land mode
    PVSDK_Mode_Changed_Autortl      = 7,    ///< Auto rtl mode
    PVSDK_Mode_Changed_Supersimple  = 8,    ///< Super simple mode
    PVSDK_Mode_Changed_Autocircle   = 9,    ///< Auto circle mode
    PVSDK_Mode_Changed_Followme     = 10,   ///< Follow me mode
    PVSDK_Mode_Changed_Autoloiter   = 11    ///< Auto loiter mode
};

@interface PVFlightHelper : NSObject

/**
 Instantiation Helper
 
 @return PVFlightHelper
 */
+ (instancetype)helper;

/**
 Aircraft mode
 */
@property(nonatomic, assign) PVSDK_Mode_Changed flightMode;

/**
 The name of current mode（returns the string）
 */
@property(nonatomic, copy) NSString *flightModeName;

/**
 Current attitude information
 */
@property(nonatomic, assign) PVFlightAttitude attitude;

/**
 Flight route status
 */
@property (nonatomic, assign) PVFlightAutoMissionState autoMissionState;

/**
 Satellite number
 */
@property (nonatomic, assign) int satelliteCount;

/**
 Ground speed
 */
@property(nonatomic, assign) float groundspeed;

/**
 Climbing speed
 */
@property(nonatomic, assign) float climb;

/**
 Geographical coordinates
 */
@property(nonatomic, assign) CLLocationCoordinate2D aircraftLocation;

/**
 Height above sea level
 */
@property(nonatomic, assign) float altitude;

/**
 The height above ground
 */
@property(nonatomic, assign) float groundHeight;

/**
 X axis velocity of geodetic coordinate
 */
@property(nonatomic, assign) float xSpeed;

/**
 Y axis velocity of geodetic coordinate
 */
@property(nonatomic, assign) float ySpeed;

/**
 Z axis velocity of geodetic coordinate
 */
@property(nonatomic, assign) float zSpeed;

@end

