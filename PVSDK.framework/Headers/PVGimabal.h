//
//  PVGimabal.h
//  PVSDK
//
//  Created by Layne on 16/6/24.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import "PVBaseComponent.h"

typedef struct
{
    /**
     *  Gimbal's pitch attitude value.  Y轴方向摆动
     */
    double pitch;
    /**
     *  Gimbal's roll attitude value.
     */
    double roll;
    /**
     *  Gimbal's yaw attitude value.    X轴方向摆动
     */
    double yaw;
} PVGimabalAttitude;

/**
 *  Gimbal axis.
 */
typedef NS_ENUM (NSInteger, PVGimbalAxis){
    /**
     *  Gimbal's yaw axis.航向
     */
    PVGimbalAxisYaw,
    /**
     *  Gimbal's pitch axis.俯仰
     */
    PVGimbalAxisPitch,
    /**
     *  Gimbal's roll axis.横滚
     */
    PVGimbalAxisRoll
};

typedef NS_ENUM (NSInteger, PVGimbalMode){
    PVGimbalModeStart=0,
    PVGimbalModeFollow=1,
    PVGimbalModeFPV=2,
    PVGimabalModeResetCenter=3,
    PVGimbalModeEnd=10
};

typedef NS_ENUM(NSInteger,PVGimbalType) {
    PowerGimbal,
    Reserve,
};

typedef NS_ENUM(NSInteger,PVGimbalStatus) {
    PVGimbalStatusOK=1,
    PVGimbalStatusUnconnect,
    PVGimbalStatusError,
};


//////////////////////////////////////////////////
/// @brief 云台控制参数
///
/// 定义了云台控制的相关参数
//////////////////////////////////////////////////
typedef struct{
    int mount_mode; ///< PVSDK_GIMBAL_MOUNT_MODE
    int stab_roll; ///< (1 = yes, 0 = no)
    int stab_pitch; ///< (1 = yes, 0 = no)
    int stab_yaw; ///< (1 = yes, 0 = no)
} PVGimbalControlInfo;


@interface PVGimabal : PVBaseComponent

/**
 *  获取云台固件版本
 *
 *  @param block 回调结果
 */
- (void)getGimbalVersionWithComplection:(void (^_Nonnull)(int version,NSError *_Nullable error))block;

/**
 *  获取云台型号
 *
 *  @param block 回调结果
 */
- (void)getGimbalTypeWithComplection:(void (^_Nonnull)(PVGimbalType gimbalType,NSError *_Nullable error))block;

/**
 获取云台状态

 @param block 回调结果
 */
- (void)getGimbalStatusWithComplection:(void (^_Nonnull)(PVGimbalStatus gimbalStatus,NSError *_Nullable error))block;

/**
 *  更新云台姿态前需要先设置PVGimbalControlInfo中mount_mode为0
 *
 *  @param gimabalAttitude 云台姿态模式设置
 */
- (void)setGimbalAttitudeControlInfo:(PVGimbalControlInfo)controlInfo;

/**
 *  更新云台姿态信息
 *
 *  @param gimabalAttitude 云台姿态信息
 */
- (void)updateGimabalAttitude:(PVGimabalAttitude)gimabalAttitude;

/**
 *  设置俯仰方向速度
 *
 *  @param speed 速度(0-100)
 *  @param block 设置结果回调
 */
- (void)setGimbalPitchSpeed:(int)speed withCompletion:(PVCompletionBlock)block;

/**
 *  获取云台俯仰速度(0-100)
 *
 *  @param block 获取结果
 */
- (void)getGimbalPitchSpeedWithCompletion:(void (^_Nonnull)(int speed, NSError *_Nullable error))block;

/**
 *  扩展俯仰轴限位参数至上30度设置
 *
 *  @param block 回调结果
 */
- (void)extendPitchAxisLimit30:(BOOL)enxtend withCompletion:(PVCompletionBlock)block;

/**
 *  获取扩展俯仰轴限位参数至上30度设置
 *
 *  @param block 回调结果
 */
- (void)getExtendPitchAxisLimit30WithCompletion:(void (^_Nonnull)(BOOL isExtend, NSError *_Nullable error))block;

/**
 *  某个方向上的平滑控制设置
 *
 *  @param smoothing 平滑参数(0-30)
 *  @param axis      方向
 *  @param block     结果回调
 */
- (void)setControllerSmoothing:(NSInteger)smoothing onAxis:(PVGimbalAxis)axis withCompletion:(PVCompletionBlock)block;

/**
 *  获取云台某个方向上的平滑参数
 *
 *  @param axis  方向
 *  @param block 回调结果
 */
- (void)getControllerSmoothing:(PVGimbalAxis)axis withCompletion:(void (^_Nonnull)(NSInteger smoothing, NSError *_Nullable error))block;

/**
 *  云台航向轴速度设置
 *
 *  @param speed 速度(-1.3~1.3)
 *  @param block  设置结果回调
 */
- (void)setGimbalYawSpeed:(float)speed withCompletion:(PVCompletionBlock)block;

/**
 *  获取云台航向轴速度
 *
 *  @param block 回调结果
 */
- (void)getGimbalYawSpeedWithCompletion:(void (^_Nonnull)(float speed, NSError *_Nullable error))block;

/**
 *  重置云台各参数，回到原点
 *
 *  @param block 结果回调
 */
- (void)resetGimbalWithCompletion:(PVCompletionBlock)block;

/**
 *  云台模式设置
 *
 *  @param mode  模式
 *  @param block 设置结果回调
 */
- (void)setGimbalMode:(PVGimbalMode)mode withCompletion:(PVCompletionBlock)block;

/**
 *  获取云台模式
 *
 *  @param block 结果回调
 */
- (void)getGimbalModeWithCompletion:(void (^_Nonnull)(PVGimbalMode gimbalMode, NSError *_Nullable error))block;

/**
 *  云台翻转角度(Roll轴)微调
 *
 *  @param angle 微调角度(-5~5)
 *  @param block 微调结果回调
 */
- (void)rollAxisAngleFineTuning:(float)angle withCompletion:(PVCompletionBlock)block;

/**
 *  获取云台翻转角度(Roll轴)微调
 *
 *  @param angle 微调角度(-5~5)
 *  @param block 微调结果回调
 */
- (void)getRollAxisAngleFineTuning:(void (^_Nonnull)(float angle, NSError *_Nullable error))block;
/**
 *  自动校准云台
 *
 *  @param block 结果回调
 */
- (void)autoCalibrateGimbalWithCompletion:(PVCompletionBlock)block;

@end
