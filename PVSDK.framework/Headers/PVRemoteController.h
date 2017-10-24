//
//  PVRemoteController.h
//  PVSDK
//
//  Created by Layne on 16/7/13.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <PVSDK/PVSDK.h>


typedef NS_ENUM(NSInteger,PVRemoteCalibrateState)
{
    PVRemoteCalibrateStateBegin,
    PVRemoteCalibrateStateEnd,
    PVRemoteCalibrateStateOnlyRead,
};

typedef NS_ENUM(NSUInteger,PVRemoteConnectState){
    /**
     *  连接中
     */
    PVRemoteConnectStateConnecting,
    /**
     *  已连接
     */
    PVRemoteConnectStateConnected,
    /**
     *  体感遥控器已连接
     */
    PVRemoteConnectStateTGConnected,
    /**
     *  连接断开
     */
    PVRemoteConnectStateDisConnected,
    /**
     *  连接超时
     */
    PVRemoteConnectStateTimeout,
    /**
     *  心跳超时
     */
    PVRemoteConnectStateHeartTimeout,
    /**
     *  连接失败
     */
    PVRemoteConnectStateFailed,
};


/**
 *  遥控器类型
 */
typedef NS_ENUM(NSInteger,PVRCType) {
    /**
     *  普通遥控器
     */
    PVRCTypeSTD=1,
    /**
     *  体感遥控器
     */
    PVRCTypeTG,
};
/**
 *  遥控器自定义快捷键功能
 */
typedef NS_ENUM(NSInteger,PVCustomButtonFunction) {
    /**
     *  航点标签
     */
//    PVCustomButtonFunctionWayPointTag,
    /**
     *  悬停
     */
//    PVCustomButtonFunctionLoiter,
    /**
     *  短按自拍，长按跟随
     */
    PVCustomButtonFunctionSelfieAndFollow=4,
    /**
     *  收放脚架
     */
    PVCustomButtonFunctionChangeHelm=5,
};

/**
 *  遥控器杆量控制EXP曲线
 */
typedef NS_ENUM(NSInteger,PVRCControlEXPType) {
    /**
     *  油门杆，上升下降
     */
    PVRCControlEXPTypeHtr,
    /**
     *  yaw杆，左转右转
     */
    PVRCControlEXPTypeYaw,
    /**
     *  俯仰杆，前进后退
     */
    PVRCControlEXPTypePitch,
    /**
     *  横滚杆，向左向右
     */
    PVRCControlEXPTypeRoll,
    /**
     *  体感遥控器遥感
     */
    PVRCControlEXPTypeTg,
};

/**
 *  遥控器模式
 */
typedef NS_ENUM(NSInteger,PVRCMode) {
    /**
     *  日本手
     */
    PVRCModeJapan=1,
    /**
     *  美国手
     */
    PVRCModeUSA,
    /**
     *  中国手
     */
    PVRCModeChinese,
    /**
     *  自定义
     */
    PVRCModeCustomer,
};

/**
 *  遥控器固件升级状态
 */
typedef NS_ENUM(NSInteger,PVFirmwareUpgradeState) {
    /**
     *  升级失败
     */
    PVFirmwareUpgradeStateFailed,
    /**
     *  升级成功
     */
    PVFirmwareUpgradeStateSuccess,
    /**
     *  升级中
     */
    PVFirmwareUpgradeStateUpgrading,
};

/**
 *  遥控器校准状态
 */
typedef NS_ENUM(NSInteger,PVRomoteCalibrateState) {
    /**
     *  校准成功
     */
    PVRomoteCalibrateStateCalibrateSuccess,
    /**
     *  校准失败
     */
    PVRomoteCalibrateStateCalibrateFail,
    /**
     *  完成失败
     */
    PVRomoteCalibrateStateCompleteSuccess,
    /**
     *  完成失败
     */
    PVRomoteCalibrateStateCompleteFail,
};

/**
 *  校准数据
 */
typedef struct {
    int directionX;//前后
    int directionY;//左右
    int directionZ;//上下
    int directionR;//偏航
    int target;//1表示在校准状态
}PVRomoteCalibrateData;

/**
 *  遥控器拨轮量
 */
typedef struct {
    int pitch;//俯仰
    int roll;//横滚
    int yaw;//航向
}PVRCMounthData;

@class PVRemoteController;
@protocol PVRemoteControllerDelegate <NSObject>

