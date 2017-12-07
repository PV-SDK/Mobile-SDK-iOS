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
     *  connecting
     */
    PVRemoteConnectStateConnecting,
    /**
     * already connected
     */
    PVRemoteConnectStateConnected,
    /**
     *  Gesture-based remote controller is connected
     */
    PVRemoteConnectStateTGConnected,
    /**
     *   connection break off
     */
    PVRemoteConnectStateDisConnected,
    /**
     *  connection time-out
     */
    PVRemoteConnectStateTimeout,
    /**
     *  heartbeat timeout
     */
    PVRemoteConnectStateHeartTimeout,
    /**
     *  Failed to connect
     */
    PVRemoteConnectStateFailed,
};


/**
 *   remote controller type
 */
typedef NS_ENUM(NSInteger,PVRCType) {
    /**
     *  remote controller
     */
    PVRCTypeSTD=1,
    /**
     *  Gesture-based remote controller
     */
    PVRCTypeTG,
};
/**
 *   remote controller's function about customing the keyboard shortcuts
 */
typedef NS_ENUM(NSInteger,PVCustomButtonFunction) {
    /**
     *  waypoint label
     */
    //    PVCustomButtonFunctionWayPointTag,
    /**
     *  hovering
     */
    //    PVCustomButtonFunctionLoiter,
    /**
     *  Short press to selfie, long press to follow
     */
    PVCustomButtonFunctionSelfieAndFollow=4,
    /**
     *  Retract & deploy landing gea
     */
    PVCustomButtonFunctionChangeHelm=5,
};

/**
 *  Remote control rod Control the EXP curve
 */
typedef NS_ENUM(NSInteger,PVRCControlEXPType) {
    /**
     *  Throttle Lever to control rise and fall
     */
    PVRCControlEXPTypeHtr,
    /**
     * Yaw rod ,turn left and right
     */
    PVRCControlEXPTypeYaw,
    /**
     *  Pitching rod，fore and back
     */
    PVRCControlEXPTypePitch,
    /**
     *  Roll rod ，turn left and right
     */
    PVRCControlEXPTypeRoll,
    /**
     *  remote sense of  Gesture-based remote controller
     */
    PVRCControlEXPTypeTg,
};

/**
 *  Remote control mode
 */
typedef NS_ENUM(NSInteger,PVRCMode) {
    /**
     *  Mode 1
     */
    PVRCModeJapan=1,
    /**
     *  Mode 2
     */
    PVRCModeUSA,
    /**
     *  Mode 3
     */
    PVRCModeChinese,
    /**
     * Mode 4
     */
    PVRCModeCustomer,
};

/**
 *  the status of remote controller firmware upgrade
 */
typedef NS_ENUM(NSInteger,PVFirmwareUpgradeState) {
    /**
     *  Failed to upgrade
     */
    PVFirmwareUpgradeStateFailed,
    /**
     *  upgrade successfully
     */
    PVFirmwareUpgradeStateSuccess,
    /**
     *   upgrading
     */
    PVFirmwareUpgradeStateUpgrading,
};

/**
 *  the status of remote controller calibration
 */
typedef NS_ENUM(NSInteger,PVRomoteCalibrateState) {
    /**
     *  Calibrate  successfully
     */
    PVRomoteCalibrateStateCalibrateSuccess,
    /**
     *  Failed to Calibrate
     */
    PVRomoteCalibrateStateCalibrateFail,
    /**
     *  failed to finish
     */
    PVRomoteCalibrateStateCompleteSuccess,
    /**
     *  failed to finish
     */
    PVRomoteCalibrateStateCompleteFail,
};

/**
 *  Calibrate the data
 */
typedef struct {
    int directionX;//before and after
    int directionY;//left and right
    int directionZ;//up and down
    int directionR;//yaw
    int target;//1 in calibration state
}PVRomoteCalibrateData;

/**
 *  遥控器拨轮量 o                                                                   f remote-c
 */
typedef struct {
    int pitch;//pitching
    int roll;//roll
    int yaw;//heading
}PVRCMounthData;

@class PVRemoteController;
@protocol PVRemoteControllerDelegate <NSObject>

- (void)remoteController:(PVRemoteController *_Nonnull)rc didUpdateRemotePosition:(CLLocationCoordinate2D)remotePosition;

