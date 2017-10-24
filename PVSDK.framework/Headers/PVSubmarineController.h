//
//  PVSubmarineController.h
//  PVSDK
//
//  Created by Layne on 2017/3/13.
//  Copyright © 2017年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PVBaseComponent.h"
#import "PVSubmarineControllerState.h"

typedef void (^_Nullable PVRaySelfCheckingBlock)(PVSubmarineSelfCheckingState state, NSError * _Nullable error);

typedef struct{
    //回中0，0，0，0
    int x; ///右上 +1000，右下 -1000
    int y; ///左左 -1000，左右 +1000
    int z; ///左上 +1000，左下-1000
    int r; ///右左 -1000，右右+1000
    unsigned short buttons;
} PVSubmarineControlInfo;

typedef NS_ENUM(NSInteger,PVSubmarineSpeedLevel) {
    PVSubmarineSpeedLevelFree=0,
    PVSubmarineSpeedLevelLow,
    PVSubmarineSpeedLevelMedium,
    PVSubmarineSpeedLevelHigh,
};

typedef NS_ENUM(NSInteger,PVSubmarineStateUpdate) {
    /**
     *  主副控状态更新
     */
    PVStateUpdateMaster,
    /**
     *  航灯亮度更新
     */
    PVStateUpdateLight,
    /**
     *  深度更新
     */
    PVStateUpdateDepth,
    /**
     *  电量更新
     */
    PVStateUpdateBattery,
    /**
     *  报警信息更新
     */
    PVStateUpdateAlarm,
    /**
     *  模式更新（定深、定速）
     */
    PVStateUpdateMode,
    /**
     *  鱼钩状态更新
     */
    PVStateUpdateFishHook,
    /**
     *  姿态更新
     */
    PVStateUpdateAttituState
    
};

/**
 *  飞控固件升级状态
 */
typedef NS_ENUM(NSInteger,PVSubmarineFirmwareUpgradeState) {
    /**
     *  升级失败
     */
    PVSubmarineFirmwareUpgradeStateFailed,
    /**
     *  升级成功
     */
    PVSubmarineFirmwareUpgradeStateSuccess,
    /**
     *  升级中
     */
    PVSubmarineFirmwareUpgradeStateUpgrading,
};



/// @brief 水下电机相关参数
///
/// 定义关于水下电机的相关参数
//////////////////////////////////////////////////
typedef struct PVSubmarineESC_PARAM {
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
} PVSubmarineESC_PARAM;

@class PVSubmarineController;
@protocol PVSubmarineControllerDelegate <NSObject>

/**
 *  机体信息改变时回调
 *
 *  @param sc  submarineController
 *  @param state 机体信息
 *  @param stateUpdate 状态类型
 */
- (void)submarineController:(PVSubmarineController *_Nonnull)sc didUpdateSubmarineControllerState:(PVSubmarineControllerState *_Nonnull)state stateType:(PVSubmarineStateUpdate)stateUpdate;

@end


@interface PVSubmarineController : PVBaseComponent

@property (nonatomic,weak)id <PVSubmarineControllerDelegate> delegate;

/**
 *  获取飞控固件版本
 *
 *  @param block 获取结果
 */
- (void)getFCVersionWithComplection:(void (^_Nonnull)(int version,NSError *_Nullable error))block;


/**
 *  机体姿态设置
 *
 *  @param block 设置结果
 */
- (void)updateSubmarineAttitude:(PVSubmarineControlInfo)info;

/**
 *  定深模式设置
 *
 *  @param block 设置结果
 */
- (void)setDepthMode:(PVRayDepthState)depthState WithCompletion:(PVCompletionBlock)block;

/**
 *  开始Ray自检
 *
 *  @param block
 */
- (void)startSelfCheckWithCompletion:(PVRaySelfCheckingBlock)block;

/**
 *  速度设置
 *
 *  @param block 设置结果
 */
- (void)setSpeed:(PVSubmarineSpeedLevel)speedLevel withComplection:(PVCompletionBlock)block;

/**
 *  设置航灯亮度(0-100)
 *
 *  @param block 设置结果
 */
- (void)setLightsValue:(int)value withComplection:(PVCompletionBlock)block;

/**
 *  收放鱼钩
 *
 *  @value 0或1
 *  @param block 设置结果
 */
- (void)putAndPullFishHook:(int)value withComplection:(PVCompletionBlock)block;

/**
 *  设置主从设备
 *
 *  @param block 设置结果
 */
- (void)setMasterControl:(BOOL)isMaster withComplection:(PVCompletionBlock)block;


/**
 开始获取基站电量

 @param ip  地址
 @param port 端口
 */
- (void)startGetBaseStationBatteryWithIP:(NSString *_Nullable)ip port:(int)port;

/**
 停止基站电量获取

 @param block
 */
- (void)stopGetBaseStationBatteryWithComplection:(PVCompletionBlock)block;


/**
 设置加解锁状态 YES 解锁，NO加锁

 @param arm 加解锁
 @param block 设置结果
 */
- (void)setRayArm:(BOOL)arm withComplection:(void (^_Nonnull)(BOOL arm,NSError *_Nullable error))block;

/**
 设置船体强制加解锁（回调复用setRayArm：回调）

 @param arm YES 解锁(当前只有解锁)
 */
- (void)setRayForceCommandArm:(BOOL)arm;


/**
 *  升级飞控固件
 */
- (void)startFlightFirmwareUpdate:(NSString *_Nullable)filePath WithComplection:(void (^_Nonnull)(PVSubmarineFirmwareUpgradeState upgradeState,NSInteger upgradeProcess,NSError *_Nullable NSError))block;


/**
 复位Ray参数

 @param block
 */
- (void)resetRayParamsWithComplection:(PVCompletionBlock)block;


/**
 改变遥控器上寻鱼器按钮灯光显示

 @param block 
 */
- (void)changeRemoteFishLightView:(BOOL)ON WithComplection:(PVCompletionBlock)block;

/**
 *  获取产品激活码
 *
 *  @param block 获取结果
 */
- (void)getProductValidateKeyWithComplection:(void (^_Nonnull)(NSString *_Nullable validateKey,NSError *_Nullable error))block;

/**
 *  激活产品
 *
 *  @param block 激活结果
 */
- (void)validateProductWithComplection:(PVCompletionBlock)block;

/**
 *  获取飞机激活状态
 *
 *  @param block 获取结果
 */
- (void)getProductValidateStateWithComplection:(void (^_Nonnull)(PVProductValidateState validateState,NSError *_Nullable error))block;



/**
 设置寻鱼器SSID配对码

 @param SSid SSID
 @param ip IP
 @param port Port
 */
- (void)setFishFinderSSid:(NSString * _Nullable)SSid pairIP:(NSString * _Nullable)ip pairPort:(int)port withComplection:(void (^_Nonnull)(PowerRay_PAIR_FISH_FINDER_STATE finderState,NSError *_Nullable error))block;



@end
