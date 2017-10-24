//
//  PVCamera.h
//  PVSDK
//
//  Created by Layne on 16/6/24.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import "PVBaseComponent.h"
#import "PVCameraSDCardState.h"
#import "PVCameraSettingsDef.h"

typedef NS_ENUM (NSUInteger, PVCameraType){
    PVCameraTypeUnknown=1,//未知
    PVCameraTypeShunmeng,//
    PVCameraTypeZcamera,//
    PVCameraTypeEncoder_zcamera,//可见光相机
    PVCameraTypeEncoder_flir,//红外相机
};


typedef NS_ENUM (NSUInteger, PVCameraMode){
    PVCameraModeShootPhoto,//拍照模式
    PVCameraModeRecordVideo,//录像模式
};

typedef NS_ENUM (NSUInteger, PVCameraState){
    PVCameraStateExist,//相机存在
    PVCameraStateRecStop,//录像结束
    PVCameraStateRecing,//录像中
    PVCameraStateRecStartError,//启动录像失败
    PVCameraStateRecStopError,//结束录像失败
    PVCameraStateRecModeSuccess,//切换录像模式成功
    PVCameraStateRecModeError,//切换录像模式失败
    PVCameraStateShootSuccess,//拍照成功
    PVCameraStateShooting,//拍照中
    PVCameraStateShootError,//拍照错误
    PVCameraStateShootModeSuccess,//切换拍照模式成功
    PVCameraStateShootModeError,//切换拍照模式失败
    PVCameraStateTimeout,//相机操作超时
    PVCameraStateShootErrorSDFull,//拍照时sd卡已满
    PVCameraStateShootErrorSDError,//拍照时sd卡出错
    PVCameraStateShootErrorSDNull,//拍照时sd卡为空
    PVCameraStateRecErrorSDFull,//录像时sd卡已满
    PVCameraStateRecErrorSDError,//录像时sd卡出错
    PVCameraStateRecErrorSDNull,//录像时sd卡为空
    
    
    PVCameraStateFlirShootSuccess,//红外相机拍照成功
    PVCameraStateFlirRecing,//红外相机录像中
    PVCameraStateFlirRecStop,//红外相机录像停止
    PVCameraStateChangeFlir,//切换红外相机完成
    PVCameraStateChangeNormal,//切换普通相机成功
    PVCameraStateFlirCalSuccess,//红外相机校准成功
    PVCameraStateFlirCalFail,//红外相机校准失败
};

//放大缩小焦距
typedef NS_ENUM (NSUInteger,PVCameraZoomState){
    PVCameraZoomStateStop=51,//停止放大或缩小
    PVCameraZoomStateIn,//缩小
    PVCameraZoomStateOut,//放大
};

//对焦方式：手动/自动
typedef NS_ENUM (NSUInteger,PVCameraZoomType){
    PVCameraZoomTypeManual=51,
    PVCameraZoomTypeAuto,
};

@class PVCamera;
@protocol PVCameraDelegate <NSObject>

@optional
/**
 *  当相机状态发生变化时回到该方法
 *
 *  @param camera      相机
 *  @param cameraState 相机状态
 */
- (void)camera:(PVCamera *_Nonnull)camera didUpdateCameraState:(PVCameraState)cameraState;

/**
 *  当SD卡状态发生改变时回调该方法
 *
 *  @param camera      相机
 *  @param sdCardState SD卡状态
 */
- (void)camera:(PVCamera *_Nonnull)camera didUpdateSDCardState:(PVCameraSDCardState *_Nonnull)sdCardState;

@end

@interface PVCamera : PVBaseComponent

@property (nonatomic,weak)id <PVCameraDelegate>delegate;


- (void)startConnectCamera;

/**
 切换视频流（可见光/红外）

 @param param 视频流参数（可见光：9   红外：10）
 @param block 结果
 */
- (void)changeVideoStreaming:(NSInteger)param withCompletion:(PVCompletionBlock)block;