@end

@interface PVRemoteController : PVBaseComponent

@property (nonatomic,assign)PVRemoteConnectState remoteConnectState;
@property (nonatomic,weak)id<PVRemoteControllerDelegate>delegate;

/**
 *  start to connect the remote control
 *
 *  @return callback successfully or failure
 */
- (void)startConnectRemoteBlockWithSuccess:(PVCompletionBlock) success failure:(PVCompletionBlock)failure;
/**
 *  Get the version of the remote control firmware
 *
 *  @param block results
 */
- (void)getRCVersionWithComplection:(void (^_Nonnull)(float version,NSError *_Nullable error))block;

/**
 *  Get the version of the Gesture-based remote control firmware
 *
 *  @param block results
 */
- (void)getTGRCVersionWithComplection:(void (^_Nonnull)(float version,NSError *_Nullable error))block;

/**
 *  Get the type of the remote control
 *
 *  @param block results
 */
- (void)getRCTypeWithComplection:(void (^_Nonnull)(PVRCType rcType,NSError *_Nullable error))block;

/**
 *  remote control calibration
 *
 *  @param remoteCalibrateState start or end the calibration
 *  @param block             callback about calibration result
 */
- (void)calibrateRemote:(PVRemoteCalibrateState)remoteCalibrateState withCompletion:(void (^_Nonnull)(PVRomoteCalibrateState state, NSError *_Nullable error))block;

/**
 *    obtain the Remote control rod quantity
 *
 *  @param block callback results
 */
- (void)getRCManaulControlDataWithCompletion:(void (^_Nonnull)(PVRomoteCalibrateData data, NSError *_Nullable error))block;

/**
 *  obtain the remote control rod quantity
 *
 *  @param block callback results
 */
- (void)getRCMounthControlDataWithCompletion:(void (^_Nonnull)(PVRCMounthData data, NSError *_Nullable error))block;

/**
 *  set the custom key function of remote control
 *
 *  @param buttonFunction key function
 *  @param block          callback of the setting results
 */
- (void)setRCCustomButton:(PVCustomButtonFunction)buttonFunction WithCompletion:(PVCompletionBlock)block;

/**
 *  Get the custom key function of the remote control
 *
 *  @param block callback results
 */
- (void)getRCCustomButtonWithCompletion:(void (^_Nonnull)(PVCustomButtonFunction buttonFunction, NSError *_Nullable error))block;

/**
 *  setting about remote control EXP lever quantity
 *
 *  @param rcControlEXPType EXP type
 *  @param value            controlled quantity
 *  @param block            setting results
 */
- (void)setRCControlEXP:(PVRCControlEXPType)rcControlEXPType controlValue:(float)value withCompletion:(PVCompletionBlock)block;

/**
 *  Get the remote control EXP lever quantity
 *
 *  @param block results
 */
- (void)getRCControlEXP:(PVRCControlEXPType)rcControlEXPType WithComplection:(void (^_Nonnull)(float controlValue, NSError *_Nullable NSError))block;

/**
 *  set remote control mode
 *
 *  @param rcMode remote control mode
 *  @param block   setting results
 */
- (void)setRCMode:(PVRCMode)rcMode withCompletion:(PVCompletionBlock)block;

/**
 *  obtain remote control mode
 *
 *  @param block results
 */
- (void)getRCModeWithComplection:(void (^_Nonnull)(PVRCMode rcMode,NSError *_Nullable error))block;

/**
 *  get the battery of remote control
 *
 *  @param block results
 */
- (void)getRCBatteryWithComplection:(void (^_Nonnull)(NSInteger battery,NSError *_Nullable error))block;

/**
 *  获取遥控器有没有和飞行器物理上断开连接（如果遥控器没有断开连接返回NO，已断开返回YES）
 *
 *  @param block results
 */
- (void)getRCUpdateEnableWithComplection:(void (^_Nonnull)(BOOL updateEnable,NSError *_Nullable error))block;

/**
 *  remote controller firmware upgrade
 *
 *  @param block Update result
 */
- (void)startRCFirmwareUpdate:(NSString *_Nullable)filePath WithComplection:(void (^_Nonnull)(PVFirmwareUpgradeState upgradeState,NSInteger upgradeProcess,NSError *_Nullable NSError))block;

@end
