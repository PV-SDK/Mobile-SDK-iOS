//
//  PVCameraCallback.h
//  PowerVision
//
//  Created by Power on 2017/9/7.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#ifndef PVCameraCallback_h
#define PVCameraCallback_h


#endif /* PVCameraCallback_h */
/**
 Return types in Camera operation
 */
typedef NS_ENUM(NSInteger,PVCameraCallbackType) {
    //success
    PVCameraCallbackTypeSuccess,
    //fail
    PVCameraCallbackTypeFailure,
    //over time
    PVCameraCallbackTypeTimeout,
    //SD card error
    PVCameraCallbackTypeSDError,
    //The SD card is full
    PVCameraCallbackTypeSDFull,
    //The SD card is full empty
    PVCameraCallbackTypeSDEmpty,
};

/**
 Camera operation types
 */
typedef NS_ENUM(NSInteger,PVCameraHandleType) {
    //take pictures
    PVCameraHandleTypeShootPhoto,
    //start filming
    PVCameraHandleTypeStartRec,
    //stop  filming
    PVCameraHandleTypeStopRec,
    //Switch to photo mode
    PVCameraHandleTypeSwitchShootPhoto,
    //Switch to video mode
    PVCameraHandleTypeSwitchRec
};
