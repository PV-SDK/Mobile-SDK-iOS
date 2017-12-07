//
//  PVCameraSettingsDef.h
//  PVSDK
//
//  Created by Layne on 16/6/28.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PVCameraSettingsDef : NSObject

/**
 * set the video recording size
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoSize) {
    /**
     *  4KP30
     */
    PVCameraVideoSize4KP30=51,
    /**
     *  4096P24
     */
    PVCameraVideoSize4096P24=52,
    /**
     *  2160P30
     */
    PVCameraVideoSize2160P30=53,
    /**
     *  2160P24
     */
    PVCameraVideoSize2160P24=54,
    /**
     *  1920P30
     */
    PVCameraVideoSize1920P30=55,
    /**
     *  1920P24
     */
    PVCameraVideoSize1920P24=56,
    /**
     *  1440P30
     */
    PVCameraVideoSize1440P30=57,
    /**
     *  1440P24
     */
    PVCameraVideoSize1440P24=58,
    /**
     *  1080P60
     */
    PVCameraVideoSize1080P60=59,
    /**
     *  1080P30
     */
    PVCameraVideoSize1080P30=60,
    /**
     *  WVGAP30
     */
    PVCameraVideoSizeWVGAP30=61,
};

/**
 *  AF settings in recording
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoAF) {
    /**
     *  normal
     */
    PVCameraVideoAFNormal=51,
    /**
     *  freemove
     */
    PVCameraVideoAFFree,
};

/**
 *  Continual focus
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoKPZoom) {
    /**
     *  close
     */
    PVCameraVideoKPZoomClose=51,
    /**
     *  open
     */
    PVCameraVideoKPZoomOpen,
};

/**
 *  CAF range settings
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoCAF) {
    /**near
     *  far
     */
    PVCameraVideoCAFFar=51,
    /**
     *
     */
    PVCameraVideoCAFNear,
    /**
     *  normal
     */
    PVCameraVideoCAFNormal,
};

/**
 *  CAF sensitivity settings
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoCAFLevel) {
    /**
     *  high
     */
    PVCameraVideoCAFLevelHigh=51,
    /**
     *  normal
     */
    PVCameraVideoCAFLevelMid,
    /**
     *  basic
     */
    PVCameraVideoCAFLevelLow,
};

/**
 *  burst speed of camera
 */
typedef NS_ENUM(NSUInteger, PVEyeCameraContinuousShootSpeed) {
    /**
     *  low speed
     */
    PVEyeCameraContinuousShootSpeedLow=51,
    /**
     *  low or medium speed
     */
    PVEyeCameraContinuousShootSpeedMidLow,
    /**
     *  medium speed
     */
    PVEyeCameraContinuousShootSpeedMid,
    /**
     *  high speed
     */
    PVEyeCameraContinuousShootSpeedHigh,
};


/**
 *  Camera shutter speed
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoShutterSpeed) {
    /**
     *  Auto
     */
    PVCameraVideoShutterSpeedAuto=51,
    /**
     *  1/240s
     */
    PVCameraVideoShutterSpeed240=52,
    /**
     *  1/120s
     */
    PVCameraVideoShutterSpeed120=53,
    /**
     *  1/100s
     */
    PVCameraVideoShutterSpeed100=54,
    /**
     *  1/75s
     */
    PVCameraVideoShutterSpeed75=55,
    /**
     *  1/62.5s
     */
    PVCameraVideoShutterSpeed625=56,
    /**
     *  1/60s
     */
    PVCameraVideoShutterSpeed60=57,
    /**
     *  1/50s
     */
    PVCameraVideoShutterSpeed50=58,
    /**
     *  1/40s
     */
    PVCameraVideoShutterSpeed40=59,
    /**
     *  1/33.3s
     */
    PVCameraVideoShutterSpeed333=60,
    /**
     *  1/30s
     */
    PVCameraVideoShutterSpeed30=61,
};

/**
 *  photo size settings
 */
