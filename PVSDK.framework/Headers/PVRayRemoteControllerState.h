//
//  PVRayRemoteControllerState.h
//  PVSDK
//
//  Created by Layne on 2017/5/10.
//  Copyright © 2017年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger,PVRayRCCommand) {
    /**
     *  拍照
     */
    PVRayRCCommandShoot,
    /**
     *  录像
     */
    PVRayRCCommandRec,
    /**
     *  寻鱼
     */
    PVRayRCCommandFindfish,
    /**
     *  未知
     */
    PVRayRCCommandUnknown,
    /**
     *  VR按钮按下
     */
    PVRayRCCommandVRPress,
    /**
     *  VR按钮松开
     */
    PVRayRCCommandVRRelease,
};

/**
 遥控器升级状态
 */
typedef NS_ENUM(NSInteger,PVRCUpgradeState) {
    /**
     *  升级成功
     */
    PVRCUpgradeStateSuccess,
    /**
     *  升级中
     */
    PVRCUpgradeStateUpgrading,
    /**
     *  升级中
     */
    PVRCUpgradeStateFailed,
};

/**
 遥控器配对状态
 */
typedef NS_ENUM(NSInteger,PVRCMatcheState) {
    /**
     *  连接失败
     */
    PVRCMatcheStateConnectError = 0,
    /**
     *  当前配对的ssid与要配对的ssid相同
     */
    PVRCMatcheStateCurrentOK,
    /**
     *  设置遥控器ssid成功
     */
    PVRCMatcheStateSetOK,
    /**
     *  保存遥控器ssid成功
     */
    PVRCMatcheStateSetSaveOK,
    /**
     *  设置ssid失败
     */
    PVRCMatcheStateSetSetFail,
    /**
     *  链接断开
     */
    PVRCMatcheStateSetConnectBreak
};
@interface PVRayRemoteControllerState : NSObject

@property (nonatomic,assign)BOOL isRayRemoteConnect;

@property (nonatomic,assign)PVRayRCCommand rayRCCommond;
/**
 遥控器升级状态
 */
@property (nonatomic,assign)PVRCUpgradeState RCUpgradeState;

@end