/**
 *  获取相机类型
 *
 *  @param block 相机类型
 */
- (void)getCameraTypeWithComplection:(void (^_Nonnull)(PVCameraType type,NSError *_Nullable error))block;

/**
 *  获取相机固件版本
 *
 *  @param block 相机版本
 */
- (void)getCameraVersionWithComplection:(void (^_Nonnull)(int version,NSError *_Nullable error))block;

/**
 *  设置相机模式
 *
 *  @param mode 相机模式
 */
- (void)setCameraMode:(PVCameraMode)mode;


/**
 *  获取相机模式
 *
 *  @param block 回调结果
 */
- (void)getCameraModeWithCompletion:(void (^_Nonnull)(PVCameraMode cameraMode))block;

/**
 *  设置相机连拍模式
 *
 *  @param cameraMode 模式
 *  @param block         回调结果
 */
- (void)setCameraContinuousMode:(PVCameraContinuousMode)cameraMode withCompletion:(PVCompletionBlock)block;


/**
 *  设置照片尺寸
 *
 *  @param ratio ratio
 */
- (void)setPhotoRatio:(PVCameraPhotoAspectRatio)ratio withCompletion:(PVCompletionBlock)block;

/**
 *  获取照片尺寸
 *
 *  @param block 回调结果
 */
- (void)getPhotoRatioWithCompletion:(void (^_Nonnull)(PVCameraPhotoAspectRatio photoRatio, NSError *_Nullable error))block;

/**
 *  设置照片质量
 *
 *  @param quality
 */
//- (void)setPhotoQuality:(PVCameraPhotoQuality)quality withCompletion:(PVCompletionBlock)block;

/**
 *  获取照片质量
 *
 *  @param block 回调结果
 */
//- (void)getPhotoQualityWithCompletion:(void (^_Nonnull)(PVCameraPhotoQuality quality,NSError *_Nullable error))block;

/**
 *  设置Egg录像分辨率
 *
 *  @param resolution
 */
- (void)setVideoResolution:(PVCameraVideoResolution)resolution withCompletion:(PVCompletionBlock)block;

/**
 *  获取Egg录像分辨率
 *
 *  @param block 回调结果
 */
- (void)getVideoResolutionWithCompletion:(void (^_Nonnull)(PVCameraVideoResolution videoResolution, NSError * _Nullable error))block;

/**
 *  设置相机ISO
 *
 *  @param iso   ISO值
 *  @param block 回调结果
 */
- (void)setISO:(PVCameraISO)iso withCompletion:(PVCompletionBlock)block;

/**
 *  获取相机ISO
 *
 *  @param block 回调结果
 */
- (void)getISOWithCompletion:(void (^_Nonnull)(PVCameraISO iso, NSError *_Nullable error))block;

/**
 *  设置相机EV值
 *
 *  @param ev    EV值
 *  @param block 回调结果
 */
- (void)setEV:(PVCameraEV)ev withCompletion:(PVCompletionBlock)block;

/**
 *  获取相机EV值
 *
 *  @param block 回调结果
 */
- (void)getEVWithCompletion:(void (^_Nonnull)(PVCameraEV ev, NSError *_Nullable error))block;

/**
 *  设置相机白平衡
 *
 *  @param whiteBalance值
 *  @param block 回调结果
 */
- (void)setWhiteBalance:(PVCameraWhiteBalance)whiteBalance withCompletion:(PVCompletionBlock)block;

/**
 *  获取相机白平衡
 *
 *  @param block 回调结果
 */
- (void)getWhiteBalanceWithCompletion:(void (^_Nonnull)(PVCameraWhiteBalance whiteBalance, NSError *_Nullable error))block;

/**
 *  设置相机测光模式
 *
 *  @param meteringMode 测光模式
 *  @param block        回调结果
 */
- (void)setMeteringMode:(PVCameraMeteringMode)meteringMode withCompletion:(PVCompletionBlock)block;

/**
 *  获取相机测光模式
 *
 *  @param block 回调结果
 */