typedef NS_ENUM(NSUInteger,PVCameraPhotoSize) {
    /**
     *  16M
     */
    PVCameraPhotoSize16M=51,
    /**
     *  12M
     */
    PVCameraPhotoSize12M,
    /**
     *  8M
     */
    PVCameraPhotoSize8M,
    /**
     *  5M
     */
    PVCameraPhotoSize5M,
    /**
     *  3M
     */
    PVCameraPhotoSize3M,
};

/**
 *  Photo quality
 */
typedef NS_ENUM(NSUInteger,PVEyeCameraPhotoQuality) {
    /**
     * basic
     */
    PVEyeCameraPhotoQualityNormal=51,
    /**
     *  Sharpness fine
     */
    PVEyeCameraPhotoQualityFine,
    /**
     *  Sharpness super fine
     */
    PVEyeCameraPhotoQualitySuperFine,
    /**
     *  JPEG+DNG
     */
    PVEyeCameraPhotoQualityJPEGDNG,
};

/**
 *  photo mode
 */
typedef NS_ENUM(NSUInteger,PVEyeCameraMode) {
    /**
     *  Single shot
     */
    PVEyeCameraModeSingle=51,
    /**
     *  Continuous shooting
     */
    PVEyeCameraModeContinuous,
    /**
     *  time-lapse shooting
     */
    PVEyeCameraModeDely,
};

/**
 *  Camera shutter speed settings
 */
typedef NS_ENUM(NSUInteger,PVCameraPhotoShutterSpeed) {
    /**
     *  Auto
     */
    PVCameraPhotoShutterSpeedAuto=51,
    /**
     *  1/2s
     */
    PVCameraPhotoShutterSpeed2s=52,
    /**
     *  1/3s
     */
    PVCameraPhotoShutterSpeed3s=53,
    /**
     *  1/4s
     */
    PVCameraPhotoShutterSpeed4s=54,
    /**
     *  1/5s
     */
    PVCameraPhotoShutterSpeed5s=55,
    /**
     *  1/8s
     */
    PVCameraPhotoShutterSpeed8s=56,
    /**
     *  1/10s
     */
    PVCameraPhotoShutterSpeed10s=57,
    /**
     *  1/15s
     */
    PVCameraPhotoShutterSpeed15s=58,
    /**
     *  1/20s
     */
    PVCameraPhotoShutterSpeed20s=59,
    /**
     *  1/25s
     */
    PVCameraPhotoShutterSpeed25s=60,
    /**
     *  1/30s
     */
    PVCameraPhotoShutterSpeed30s=61,
    /**
     *  1/40s
     */
    PVCameraPhotoShutterSpeed40s=62,
    /**
     *  1/50s
     */
    PVCameraPhotoShutterSpeed50s=63,
    /**
     *  1/60s
     */
    PVCameraPhotoShutterSpeed60s=64,
    /**
     *  1/80s
     */
    PVCameraPhotoShutterSpeed80s=65,
    /**
     *  1/100s
     */
    PVCameraPhotoShutterSpeed100s=66,
    /**
     *  1/125s
     */
    PVCameraPhotoShutterSpeed125s=67,
    /**
     *  1/160s
     */
    PVCameraPhotoShutterSpeed160s=68,
    /**
     *  1/200s
     */
    PVCameraPhotoShutterSpeed200s=69,
    /**
     *  1/250s
     */
    PVCameraPhotoShutterSpeed250s=70,
    /**
     *  1/320s
     */
    PVCameraPhotoShutterSpeed320s=71,
};

/**
 *  Aperture size
 */
