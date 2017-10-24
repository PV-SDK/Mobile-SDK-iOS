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
 *  相机连拍模式
 */
typedef NS_ENUM(NSUInteger, PVCameraContinuousMode) {
    /**
     *  普通模式
     */
    PVCameraContinuousModeNormal=1,
    /**
     *  连拍模式
     */
    PVCameraContinuousModeContinuous,
};

/**
 *  照片尺寸
 */
typedef NS_ENUM(NSUInteger, PVCameraPhotoAspectRatio) {
    /**
     *  照片尺寸为4608x3456  暂不支持
     */
    PVCameraPhotoAspectRatio4608x3456=1,
    /**
     *  照片尺寸为4254x3264
     */
    PVCameraPhotoAspectRatio4254x3264,
    /**
     *  照片尺寸为4000x3000
     */
    PVCameraPhotoAspectRatio4000x3000,
    /**
     *  照片尺寸为3840x2160
     */
    PVCameraPhotoAspectRatio3840x2160,
    /**
     *  照片尺寸为2560x1920
     */
    PVCameraPhotoAspectRatio2560x1920,
    /**
     *  照片尺寸为2048x1536  暂不支持
     */
    PVCameraPhotoAspectRatio2048x1536,
};

/**
 *  视频分辨率
 */
typedef NS_ENUM(NSUInteger, PVCameraVideoResolution) {
    /**
     *  视频分辨率为4K 3840x2160 30P  16:9
     */
    PVCameraVideoResolution3840x2160=1,
    /**
     *  视频分辨率为2.7K 2704x1520 30P  16:9  暂不支持，拍摄会变形
     */
    PVCameraVideoResolution2704x1520,
    /**
     *  视频分辨率为1080P: 1920*1080  120P 16:9
     */
    PVCameraVideoResolution1920x1080_120P,
    /**
     *  视频分辨率为1080P: 1920*1080  60P 16:9
     */
    PVCameraVideoResolution1920x1080_60P,
    /**
     *  视频分辨率为1080P: 1920*1080 30P  16:9
     */
    PVCameraVideoResolution1920x1080_30P,
    /**
     *  视频分辨率为720P: 1280x720 240P  16:9
     */
    PVCameraVideoResolution1280x720_240P,
    /**
     *  视频分辨率为720P: 1280x720 120P  16:9
     */
    PVCameraVideoResolution1280x720_120P,

};

/**
 *  照片画质
 */
typedef NS_ENUM(NSUInteger, PVCameraPhotoQuality) {
    /**
     *  normal
     */
    PVCameraPhotoQualityNormal=1,
    /**
     *  fine
     */
    PVCameraPhotoQualityFine,
    /**
     *  superFine
     */
    PVCameraPhotoQualitySuFine,
};

typedef NS_ENUM (NSUInteger, PVCameraISO){
    /**
     *  The ISO value is automatically set. This cannot be used for all cameras when in Manual mode.
     */
    PVCameraISOAuto=1,
    /**
     *  The ISO value is set to 100.
     */
    PVCameraISO100,
    /**
     *  The ISO value is set to 200.
     */
    PVCameraISO200,
    /**
     *  The ISO value is set to 400.
     */
    PVCameraISO400,
    /**
     *  The ISO value is set to 800.
     */
    PVCameraISO800,
    /**
     *  The ISO value is set to 1600.
     */
    PVCameraISO1600,
};

/**
 *  相机EV值
 */
typedef NS_ENUM(NSUInteger, PVCameraEV) {
    /**
     *  EV值：-2.0
     */
    PVCameraEVN20=1,
    /**
     *  EV值：-1.7
     */
    PVCameraEVN17,
    /**
     *  EV值：-1.3
     */
    PVCameraEVN13,
    /**
     *  EV值：-1.0
     */
    PVCameraEVN10,
    /**
     *  EV值：-0.7
     */
    PVCameraEVN07,
    /**
     *  EV值：-0.3
     */
    PVCameraEVN03,
    /**
     *  EV值：0
     */
    PVCameraEV00,
    /**
     *  EV值：0.3
     */
    PVCameraEV03,
    /**
     *  EV值：0.7
     */
    PVCameraEV07,
    /**
     *  EV值：1.0
     */
    PVCameraEV10,
    /**
     *  EV值：1.3
     */
    PVCameraEV13,
    /**
     *  EV值：-1.7
     */
    PVCameraEV17,
    /**
     *  EV值：2.0
     */
    PVCameraEV20,
};