- (void)remoteController:(PVRemoteController *_Nonnull)rc didUpdateRemotePosition:(CLLocationCoordinate2D)remotePosition;

@end

@interface PVRemoteController : PVBaseComponent

@property (nonatomic,assign)PVRemoteConnectState remoteConnectState;
@property (nonatomic,weak)id<PVRemoteControllerDelegate>delegate;

/**
 *  开始连接遥控器
 *
 *  @return 成功或失败回调
 */
- (void)startConnectRemoteBlockWithSuccess:(PVCompletionBlock) success failure:(PVCompletionBlock)failure;
/**
 *  获取遥控器固件版本
 *
 *  @param block 获取结果
 */
- (void)getRCVersionWithComplection:(void (^_Nonnull)(float version,NSError *_Nullable error))block;

/**
 *  获取体感遥控器固件版本
 *
 *  @param block 获取结果
 */
- (void)getTGRCVersionWithComplection:(void (^_Nonnull)(float version,NSError *_Nullable error))block;

/**
 *  获取遥控器类型
 *
 *  @param block 获取结果
 */
- (void)getRCTypeWithComplection:(void (^_Nonnull)(PVRCType rcType,NSError *_Nullable error))block;

/**
 *  遥控器校准
 *
 *  @param remoteCalibrateState 校准开始或结束
 *  @param block                校准结果回调
 */
- (void)calibrateRemote:(PVRemoteCalibrateState)remoteCalibrateState withCompletion:(void (^_Nonnull)(PVRomoteCalibrateState state, NSError *_Nullable error))block;

/**
 *  遥控器杆量获取
 *
 *  @param block 回调结果
 */
- (void)getRCManaulControlDataWithCompletion:(void (^_Nonnull)(PVRomoteCalibrateData data, NSError *_Nullable error))block;

/**
 *  遥控器杆量获取
 *
 *  @param block 回调结果
 */
- (void)getRCMounthControlDataWithCompletion:(void (^_Nonnull)(PVRCMounthData data, NSError *_Nullable error))block;

/**
 *  设置遥控自定义按键功能
 *
 *  @param buttonFunction 按键功能
 *  @param block          设置结果回调
 */
- (void)setRCCustomButton:(PVCustomButtonFunction)buttonFunction WithCompletion:(PVCompletionBlock)block;

/**
 *  获取遥控器自定义按键功能
 *
 *  @param block 回调结果
 */
- (void)getRCCustomButtonWithCompletion:(void (^_Nonnull)(PVCustomButtonFunction buttonFunction, NSError *_Nullable error))block;

/**
 *  遥控器EXP杆量设置
 *
 *  @param rcControlEXPType EXP类型
 *  @param value            控制量
 *  @param block            设置结果
 */
- (void)setRCControlEXP:(PVRCControlEXPType)rcControlEXPType controlValue:(float)value withCompletion:(PVCompletionBlock)block;

/**
 *  获取遥控器EXP杆量
 *
 *  @param block 获取结果
 */
- (void)getRCControlEXP:(PVRCControlEXPType)rcControlEXPType WithComplection:(void (^_Nonnull)(float controlValue, NSError *_Nullable NSError))block;

/**
 *  设置遥控器模式
 *
 *  @param rcMode 遥控器模式
 *  @param block  设置结果
 */
- (void)setRCMode:(PVRCMode)rcMode withCompletion:(PVCompletionBlock)block;

/**
 *  获取遥控器模式
 *
 *  @param block 获取结果
 */
- (void)getRCModeWithComplection:(void (^_Nonnull)(PVRCMode rcMode,NSError *_Nullable error))block;

/**
 *  获取遥控器电量
 *
 *  @param block 获取结果
 */
- (void)getRCBatteryWithComplection:(void (^_Nonnull)(NSInteger battery,NSError *_Nullable error))block;

/**
 *  获取遥控器有没有和飞行器物理上断开连接（如果遥控器没有断开连接返回NO，已断开返回YES）
 *
 *  @param block 获取结果
 */
- (void)getRCUpdateEnableWithComplection:(void (^_Nonnull)(BOOL updateEnable,NSError *_Nullable error))block;

/**
 *  遥控器固件升级
 *
 *  @param block 升级结果
 */
- (void)startRCFirmwareUpdate:(NSString *_Nullable)filePath WithComplection:(void (^_Nonnull)(PVFirmwareUpgradeState upgradeState,NSInteger upgradeProcess,NSError *_Nullable NSError))block;

@end
