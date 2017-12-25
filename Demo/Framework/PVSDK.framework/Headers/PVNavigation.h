//
//  PVNavigation.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, PVWayPointSendState) {
    PVWayPointSendState_Timeout = -1,   ///< 发送超时
    PVWayPointSendState_Success = 2,    ///< 发送成功
    PVWayPointSendState_Failed  = 4     ///< 发送失败
};

@class PVNavigation;
@class PVFlightHelper;

@protocol PVNavigationDelegate <NSObject>

@optional

/**
 [PVNavigationDelegate] 发送航点

 @param navigation PVNavigation
 @param sendState PVWayPointSendState
 */
- (void)pv_navigation:(PVNavigation *)navigation SendWayPointState:(PVWayPointSendState)sendState;

/**
 [PVNavigationDelegate] 当前航点

 @param navigation PVNavigation
 @param currentPoint currentPoint
 */
- (void)pv_navigation:(PVNavigation *)navigation UpdateWayPointCurrentPoint:(int)currentPoint;

/**
 [PVNavigationDelegate] 到达航点

 @param navigation PVNavigation
 @param reachedPoint reachedPoint
 */
- (void)pv_navigation:(PVNavigation *)navigation UpdateWayPointReachedPoint:(int)reachedPoint;

/**
 [PVNavigationDelegate] 执行航点超时
 */
- (void)pv_navigationUpdateWayPointTimeOut;

/**
 [PVNavigationDelegate] 返回上一个模式

 @param navigation PVNavigation
 @param result YES: Success, NO: Failed
 */
- (void)pv_navigation:(PVNavigation *)navigation ChangeLastModeResult:(BOOL)result;

/**
 [PVNavigationDelegate] 姿态

 @param navigation PVNavigation
 @param helper PVFlightHelper
 */
- (void)pv_navigation:(PVNavigation *)navigation UpdateFlightAttitudeWithHelper:(PVFlightHelper *)helper;

@end

@interface PVNavigation : NSObject

@property (nonatomic, weak) id <PVNavigationDelegate>delegate;

+ (PVNavigation *)shareNavigation;

/**
 开始航线飞行
 */
- (void)startToAutoMission;

/**
 First: Add way points

 @param wayPoints Way points Array.
 */
- (void)addLocationWayPoints:(NSArray *)wayPoints;

/**
 切回上一个模式
 */
- (void)setLastMode;

/**
 自动返航
 */
- (void)autoReturnToLand;

@end
