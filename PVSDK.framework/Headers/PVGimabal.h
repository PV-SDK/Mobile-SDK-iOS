//
//  PVGimabal.h
//  PVSDK
//
//  Created by Layne on 16/6/24.
//  Copyright © 2016 Layne. All rights reserved.
//

#import "PVBaseComponent.h"

typedef struct
{
    /**
     *  Gimbal's pitch attitude value.  Swinging in the direction of Y axis
     */
    double pitch;
    /**
     *  Gimbal's roll attitude value.
     */
    double roll;
    /**
     *  Gimbal's yaw attitude value.    　Swinging in the direction of  Ｘaxis
     */
    double yaw;
} PVGimabalAttitude;

/**
 *  Gimbal axis.
 */
typedef NS_ENUM (NSInteger, PVGimbalAxis){
    /**
     *  Gimbal's yaw axis.heading
     */
    PVGimbalAxisYaw,
    /**
     *  Gimbal's pitch axis.pitching
     */
    PVGimbalAxisPitch,
    /**
     *  Gimbal's roll axis.roll
     */
    PVGimbalAxisRoll
};

typedef NS_ENUM (NSInteger, PVGimbalMode){
    PVGimbalModeStart           =0,
    PVGimbalModeFollow          =1,
    PVGimbalModeFPV             =2,
    PVGimabalModeResetCenter    =3,
    PVGimbalModeEnd             =10
};

typedef NS_ENUM(NSInteger,PVGimbalType) {
    PowerGimbal,
    Reserve,
};

typedef NS_ENUM(NSInteger,PVGimbalStatus) {
    PVGimbalStatusOK            =1,
    PVGimbalStatusUnconnect,
    PVGimbalStatusError,
};


//////////////////////////////////////////////////
/// @brief parameters of gimbal control
///
/// defined the parameters of gimbal control
//////////////////////////////////////////////////
typedef struct{
    int mount_mode;     ///< PVSDK_GIMBAL_MOUNT_MODE
    int stab_roll;      ///< (1 = yes, 0 = no)
    int stab_pitch;     ///< (1 = yes, 0 = no)
    int stab_yaw;       ///< (1 = yes, 0 = no)
} PVGimbalControlInfo;


@interface PVGimabal : PVBaseComponent

/**
 Get the gimbal firmware version
 
 @param block callback results
 */
- (void)getGimbalVersionWithComplection:(void (^_Nonnull)(int version,NSError *_Nullable error))block;

/**
 Get the gimbal model
 
 @param block callback results
 */
- (void)getGimbalTypeWithComplection:(void (^_Nonnull)(PVGimbalType gimbalType,NSError *_Nullable error))block;

/**
 Get the status of gimbal
 
 @param block callback results
 */
- (void)getGimbalStatusWithComplection:(void (^_Nonnull)(PVGimbalStatus gimbalStatus,NSError *_Nullable error))block;

/**
 You need to set the PVGimbalControlInfo in the mount_mode to 0 before updating the gimbal pose,
 
 @param gimabalAttitude  gimbal pose mode setting
 */
- (void)setGimbalAttitudeControlInfo:(PVGimbalControlInfo)controlInfo;

/**
 Update the information of the gimbal pose
 
 @param gimabalAttitude information of the gimbal pose
 */
- (void)updateGimabalAttitude:(PVGimabalAttitude)gimabalAttitude;

/**
 Set up the pitch direction and speed

 @param speed speed(0-100)
 @param block callback about the setting results
 */
- (void)setGimbalPitchSpeed:(int)speed withCompletion:(PVCompletionBlock)block;

/**
 Get the pitching speed of the gimbal(0-100)

 @param block results
 */
- (void)getGimbalPitchSpeedWithCompletion:(void (^_Nonnull)(int speed, NSError *_Nullable error))block;

/**
 The maximum 30 degree settings of the extended pitch axis

 @param block callback results
 */
- (void)extendPitchAxisLimit30:(BOOL)enxtend withCompletion:(PVCompletionBlock)block;

/**
 Get the maximum 30 degree settings of the extended pitch axis

 @param block callback results
 */
- (void)getExtendPitchAxisLimit30WithCompletion:(void (^_Nonnull)(BOOL isExtend, NSError *_Nullable error))block;

/**
 Smooth control setting settings in a certain direction

 @param smoothing smooth parameters(0-30)
 @param axis      direction
 @param block     results callback
 */
- (void)setControllerSmoothing:(NSInteger)smoothing onAxis:(PVGimbalAxis)axis withCompletion:(PVCompletionBlock)block;

/**
 Get the smooth parameters in a certain direction of gimbal


 @param axis  direction
 @param block callback results
 */
- (void)getControllerSmoothing:(PVGimbalAxis)axis withCompletion:(void (^_Nonnull)(NSInteger smoothing, NSError *_Nullable error))block;

/**
 Gimbal heading axis speed settings

 @param speed speed(-1.3~1.3)
 @param block  callback about setting results
 */
- (void)setGimbalYawSpeed:(float)speed withCompletion:(PVCompletionBlock)block;

/**
 Get the the speed of the gimbal heading axis

 @param block results callback
 */
- (void)getGimbalYawSpeedWithCompletion:(void (^_Nonnull)(float speed, NSError *_Nullable error))block;

/**
 Reset the parameters of gimbal and then  return origin

 @param block result callback
 */
- (void)resetGimbalWithCompletion:(PVCompletionBlock)block;

/**
 Gimbal mode settings

 @param mode  mode
 @param block callback about the setting results
 */
- (void)setGimbalMode:(PVGimbalMode)mode withCompletion:(PVCompletionBlock)block;

/**
 Get the gimbal mode

 @param block Result callback
 */
- (void)getGimbalModeWithCompletion:(void (^_Nonnull)(PVGimbalMode gimbalMode, NSError *_Nullable error))block;

/**
 Fine tuning of gimbal flip angle( Roll axis)

 @param angle fine tuning angle(-5~5)
 @param block  callback about fine tuning results
 */
- (void)rollAxisAngleFineTuning:(float)angle withCompletion:(PVCompletionBlock)block;

/**
 Get the fine tuning of gimbal flip angle( Roll axis)

 @param angle fine tuning angle(-5~5)
 @param block callback about fine tuning results
 */
- (void)getRollAxisAngleFineTuning:(void (^_Nonnull)(float angle, NSError *_Nullable error))block;
/**
 Calibrate gimbal automatically

 @param block Result callback
 */
- (void)autoCalibrateGimbalWithCompletion:(PVCompletionBlock)block;

@end