- (void)getMeteringModeWithCompletion:(void (^_Nonnull)(PVCameraMeteringMode meteringMode, NSError *_Nullable error))block;

/**
 *  设置照片风格
 *
 *  @param cameraStyle 照片风格
 *  @param block       回调结果
 */
- (void)setCameraStyle:(PVCameraStyle)cameraStyle withCompletion:(PVCompletionBlock)block;

/**
 *  获取照片风格
 *
 *  @param block 回调结果
 */
- (void)getCameraStyleWithCompletion:(void (^_Nonnull)(PVCameraStyle cameraStyle, NSError *_Nullable error))block;

/**
 *  设置照片锐度
 *
 *  @param cameraAcutance 照片锐度
 *  @param block       回调结果
 */
- (void)setCameraAcutance:(PVCameraAcutance)cameraAcutance withCompletion:(PVCompletionBlock)block;

/**
 *  获取照片锐度
 *
 *  @param block 回调结果
 */
- (void)getCameraAcutanceWithCompletion:(void (^_Nonnull)(PVCameraAcutance cameraAcutance, NSError *_Nullable error))block;

/**
 *  设置照片格式
 *
 *  @param cameraPhotoFileFormat 照片锐度
 *  @param block       回调结果
 */
- (void)setCameraPhotoFileFormat:(PVCameraPhotoFileFormat)cameraPhotoFileFormat withCompletion:(PVCompletionBlock)block;

/**
 *  获取照片格式
 *
 *  @param block 回调结果
 */
- (void)getCameraPhotoFileFormatWithCompletion:(void (^_Nonnull)(PVCameraPhotoFileFormat photoFileFormate, NSError *_Nullable error))block;

/**
 *  设置相机连拍速度
 *
 *  @param cameraContinuousShootSpeed 连拍速度
 *  @param block       回调结果
 */
- (void)setCameraContinuousShootSpeed:(PVCameraContinuousShootSpeed)cameraContinuousShootSpeed withCompletion:(PVCompletionBlock)block;

/**
 *  获取相机连拍速度
 *
 *  @param block 回调结果
 */
- (void)getCameraContinuousShootSpeedWithCompletion:(void (^_Nonnull)(PVCameraContinuousShootSpeed cameraContinuousShootSpeed, NSError *_Nullable error))block;


/**
 *  设置视频文件格式
 *
 *  @param cameraVideoFileFormat 视频格式
 *  @param block       回调结果
 */
- (void)setCameraVideoFileFormat:(PVCameraVideoFileFormat)cameraVideoFileFormat withCompletion:(PVCompletionBlock)block;

/**
 *  获取视频文件格式
 *
 *  @param block 回调结果
 */
- (void)getCameraVideoFileFormatWithCompletion:(void (^_Nonnull)(PVCameraVideoFileFormat cameraVideoFileFormat, NSError *_Nullable error))block;

/**
 *  获取SD卡状态信息
 *
 *  @param block 回调结果
 */
- (void)getSDCardStateWithCompletion:(void (^_Nonnull)(PVCameraSDCardState *_Nullable sdCardState))block;

/**
 *  获取相机SD卡容量
 *
 *  @param block 回调结果
 */
- (void)getSDRemainingCapacityWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

/**
 *  获取相机SD卡容量(非请求方式获取)
 *
 *  @param block 回调结果
 */
- (void)getSDRemainingCapacityNORequestWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

/**
 *  获取相机SD卡容量
 *
 *  @param block 回调结果
 */
- (void)getEyeSDRemainingCapacityWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

/**
 *  获取相机SD卡容量（非请求方式）
 *
 *  @param block 回调结果
 */
- (void)getEyeSDRemainingCapacityNORequestWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

/**
 *  拍摄照片
 */
- (void)ShootPhoto;

/**
 *  开始录像
 */
- (void)startRecordVideo;

/**
 *  停止录像
 */
- (void)stopRecordVideo;

