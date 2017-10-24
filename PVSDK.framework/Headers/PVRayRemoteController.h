//
//  PVRayRemoteController.h
//  PVSDK
//
//  Created by Layne on 2017/5/4.
//  Copyright © 2017年 Layne. All rights reserved.
//

#import <PVSDK/PVSDK.h>
#import "PVRayRemoteControllerState.h"

typedef void (^PVRayRCBatteryBlock)(NSInteger battery);

typedef NS_ENUM(NSInteger,PVRayRemoteStateUpdate){
    //连接状态更新
    PVRayRemoteStateUpdateConnect,
    //遥控器指令更新
    PVRayRemoteStateUpdateCommond,
};

/**
 *  Ray遥控器模式
 */
typedef NS_ENUM(NSInteger,PVRayRCMode) {
    /**
     *  日本手
     */
    PVRayRCMode1=1,
    /**
     *  美国手
     */
    PVRayRCMode2,
    /**
     *  中国手
     */
    PVRayRCMode3,
    /**
     *  自定义
     */
    PVRayRCMode4,
};

@class PVRayRemoteController;
@protocol PVRayRemoteControllerDelegate <NSObject>

- (void)rayRemoteController:(PVRayRemoteController *)rc didUpdateRCState:(PVRayRemoteControllerState*)state stateType:(PVRayRemoteStateUpdate)stateUpdate;

@end

@interface PVRayRemoteController : PVBaseComponent

@property (nonatomic,weak)id <PVRayRemoteControllerDelegate>delegate;

@property (nonatomic,strong)PVRayRemoteControllerState *state;

/**
 遥控器电量回调
 */
@property (nonatomic,strong) PVRayRCBatteryBlock batteryBlock;

/**
 *  设置遥控器模式
 *
 *  @param rcMode 遥控器模式
 *  @param block  设置结果
 */
- (void)setRCMode:(PVRayRCMode)rcMode withCompletion:(PVCompletionBlock)block;

/**
 *  获取遥控器模式
 *
 *  @param block 获取结果
 */
- (void)getRCModeWithComplection:(void (^_Nonnull)(PVRayRCMode rcMode,NSError *_Nullable error))block;

/**
 获取遥控器固件版本号

 @param block 回调
 */
- (void)getRCVersionWithComplection:(void(^_Nonnull)(float version,NSError *_Nullable error))block;

/**
 监听VR按键点击状态

 @param block 按键回调
 */
- (void)getRCVRButtonStateWithComplection:(void(^_Nonnull)(PVRayRemoteControllerState * _Nullable State,NSError *_Nullable error))block;

/**
 获取遥控器升级状态
 
 @param block 获取遥控器升级状态回调
 */
- (void)getRemoteControllerUpgradeStateWithComloection:(void (^_Nonnull)(PVRCUpgradeState UpgradeState,NSError * _Nullable error))block;

/**
 遥控器配对

 @param ssid 要配对的SSID  格式为：PRA_Station_xxxxxx
 @param ip 基站iP地址
 @param port 端口号
 @param block 配对回调
 */
- (void)matchUpRemoteControllerWithSSID:(NSString * _Nullable)ssid andIPAdress:(NSString * _Nullable)ip andPort:(int)port withComplection:(void (^_Nonnull)(PVRCMatcheState matcheState,NSError *_Nullable error))block;



@end