typedef NS_ENUM(NSUInteger,PVCameraAperture) {
    /**
     *  2.5
     */
    PVCameraAperture25=51,
    /**
     *  2.8
     */
    PVCameraAperture28=52,
    /**
     *  3.2
     */
    PVCameraAperture32=53,
    /**
     *  3.5
     */
    PVCameraAperture35=54,
    /**
     *  4.0
     */
    PVCameraAperture40=55,
    /**
     *  4.5
     */
    PVCameraAperture45=56,
    /**
     *  5.0
     */
    PVCameraAperture50=57,
    /**
     *  5.6
     */
    PVCameraAperture56=58,
    /**
     *  6.3
     */
    PVCameraAperture63=59,
    /**
     *  7.1
     */
    PVCameraAperture71=60,
    /**
     *  8.0
     */
    PVCameraAperture80=61,
    /**
     *  9.0
     */
    PVCameraAperture90=62,
    /**
     *  10.0
     */
    PVCameraAperture100=63,
    /**
     *  11.0
     */
    PVCameraAperture110=64,
    /**
     *  13.0
     */
    PVCameraAperture130=65,
    /**
     *  14.0
     */
    PVCameraAperture140=66,
    /**
     *  16.0
     */
    PVCameraAperture160=67,
    /**
     *  18.0
     */
    PVCameraAperture180=68,
    /**
     *  20.0
     */
    PVCameraAperture200=69,
    /**
     *  22.0
     */
    PVCameraAperture220=70,
    
    
};

/**
 *  camera white balance
 */
typedef NS_ENUM(NSInteger,PVEyeCameraWhiteBalanceMode) {
    /**
     *  auto
     */
    PVEyeCameraWhiteBalanceModeAuto=51,
    /**
     * Manual
     */
    PVEyeCameraWhiteBalanceModeManual,
};

typedef NS_ENUM (NSUInteger, PVEyeCameraISO){
    /**
     *  The ISO value is automatically set. This cannot be used for all cameras when in Manual mode.
     */
    PVEyeCameraISOAuto=51,
    /**
     *  The ISO value is set to 100.
     */
    PVEyeCameraISO100,
    /**
     *  The ISO value is set to 125.
     */
    PVEyeCameraISO125,
    /**
     *  The ISO value is set to 160.
     */
    PVEyeCameraISO160,
    /**
     *  The ISO value is set to 200.
     */
    PVEyeCameraISO200,
    /**
     *  The ISO value is set to 160.
     */
    PVEyeCameraISO250,
    /**
     *  The ISO value is set to 250.
     */
    PVEyeCameraISO320,
    /**
     *  The ISO value is set to 160.
     */
    PVEyeCameraISO400,
    /**
     *  The ISO value is set to 160.
     */
    PVEyeCameraISO500,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO640,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO800,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO1000,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO1250,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO1600,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO2000,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO2500,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO3200,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO4000,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO5000,
    /**
     *  The ISO value is set to 800.
     */
    PVEyeCameraISO6400,
};

/**
 * camera light-metering mode
 */
typedef NS_ENUM(NSUInteger, PVEyeCameraMeteringMode) {
    /**
     *  Center-weighted
     */
    PVEyeCameraMeteringModeCenter=51,
    /**
     *  Average
     */
    PVEyeCameraMeteringModeAverage,
    /**
     *  Spot metering
     */
    PVEyeCameraMeteringModePoint,
};

typedef NS_ENUM(NSUInteger, PVEyeOSDSwitchState){
    
    /**
     *  close
     */
    PVEyeOSDSwitchStateClose=51,
    /**
     *  open
     */
    PVEyeOSDSwitchStateOpen,
    
};

/**
 *  telecontroller's automatic off time
 */
typedef NS_ENUM(NSUInteger, PVCameraAutoOffTime) {
    /**
     *
     */
    PVCameraAutoOffTimeAuto=51,
    /**
     *
     */
    PVCameraAutoOffTime30s,
    /**
     *
     */
    PVCameraAutoOffTime1m,
    /**
     *
     */
    PVCameraAutoOffTime2m,
    /**
     *
     */
    PVCameraAutoOffTime4m,
    /**
     *
     */
    PVCameraAutoOffTime8m,
    /**
     *
     */
    PVCameraAutoOffTime15m,
};



@end