/**
 *  相机白平衡
 */
typedef NS_ENUM(NSInteger,PVCameraWhiteBalance) {
    /**
     *  自动
     */
    PVWhiteBalanceAuto=1,
    /**
     *  日光
     */
    PVWhiteBalanceSunny=2,
    /**
     *  多云
     */
    PVWhiteBalanceCloudy=3,
    /**
     *  白炽灯
     */
    PVWhiteBalanceIncandescent=4,
    /**
     *  荧光灯
     */
    PVWhiteBalanceFluorescent=5,
    /**
     *  water
     */
    PVWhiteBalanceWater=6,
    /**
     *  户外
     */
    PVWhiteBalanceOutdoor=7,
};

/**
 *  相机测光模式
 */
typedef NS_ENUM(NSUInteger, PVCameraMeteringMode) {
    /**
     *  平均测光
     */
    PVCameraMeteringModeAverage=1,
    /**
     *  多点测光
     */
    PVCameraMeteringModeMulti,
    /**
     *  中心测光
     */
    PVCameraMeteringModeCenter,
};

/**
 *  照片风格
 */
typedef NS_ENUM(NSUInteger, PVCameraStyle) {
    /**
     *  正常
     */
    PVCameraStyleNormal=1,
    /**
     *  油画
     */
    PVCameraStyleCanvas,
    /**
     *  复古
     */
    PVCameraStyleOldTime,
    /**
     *  负片
     */
    PVCameraStyleNagtive,
    /**
     *  黑白
     */
    PVCameraStyleBlackWhite,
    /**
     *  色彩增强
     */
    PVCameraStyleCloroEnhance,
    /**
     *  70年代
     */
    PVCameraStyle70sYear,
};

/**
 *  照片锐度
 */
typedef NS_ENUM(NSUInteger, PVCameraAcutance) {
    /**
     *  锋利
     */
    PVCameraAcutanceSharp=1,
    /**
     *  正常
     */
    PVCameraAcutanceNormal,
    /**
     *  柔和
     */
    PVCameraAcutancesoft,
};

/**
 *  照片文件格式
 */
typedef NS_ENUM(NSUInteger, PVCameraPhotoFileFormat) {
    /**
     *  JPEG
     */
    PVCameraPhotoFileFormatJPEG=1,
    /**
     *  DNG
     */
    PVCameraPhotoFileFormatDNG,
};

/**
 *  相机连拍速度
 */
typedef NS_ENUM(NSUInteger, PVCameraContinuousShootSpeed) {
    /**
     *  3张/s
     */
    PVCameraContinuousShootSpeed3=1,
    /**
     *  5张/s
     */
    PVCameraContinuousShootSpeed5,
    /**
     *  10张/s
     */
    PVCameraContinuousShootSpeed10,
};

/**
 *  视频制式
 */
typedef NS_ENUM(NSUInteger, PVCameraVideoStandard) {
    /**
     *  NTSC
     */
    PVCameraVideoStandardNTSC=1,
    /**
     *  PAL
     */
    PVCameraVideoStandardPAL,
};

/**
 *  视频文件格式
 */
typedef NS_ENUM (NSUInteger, PVCameraVideoFileFormat){
    /**
     *  MP4
     */
    PVCameraVideoFileFormatMP4=1,
    /**
     *  MOV
     */
    PVCameraVideoFileFormatMOV,
};

/**
 *  视频质量
 */
typedef NS_ENUM (NSUInteger, PVCameraVideoQuality){
    /**
     *  超精细
     */
    PVCameraVideoQualitySuper=1,
    /**
     *  精细
     */
    PVCameraVideoQualityFine,
    /**
     *  普通
     */
    PVCameraVideoQualityNormal,
};