/**
 *  红外相机拍摄照片
 */
- (void)ShootPhoto_Flir;

/**
 *  红外相机开始录像
 */
- (void)startRecordVideo_Flir;

/**
 *  红外相机停止录像
 */
- (void)stopRecordVideo_Flir;


/**
 格式化SD卡

 @param block 回调结果
 */
- (void)formatSDWithCompletion:(PVCompletionBlock)block;

/**
 恢复出厂设置

 @param block 回调结果
 */
- (void)resetToCameraFactoryWithCompletion:(PVCompletionBlock)block;

/**
 *  获取相机当前的模式
 *
 *  @param block 回调结果
 */
- (void)getCameraCurrentState:(void (^_Nonnull)(PVCameraState camerastate, NSError *_Nullable error))block;

/**
 *  设置视频质量
 *
 *  @param quality 视频质量
 */
- (void)setVideoQuality:(PVCameraVideoQuality)quality withCompletion:(PVCompletionBlock)block;

/**
 *  获取视频质量
 *
 *  @param block 回调结果
 */
- (void)getVideoQualityWithCompletion:(void (^_Nonnull)(PVCameraVideoQuality quality, NSError *_Nullable error))block;

/**
 *  设置拍摄场景
 *
 *  @param 拍摄场景
 *  @param block       回调结果
 */
- (void)setCameraSenceMode:(PVCameraSenceMode)cameraSenceMode withCompletion:(PVCompletionBlock)block;

/**
 *  获取拍摄场景
 *
 *  @param block 回调结果
 */
- (void)getCameraSenceModeWithCompletion:(void (^_Nonnull)(PVCameraSenceMode senceMode, NSError *_Nullable error))block;

/**
 *  设置图像刷新频率
 *
 *  @param refreshRate 刷新频率
 *  @param block       回调结果
 */
- (void)setCameraRefreshRate:(PVCameraRefreshRate)refreshRate withCompletion:(PVCompletionBlock)block;

- (void)getCameraRefreshRateWithCompletion:(void (^_Nonnull)(PVCameraRefreshRate rate, NSError *_Nullable error))block;

/**
 *  设置长曝光时间
 *
 *  @param longExposure 长曝光时间
 *  @param block       回调结果
 */
- (void)setCameraLongExposure:(PVCameraLongExposure)longExposure withCompletion:(PVCompletionBlock)block;

- (void)getCameraLongExposureWithCompletion:(void (^_Nonnull)(PVCameraLongExposure exposure, NSError * _Nullable))block;

/**
 *  设置视频制式
 *
 *  @param cameraVideoStandard 视频制式
 *  @param block       回调结果
 */
- (void)setCameraVideoStandard:(PVCameraVideoStandard)cameraVideoStandard withCompletion:(PVCompletionBlock)block;

/**
 *  获取视频制式
 *
 *  @param block 回调结果
 */
- (void)getCameraVideoStandardWithCompletion:(void (^_Nonnull)(PVCameraVideoStandard cameraVideoStandard, NSError *_Nullable error))block;

///同步相机时间（年月日时分秒）
- (void)setCameraTimeWithYear:(NSInteger)year month:(NSInteger)month withCompletion:(PVCompletionBlock)block;
- (void)setCameraTimeWithDay:(NSInteger)day hour:(NSInteger)hour withCompletion:(PVCompletionBlock)block;
- (void)setCameraTimeWithMinute:(NSInteger)minute month:(NSInteger)second withCompletion:(PVCompletionBlock)block;

/**
 *  设置视频标记
 *
 *  @param videoMarkerType 标记类型
 */
- (void)setVideoMarkerType:(PVCameraMarkerType)videoMarkerType withCompletion:(PVCompletionBlock)block;

/**
 *  设置照片标记
 *
 *  @param photoMarkerType 标记类型
 */
- (void)setPhotoMarkerType:(PVCameraMarkerType)photoMarkerType withCompletion:(PVCompletionBlock)block;

//*************************PowerEye相关设置****************************

