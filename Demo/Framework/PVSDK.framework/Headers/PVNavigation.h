//
//  PVNavigation.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import "PVBaseComponent.h"

typedef NS_ENUM(NSUInteger, PVWayPointSendState) {
    PVWayPointSendState_Timeout = -1,   ///< Send timeout
    PVWayPointSendState_Success = 2,    ///< Send successfully
    PVWayPointSendState_Failed  = 4     ///< Failed to send
};

typedef NS_ENUM(NSUInteger, PVSDK_Start_Waypoint) {
    PVSDK_Start_Waypoint_Timeout    = -1,   ///< Timeout
    PVSDK_Start_Waypoint_Start      = 0,    ///< Start
    PVSDK_Start_Waypoint_Stop       = 1     ///< Stop
};

@class PVNavigation;
@class PVFlightHelper;

@protocol PVNavigationDelegate <NSObject>

@optional

/**
 [PVNavigationDelegate] Send the waypoint delegate
 
 @param navigation PVNavigation
 @param sendState PVWayPointSendState
 */
- (void)pv_navigation:(PVNavigation *)navigation SendWayPointState:(PVWayPointSendState)sendState;

/**
 [PVNavigationDelegate] Current waypoint delegate
 
 @param navigation PVNavigation
 @param currentPoint currentPoint
 */
- (void)pv_navigation:(PVNavigation *)navigation UpdateWayPointCurrentPoint:(int)currentPoint;

/**
 [PVNavigationDelegate] Arrive at the waypoint delegate
 
 @param navigation PVNavigation
 @param reachedPoint reachedPoint
 */
- (void)pv_navigation:(PVNavigation *)navigation UpdateWayPointReachedPoint:(int)reachedPoint;

/**
 [PVNavigationDelegate] Execution timeout
 */
- (void)pv_navigationUpdateWayPointTimeOut;

/**
 [PVNavigationDelegate] Return to the last mode delegate
 
 @param navigation PVNavigation
 @param result YES: Success, NO: Failed
 */
- (void)pv_navigation:(PVNavigation *)navigation ChangeLastModeResult:(BOOL)result;

/**
 [PVNavigationDelegate] Update attitude delegte
 
 @param navigation PVNavigation
 @param helper PVFlightHelper
 */
- (void)pv_navigation:(PVNavigation *)navigation UpdateFlightAttitudeWithHelper:(PVFlightHelper *)helper;

@end

@interface PVNavigation : PVBaseComponent

@property (nonatomic, weak) id <PVNavigationDelegate>delegate;

/**
 Instantiation PVNavigation
 
 @return PVNavigation
 */
+ (instancetype)product;

/**
 Start to fly
 */
- (void)startToAutoMission;

/**
 Add way points[Please confirm the height is between 3 and 100 meters.！！！]
 
 @param wayPoints Way points Array. Class: PVWayPointModel Array.
 */
- (void)addLocationWayPoints:(NSArray *)wayPoints;

/**
 Switch to the last mode
 */
- (void)setLastMode;

/**
 Automatic return
 */
- (void)autoReturnToLand;

@end