/**
 *  拍摄场景设置
 */
typedef NS_ENUM (NSUInteger, PVCameraSenceMode){
    /**
     *  正常
     */
    PVCameraSenceModeNormal=1,
    /**
     *  闪光
     */
    PVCameraSenceModeFlash,
    /**
     *  夜晚
     */
    PVCameraSenceModeNight,
    /**
     *  运动
     */
    PVCameraSenceModeSport,
    /**
     *
     */
    PVCameraSenceModeLandscape,
    /**
     *
     */
    PVCameraSenceModePortrial,
    /**
     *  日落
     */
    PVCameraSenceModeSunset,
};

/**
 *  设置图像刷新频率
 */
typedef NS_ENUM (NSUInteger, PVCameraRefreshRate){
    /**
     *  正常
     */
    PVCameraRefreshRateAuto=1,
    /**
     *  闪光
     */
    PVCameraRefreshRate50,
    /**
     *  夜晚
     */
    PVCameraRefreshRate60,
};

/**
 *  设置长曝光
 */
typedef NS_ENUM (NSUInteger, PVCameraLongExposure){
    /**
     *  正常
     */
    PVCameraLongExposureOff=1,
    /**
     *  闪光
     */
    PVCameraLongExposure030,
    /**
     * 1s
     */
    PVCameraLongExposure1,
    /**
     * 2s
     */
    PVCameraLongExposure2,
    /**
     * 5s
     */
    PVCameraLongExposure5,
    /**
     * 10s
     */
    PVCameraLongExposure10,
    /**
     * 20s
     */
    PVCameraLongExposure20,
    /**
     * 30s
     */
    PVCameraLongExposure30,
    /**
     * 60s
     */
    PVCameraLongExposure60,
};


/**
 *  相机标记
 */
typedef NS_ENUM(NSUInteger,PVCameraMarkerType) {
    /**
     * 关闭
     */
    PVCameraMarkerTypeClose,
    /**
     * 日期
     */
    PVCameraMarkerTypeDate,
    /**
     * 时间
     */
    PVCameraMarkerTypeTime,
    /**
     * 日期+时间
     */
    PVCameraMarkerTypeDateTime
};


//********************************************************************************

/**
 *  视频录制尺寸设置
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoSize) {
    /**
     *  4KP30
     */
    PVCameraVideoSize4KP30=51,
    
    /**
     *  4KP24
     */
//    PVCameraVideoSize4KP24=52,
    
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
     *  1080P24
     */
//    PVCameraVideoSize1080P24=62,

    /**
     *  720P240 暂不支持
     */
//    PVCameraVideoSize720P240=63,
    /**
     *  720P60  暂不支持
     */
//    PVCameraVideoSize720P60=64,
    
    /**
     *  WVGAP30
     */
    PVCameraVideoSizeWVGAP30=61,
};

/**
 *  相机录制AF设置
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoAF) {
    /**
     *  正常
     */
    PVCameraVideoAFNormal=51,
    /**
     *  自由移动
     */
    PVCameraVideoAFFree,
};

/**
 *  相机连续对焦
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoKPZoom) {
    /**
     *  关闭
     */
    PVCameraVideoKPZoomClose=51,
    /**
     *  开启
     */
    PVCameraVideoKPZoomOpen,
};

/**
 *  相机CAF范围设置
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoCAF) {
    /**
     *  远
     */
    PVCameraVideoCAFFar=51,
    /**
     *  近
     */
    PVCameraVideoCAFNear,
    /**
     *  正常
     */
    PVCameraVideoCAFNormal,
};

/**
 *  相机CAF灵敏度设置
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoCAFLevel) {
    /**
     *  高
     */
    PVCameraVideoCAFLevelHigh=51,
    /**
     *  中
     */
    PVCameraVideoCAFLevelMid,
    /**
     *  低
     */
    PVCameraVideoCAFLevelLow,
};

/**
 *  相机连拍速度
 */