/**
 *  设置变焦类型
 *
 *  @param zoomType 变焦类型
 */
- (void)setCameraZoomType:(PVCameraZoomType)zoomType withCompletion:(PVCompletionBlock)block;

/**
 *  改变摄像头焦距
 *
 *  @param zoomState 焦距状态
 */
- (void)changeCameraZoom:(PVCameraZoomState)zoomState withCompletion:(PVCompletionBlock)block;

/**
 *  设置视频录制尺寸
 *
 *  @param videoSize 视频尺寸
 *  @param block     回调结果
 */
- (void)setCameraVideoSize:(PVCameraVideoSize)videoSize withCompletion:(PVCompletionBlock)block;

- (void)getCameraVideoSizeWithCompletion:(void (^_Nonnull)(PVCameraVideoSize videoSize, NSError *_Nullable error))block;

/**
 *  设置录制AF
 *
 *  @param videoAF AF值
 *  @param block   回调结果
 */
- (void)setCameraVideoAF:(PVCameraVideoAF)videoAF withCompletion:(PVCompletionBlock)block;

- (void)getCameraVideoAFWithCompletion:(void (^_Nonnull)(PVCameraVideoAF videoAF, NSError *_Nullable error))block;


/**
 *  设置连续对焦状态
 *
 *  @param videoKPZoom 开启/关闭
 *  @param block       回调结果
 */
- (void)setCameraVideoKPZoom:(PVCameraVideoKPZoom)videoKPZoom withCompletion:(PVCompletionBlock)block;

- (void)getCameraVideoKPZoomWithCompletion:(void (^_Nonnull)(PVCameraVideoKPZoom videoKPZoom, NSError *_Nullable error))block;

/**
 *  设置相机CAF范围
 *
 *  @param videoCAF CAF范围设置
 *  @param block    回调结果
 */
- (void)setCameraVideoCAF:(PVCameraVideoCAF)videoCAF withCompletion:(PVCompletionBlock)block;

- (void)getCameraVideoCAFWithCompletion:(void (^_Nonnull)(PVCameraVideoCAF videoCAF, NSError *_Nullable error))block;

/**
 *  相机CAF灵敏度设置
 *
 *  @param videoCAFLevel 相机灵敏度
 *  @param block         回调结果
 */
- (void)setCameraVideoCAFLevel:(PVCameraVideoCAFLevel)videoCAFLevel withCompletion:(PVCompletionBlock)block;

- (void)getCameraVideoCAFLevelWithCompletion:(void (^_Nonnull)(PVCameraVideoCAFLevel videoCAFLevel, NSError *_Nullable error))block;


/**
 *  设置摄像快门速度
 *
 *  @param videoCAFLevel 相机摄像快门速度
 *  @param block         回调结果
 */
- (void)setCameraVideoShutterSpeed:(PVCameraVideoShutterSpeed)videoShutterSpeed withCompletion:(PVCompletionBlock)block;

- (void)getCameraVideoShutterSpeedWithCompletion:(void (^_Nonnull)(PVCameraVideoShutterSpeed videoShutterSpeed, NSError *_Nullable error))block;

//*****************拍照模式下********************

/**
 *  设置拍照尺寸
 *
 *  @param videoCAFLevel 拍照尺寸
 *  @param block         回调结果
 */
- (void)setCameraPhotoSize:(PVCameraPhotoSize)photoSize withCompletion:(PVCompletionBlock)block;

- (void)getCameraPhotoSizeWithCompletion:(void (^_Nonnull)(PVCameraPhotoSize photoSize, NSError *_Nullable error))block;


/**
 *  设置照片质量
 *
 *  @param videoCAFLevel 照片质量
 *  @param block         回调结果
 */
- (void)setEyeCameraPhotoQuality:(PVEyeCameraPhotoQuality)photoQuality withCompletion:(PVCompletionBlock)block;

