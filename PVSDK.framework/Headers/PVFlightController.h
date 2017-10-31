/**
 * @file PVFlightController.h
 * @author Layne
 * Created by Layne on 17/8/22.
 * Copyright © 2017年 Layne. All rights reserved.
 *
 * @brief 飞行接口文件
 *
 */

/**
 * @defgroup PVSDK_CORE_API_FLIGHTCONTROL 核心SDK飞行相关接口
 * @{
 */

/**
 * @page flight-page 飞行器接口
 */

#import <Foundation/Foundation.h>
#import "PVBaseComponent.h"
#import "PVFlightControllerState.h"

////////////////////////////////////////
/// @brief 飞行器状态类型
///
/// 定义了飞行器状态类型
////////////////////////////////////////
typedef enum _PVStateUpdate{
    PVFlightConnectStateUpdate, ///< 连接状态更新
    PVAttitudeStateUpdate, ///< 飞行器姿态更新
    PVAircraftPositionStateUpdate, ///< 飞行器位置更新
    PVHomePositionStateUpdate, ///< 飞行器Home点更新
    PVGPSCountStateUpdate, ///< 飞行器卫星颗数更新
    PVBatteryStateUpdate, ///< 飞行器电池电量更新
    PVModeStateUpdate, ///< 飞行器模式更新
    PVFlighParamSetStateUpdate, ///< 飞行器返航点更新
    PVFlightLandPositionStateUpdate, ///< 飞行器返航点更新
    PVAlarmMessageUpdate, ///< 报警信息更新
    PVAutoMissionStateUpdate, ///< 任务状态更新
    PVFlightLocatingTypeUpdate, ///< 定位方式更新
}PVStateUpdate;

@class PVFlightController;
@protocol PVFlightControllerDelegate <NSObject>

@optional

/**
 *  飞机信息改变时回调
 *
 *  @param fc    flightController
 *  @param state 飞机信息
 */
- (void)flightController:(PVFlightController *)fc didUpdateFlightState:(PVFlightControllerState *)state stateType:(PVStateUpdate)stateUpdate;

@end

@interface PVFlightController : PVBaseComponent

/**
 设备当前状态
 */
@property (nonatomic,strong) PVFlightControllerState *flightControllerState;

/**
 设备当前连接状态
 */
@property (nonatomic,assign)PVFlightConnectState flightConnectState;

@property (nonatomic,weak)id <PVFlightControllerDelegate>delegate;

/**
 *  开始连接飞机
 *
 *  @return 成功与失败是指连接方法的调用，不是飞行器连接成功与否，飞行器连接状态需要从代理方法中获取（didUpdateFlightState）
 */
- (void)startConnectFlightBlockWithSuccess:(void (^)(PVFlightController *fc))success failure:(void (^)(PVFlightController *fc))failure;

/**
 *  断开飞机连接
 *
 *  @return 成功返回YES，否则返回NO
 */
- (BOOL)stopConnectFlight;

/**
 *  重连飞机
 *
*/
- (void)reConnectTCPAndAircraft;

@end

/**  @} */