typedef NS_ENUM(NSUInteger, PVEyeCameraContinuousShootSpeed) {
    /**
     *  低速
     */
    PVEyeCameraContinuousShootSpeedLow=51,
    /**
     *  中低速
     */
    PVEyeCameraContinuousShootSpeedMidLow,
    /**
     *  中速
     */
    PVEyeCameraContinuousShootSpeedMid,
    /**
     *  高速
     */
    PVEyeCameraContinuousShootSpeedHigh,
};


/**
 *  摄像快门速度
 */
typedef NS_ENUM(NSUInteger,PVCameraVideoShutterSpeed) {
    /**
     *  自动
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
 *  照片尺寸设置
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
 *  照片质量
 */
typedef NS_ENUM(NSUInteger,PVEyeCameraPhotoQuality) {
    /**
     *  基本
     */
    PVEyeCameraPhotoQualityNormal=51,
    /**
     *  精细
     */
    PVEyeCameraPhotoQualityFine,
    /**
     *  超精细
     */
    PVEyeCameraPhotoQualitySuperFine,
    /**
     *  JPEG+DNG
     */
    PVEyeCameraPhotoQualityJPEGDNG,
};

/**
 *  拍照模式
 */
typedef NS_ENUM(NSUInteger,PVEyeCameraMode) {
    /**
     *  单拍
     */
    PVEyeCameraModeSingle=51,
    /**
     *  连拍
     */
    PVEyeCameraModeContinuous,
    /**
     *  延时拍摄
     */
    PVEyeCameraModeDely,
};

/**
 *  拍照快门速度设置
 */
typedef NS_ENUM(NSUInteger,PVCameraPhotoShutterSpeed) {
    /**
     *  自动
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
 *  光圈大小
 */
typedef NS_ENUM(NSUInteger,PVCameraAperture) {
//    /**
//     *  1.7
//     */
//    PVCameraAperture17=51,
//    /**
//     *  2.0
//     */
//    PVCameraAperture20,
//    /**
//     *  2.3
//     */
//    PVCameraAperture23,
//    /**
//     *  2.7
//     */
//    PVCameraAperture27,
//    /**
//     *  3.0
//     */
//    PVCameraAperture30,
//    /**
//     *  3.3
//     */
//    PVCameraAperture33,
//    /**
//     *  3.7
//     */
//    PVCameraAperture37,
//    /**
//     *  4.0
//     */
//    PVCameraAperture40,
//    /**
//     *  4.3
//     */
//    PVCameraAperture43,
//    /**
//     *  4.7
//     */
//    PVCameraAperture47,
//    /**
//     *  5.0
//     */
//    PVCameraAperture50,
//    /**
//     *  5.3
//     */
//    PVCameraAperture53,
//    /**
//     *  5.7
//     */
//    PVCameraAperture57,
//    /**
//     *  6.0
//     */
//    PVCameraAperture60,
//    /**
//     *  6.3
//     */
//    PVCameraAperture63,
//    /**
//     *  6.7
//     */
//    PVCameraAperture67,
//    /**
//     *  7.0
//     */
//    PVCameraAperture70,
    
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
 *  相机白平衡
 */
typedef NS_ENUM(NSInteger,PVEyeCameraWhiteBalanceMode) {
    /**
     *  自动
     */
    PVEyeCameraWhiteBalanceModeAuto=51,
    /**
     *  手动
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
 *  相机测光模式
 */
typedef NS_ENUM(NSUInteger, PVEyeCameraMeteringMode) {
    /**
     *  中心测光
     */
    PVEyeCameraMeteringModeCenter=51,
    /**
     *  平均测光
     */
    PVEyeCameraMeteringModeAverage,
    /**
     *  点测
     */
    PVEyeCameraMeteringModePoint,
};

typedef NS_ENUM(NSUInteger, PVEyeOSDSwitchState){
    
    /**
     *  关闭
     */
    PVEyeOSDSwitchStateClose=51,
    /**
     *  开启
     */
    PVEyeOSDSwitchStateOpen,

};

/**
 *  遥控器自动关机时间
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