- (void)getEyeCameraPhotoQualityWithCompletion:(void (^_Nonnull)(PVEyeCameraPhotoQuality photoQuality, NSError *_Nullable error))block;


/**
 *  设置拍照模式
 *
 *  @param cameraMode 拍照模式
 *  @param block         回调结果
 */
- (void)setEyeCameraMode:(PVEyeCameraMode)cameraMode withCompletion:(PVCompletionBlock)block;

- (void)getEyeCameraModeWithCompletion:(void (^_Nonnull)(PVEyeCameraMode cameraMode, NSError *_Nullable error))block;


/**
 *  设置PowerEye的连拍速度
 *
 *  @param cameraMode 连拍速度
 *  @param block         回调结果
 */
- (void)setEyeCameraContinuousShootSpeed:(PVEyeCameraContinuousShootSpeed)shootSpeed withCompletion:(PVCompletionBlock)block;

- (void)getEyeCameraContinuousShootSpeedWithCompletion:(void (^_Nonnull)(PVEyeCameraContinuousShootSpeed shootSpeed, NSError *_Nullable error))block;


/**
 *  设置拍照快门速度
 *
 *  @param shutterSpeed 拍照速度
 *  @param block         回调结果
 */
- (void)setCameraPhotoShutterSpeed:(PVCameraPhotoShutterSpeed)shutterSpeed withCompletion:(PVCompletionBlock)block;

- (void)getCameraPhotoShutterSpeedWithCompletion:(void (^_Nonnull)(PVCameraPhotoShutterSpeed shutterSpeed, NSError *_Nullable error))block;


/**
 *  设置光圈大小
 *
 *  @param shutterSpeed 光圈大小
 *  @param block         回调结果
 */
- (void)setPVCameraAperture:(PVCameraAperture)aperture withCompletion:(PVCompletionBlock)block;

- (void)getPVCameraApertureWithCompletion:(void (^_Nonnull)(PVCameraAperture aperture, NSError *_Nullable error))block;


/**
 *  设置PowerEye相机白平衡模式
 *
 *  @param whiteBalance模式（手动/自动）
 *  @param block 回调结果
 */
- (void)setEyeWhiteBalanceMode:(PVEyeCameraWhiteBalanceMode)whiteBalanceMode withCompletion:(PVCompletionBlock)block;

- (void)getEyeWhiteBalanceModeWithCompletion:(void (^_Nonnull)(PVEyeCameraWhiteBalanceMode whiteBalanceMode, NSError *_Nullable error))block;


/**
 *  设置曝光补偿
 *
 *  @param exposure值（-96~96）
 *  @param block 回调结果
 */

- (void)setEyeExposure:(NSInteger)exposure withCompletion:(PVCompletionBlock)block;

- (void)getEyeExposureWithCompletion:(void (^_Nonnull)(NSInteger exposure, NSError *_Nullable error))block;

/**
 *  设置PowerEye相机手动模式下的白平衡参数
 *
 *  @param whiteBalance值(-100~100)
 *  @param block 回调结果
 */
- (void)setEyeWhiteBalance:(NSInteger)whiteBalance withCompletion:(PVCompletionBlock)block;

- (void)getEyeWhiteBalanceWithCompletion:(void (^_Nonnull)(NSInteger whiteBalance, NSError *_Nullable error))block;

/**
 *  设置PowerEye相机ISO
 *
 *  @param ISO值
 *  @param block 回调结果
 */
- (void)setEyeISO:(PVEyeCameraISO)iso withCompletion:(PVCompletionBlock)block;

- (void)getEyeISOWithCompletion:(void (^_Nonnull)(PVEyeCameraISO iso, NSError *_Nullable error))block;

/**
 *  设置PowerEye测光模式
 *
 *  @param meteringMode 测光模式
 *  @param block        回调结果
 */
- (void)setEyeMeteringMode:(PVEyeCameraMeteringMode)meteringMode withCompletion:(PVCompletionBlock)block;

