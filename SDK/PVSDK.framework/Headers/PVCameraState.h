//
//  PVCameraState.h
//  PVSDK
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#ifndef PVCameraState_h
#define PVCameraState_h

/**
 *the type of camera operation callback
 */
typedef NS_ENUM(NSInteger,PVCameraCallbackType) {
    PVCameraCallbackTypeSuccess,    ///< success
    PVCameraCallbackTypeFailure,    ///< failure
    PVCameraCallbackTypeTimeout,    ///< timeout
    PVCameraCallbackTypeSDError,    ///< SD card error
    PVCameraCallbackTypeSDFull,     ///< SD card is full
    PVCameraCallbackTypeSDEmpty,    ///< SD card is full
};

/**
 *Camera operation type
 */
typedef NS_ENUM(NSInteger,PVCameraHandleType) {
    PVCameraHandleTypeShootPhoto,       ///< shoot
    PVCameraHandleTypeStartRec,         ///< start recording
    PVCameraHandleTypeStopRec,          ///< finish recording
    PVCameraHandleTypeSwitchShootPhoto, ///< switch to shooting mode
    PVCameraHandleTypeSwitchRec         ///< switch to recording mode
};

#endif /* PVCameraState_h */