- (void)getEyeMeteringModeWithCompletion:(void (^_Nonnull)(PVEyeCameraMeteringMode meteringMode, NSError *_Nullable error))block;

/**
 *  设置PowerEye图像亮度
 *
 *  @param brightness 亮度值
 *  @param block        回调结果
 */
- (void)setImageBrightness:(NSInteger)brightness withCompletion:(PVCompletionBlock)block;

- (void)getImageBrightnessWithCompletion:(void (^_Nonnull)(NSInteger brightness, NSError *_Nullable error))block;


/**
 *  设置PowerEye图像锐度
 *
 *  @param sharpness 锐度值
 *  @param block        回调结果
 */
- (void)setImageSharpness:(NSInteger)sharpness withCompletion:(PVCompletionBlock)block;

- (void)getImageSharpnessWithCompletion:(void (^_Nonnull)(NSInteger sharpness, NSError *_Nullable error))block;

/**
 *  设置PowerEye图像饱和度
 *
 *  @param Saturation 饱和值
 *  @param block        回调结果
 */
- (void)setImageSaturation:(NSInteger)saturation withCompletion:(PVCompletionBlock)block;

- (void)getImageSaturationWithCompletion:(void (^_Nonnull)(NSInteger saturation, NSError *_Nullable error))block;


/**
 *  设置PowerEye图像对比度
 *
 *  @param brightness 对比度值
 *  @param block        回调结果
 */
- (void)setImageContrast:(NSInteger)contrast withCompletion:(PVCompletionBlock)block;

- (void)getImageContrastWithCompletion:(void (^_Nonnull)(NSInteger contrast, NSError *_Nullable error))block;


/**
 *  设置PowerEye相机自动关机时间
 *
 *  @param time 时间
 *  @param block        回调结果
 */
- (void)setCameraAutoOffTime:(PVCameraAutoOffTime)cameraAutoOffTime withCompletion:(PVCompletionBlock)block;

- (void)getCameraAutoOffTimeWithCompletion:(void (^_Nonnull)(PVCameraAutoOffTime cameraAutoOffTime, NSError *_Nullable error))block;


/**
 *  设置PowerEye拍照延时时间
 *
 *  @param time 时间(1~1799)
 *  @param block        回调结果
 */
- (void)setTakePhotoDelyTime:(NSInteger)time withCompletion:(PVCompletionBlock)block;

- (void)getTakePhotoDelyTimeWithCompletion:(void (^_Nonnull)(NSInteger time, NSError *_Nullable error))block;


/**
 *  设置PowerEye拍照延时数量
 *
 *  @param num 数量(2~100)
 *  @param block        回调结果
 */
- (void)setTakePhotoDelyNum:(NSInteger)num withCompletion:(PVCompletionBlock)block;

- (void)getTakePhotoDelyNumWithCompletion:(void (^_Nonnull)(NSInteger num, NSError *_Nullable error))block;

/**
 *  设置PowerEye OSD叠加开关
 *
 *  @param open BOOL
 *  @param block        回调结果
 */
- (void)setOSDSwitchOpenState:(PVEyeOSDSwitchState)state WithCompletion:(PVCompletionBlock)block;

/**
 *  获取PowerEye  OSD叠加开关
 *
 *  @param block 回调结果
 */
- (void)getOSDSwitchOpenStatusWithCompletion:(void (^_Nonnull)(PVEyeOSDSwitchState state, NSError *_Nullable))block;

/**
 *  获取PowerEye所有设置
 *
 *  @param block 回调结果
 */
- (void)getAllCameraSettingWithCompletion:(PVCompletionBlock)block;


/**
 恢复出厂设置

 @param block 复位结果
 */
- (void)RecoveryfactoryWithComplection:(PVCompletionBlock)block;

/**
 校准红外相机
 */
- (void)calibrationFlirCamera;

/**
 开启相机log
 
 @param path log路径
 */
- (void)startRecordCameraLog:(NSString *)path;


/**
 关闭相机log
  */
- (void)stopRecordCameraLog;

@end
