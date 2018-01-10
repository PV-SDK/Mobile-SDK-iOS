//
//  PVEyeCamera.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import "PVBaseComponent.h"
#import "PVCameraSDCardState.h"
#import "PVEyeCameraSettingsDef.h"

typedef NS_ENUM (NSUInteger, PVEyeCameraShootMode){
    PVEyeCameraShootModeTakePhoto   = 0,    ///< Take Photo Mode
    PVEyeCameraShootModeRecord      = 1     ///< Record Mode
};

typedef NS_ENUM (NSUInteger, PVEyeCameraState){
    PVEyeCameraState_Exist,                 ///< Camera exist.
    PVEyeCameraState_RecStop,               ///< Finished recording.
    PVEyeCameraState_Recing,                ///< Recording.
    PVEyeCameraState_RecStartError,         ///< Failed to start recording.
    PVEyeCameraState_RecStopError,          ///< Failed to finish recording.
    PVEyeCameraState_RecModeSuccess,        ///< Switch to rec mode successfully.
    PVEyeCameraState_RecModeError,          ///< Failed to switch to rec mode.
    PVEyeCameraState_ShootSuccess,          ///< Shoot successfully.
    PVEyeCameraState_Shooting,              ///< Shooting.
    PVEyeCameraState_ShootError,            ///< Shooting error.
    PVEyeCameraState_ShootModeSuccess,      ///< Switch to shooting mode successfully.
    PVEyeCameraState_ShootModeError,        ///< Failed to switch to  shooting mode
    PVEyeCameraState_Timeout,               ///< Operation timeout.
    PVEyeCameraState_ShootErrorSDFull,      ///< SD card is full when taking photos.
    PVEyeCameraState_ShootErrorSDError,     ///< SD card error when taking photos.
    PVEyeCameraState_ShootErrorSDNull,      ///< SD card is empty when taking photos.
    PVEyeCameraState_RecErrorSDFull,        ///< The SD card is full when recording.
    PVEyeCameraState_RecErrorSDError,       ///< SD card error  when recording.
    PVEyeCameraState_RecErrorSDNull,        ///< SD card is empty when recording.
    PVEyeCameraState_FlirShootSuccess,      ///< Shoot successfully by infrared camera.
    PVEyeCameraState_FlirRecing,            ///< Infrared camera  is recording.
    PVEyeCameraState_FlirRecStop,           ///< Infrared camera stop recording.
    PVEyeCameraState_ChangeFlir,            ///< Completed switching to infrared camera.
    PVEyeCameraState_ChangeNormal,          ///< Switch to camera successfully.
    PVEyeCameraState_FlirCalSuccess,        ///< Infrared camera calibrate successfully.
    PVEyeCameraState_FlirCalFail            ///< Failed to calibrate by infrared camera.
};

@class PVEyeCamera;
@protocol PVEyeCameraDelegate <NSObject>

/**
 Return to this method when the camera's state changes

 @param camera camera
 @param cameraState camera state
 */
- (void)pv_camera:(PVEyeCamera *_Nullable)camera didUpdateCameraState:(PVEyeCameraState)cameraState;

@end

@interface PVEyeCamera : PVBaseComponent

NS_ASSUME_NONNULL_BEGIN

@property (nonatomic, weak) id<PVEyeCameraDelegate>delegate;

NS_ASSUME_NONNULL_END

+ (PVEyeCamera *_Nullable)product;

#pragma mark - Camera Control

/**
 Change Camera Mode

 @param mode Camera Mode
 */
- (void)setEyeCameraMode:(PVEyeCameraShootMode)mode;
/**
 *  Take photo
 */
- (void)takePhoto;

/**
 *  Start recording
 */
- (void)startRecordVideo;

/**
 *  Stop Recording
 */
- (void)stopRecordVideo;

/**
 Format the SD card

 @param block CallBack Results
 */
- (void)formatSDWithCompletion:(PVCompletionBlock)block;

/**
 Factory reset

 @param block Callback results
 */
- (void)resetToEyeCameraFactoryWithCompletion:(PVCompletionBlock)block;

/**
 Get the camera current mode

 @param block CallBack Results
 */
- (void)getEyeCameraCurrentState:(void (^_Nonnull)(PVEyeCameraState camerastate, NSError *_Nullable error))block;

/**
 Get the capacity of camera SD card

 @param block CallBack Results
 */
- (void)getEyeCameraSDRemainingCapacityWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

/**
 Get the capacity of camera SD card(unsolicited)
 
 @param block Callback results
 */
- (void)getEyeCameraSDRemainingCapacityNORequestWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

#pragma mark - Camera Setting
/**
 Set the Video Size of PowerEye

 @param videoSize Video Size
 @param block Callback results
 */
- (void)setEyeCameraVideoSize:(PVEyeCameraVideoSize)videoSize withCompletion:(PVCompletionBlock)block;

/**
 Get the Vedio Size of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraVideoSizeWithCompletion:(void (^_Nonnull)(PVEyeCameraVideoSize videoSize, NSError *_Nullable error))block;

/**
 Set the AF recording of PowerEye

 @param videoAF AF Value
 @param block Callback results
 */
- (void)setEyeCameraVideoAF:(PVEyeCameraVideoAF)videoAF withCompletion:(PVCompletionBlock)block;

/**
 Get the AF recording of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraVideoAFWithCompletion:(void (^_Nonnull)(PVEyeCameraVideoAF videoAF, NSError *_Nullable error))block;

/**
 Get the Camera shutter speed of PowerEye

 @param videoShutterSpeed Camera shutter speed
 @param block Callback results
 */
- (void)setEyeCameraVideoShutterSpeed:(PVEyeCameraVideoShutterSpeed)videoShutterSpeed withCompletion:(PVCompletionBlock)block;

/**
 Get the Camera shutter speed of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraVideoShutterSpeedWithCompletion:(void (^_Nonnull)(PVEyeCameraVideoShutterSpeed videoShutterSpeed, NSError *_Nullable error))block;

/**
 Set the photo size of PowerEye

 @param videoCAFLevel  photo size
 @param block          callback results
 */
- (void)setEyeCameraPhotoSize:(PVEyeCameraPhotoSize)photoSize withCompletion:(PVCompletionBlock)block;

/**
 Get the photo size of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraPhotoSizeWithCompletion:(void (^_Nonnull)(PVEyeCameraPhotoSize photoSize, NSError *_Nullable error))block;

/**
 Set the photo quality of PowerEye

 @param photoQuality Photo quality
 @param block Callback results
 */
- (void)setEyeCameraPhotoQuality:(PVEyeCameraPhotoQuality)photoQuality withCompletion:(PVCompletionBlock)block;

/**
 Get the photo quality of PowerEye
 
 @param block callback results
 */
- (void)getEyeCameraPhotoQualityWithCompletion:(void (^_Nonnull)(PVEyeCameraPhotoQuality photoQuality, NSError *_Nullable error))block;

/**
 Set the camera mode of PowerEye

 @param cameraMode Camera mode
 @param block CallBack results
 */
- (void)setEyeCameraMode:(PVEyeCameraMode)cameraMode withCompletion:(PVCompletionBlock)block;

/**
 Get the camera mode of PowerEye

 @param block CallBack results
 */
- (void)getEyeCameraModeWithCompletion:(void (^_Nonnull)(PVEyeCameraMode cameraMode, NSError *_Nullable error))block;

/**
 Set the  Burst speed of PowerEye
 
 @param cameraMode Burst speed
 @param block     Callback results
 */
- (void)setEyeCameraContinuousShootSpeed:(PVEyeCameraContinuousShootSpeed)shootSpeed withCompletion:(PVCompletionBlock)block;

/**
 Get the  Burst speed of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraContinuousShootSpeedWithCompletion:(void (^_Nonnull)(PVEyeCameraContinuousShootSpeed shootSpeed, NSError *_Nullable error))block;

/**
 Set the Photo shutter speed of PowerEye

 @param shutterSpeed Photo shutter speed
 @param block Callback results
 */
- (void)setEyeCameraPhotoShutterSpeed:(PVEyeCameraPhotoShutterSpeed)shutterSpeed withCompletion:(PVCompletionBlock)block;

/**
 Get the Photo shutter speed of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraPhotoShutterSpeedWithCompletion:(void (^_Nonnull)(PVEyeCameraPhotoShutterSpeed shutterSpeed, NSError *_Nullable error))block;

/**
 Set the Camera aperture size of PowerEye

 @param aperture f-number
 @param block Callback results
 */
- (void)setEyeCameraAperture:(PVEyeCameraAperture)aperture withCompletion:(PVCompletionBlock)block;

/**
 Get the Camera aperture size of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraApertureWithCompletion:(void (^_Nonnull)(PVEyeCameraAperture aperture, NSError *_Nullable error))block;

/**
 Set the white balance of PowerEye

 @param whiteBalancemode（manual/automatic）
 @param block Callback results
 */
- (void)setEyeCameraWhiteBalanceMode:(PVEyeCameraWhiteBalanceMode)whiteBalanceMode withCompletion:(PVCompletionBlock)block;

/**
 Get the white balance of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraWhiteBalanceModeWithCompletion:(void (^_Nonnull)(PVEyeCameraWhiteBalanceMode whiteBalanceMode, NSError *_Nullable error))block;

/**
 Set the exposure compensation of PowerEye

 @param exposure value （-96~96）
 @param block Callback results
 */
- (void)setEyeCameraExposure:(NSInteger)exposure withCompletion:(PVCompletionBlock)block;

/**
 Get the exposure compensation
 
 @param block Callback results
 */
- (void)getEyeCameraExposureWithCompletion:(void (^_Nonnull)(NSInteger exposure, NSError *_Nullable error))block;

/**
 *  Set the white balance parameters of PowerEye camera in manual mode
 *
 *  @param whiteBalancevalue(-100~100)
 *  @param block Callback results
 */
- (void)setEyeCameraWhiteBalance:(NSInteger)whiteBalance withCompletion:(PVCompletionBlock)block;

/**
 Get the white balance parameters of PowerEye camera in manual mode
 
 @param block Callback results
 */
- (void)getEyeCameraWhiteBalanceWithCompletion:(void (^_Nonnull)(NSInteger whiteBalance, NSError *_Nullable error))block;

/**
 Set the camera ISO of PowerEye
 
 @param ISOvalue
 @param block Callback results
 */
- (void)setEyeCameraISO:(PVEyeCameraISO)iso withCompletion:(PVCompletionBlock)block;

/**
 Get the camera ISO of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraISOWithCompletion:(void (^_Nonnull)(PVEyeCameraISO iso, NSError *_Nullable error))block;

/**
 Set the Light-metering of PowerEye

 @param meteringMode Light-metering
 @param block Callback results
 */

- (void)setEyeCameraMeteringMode:(PVEyeCameraMeteringMode)meteringMode withCompletion:(PVCompletionBlock)block;

/**
 Get the Light-metering mode of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraMeteringModeWithCompletion:(void (^_Nonnull)(PVEyeCameraMeteringMode meteringMode, NSError *_Nullable error))block;

/**
 Set the picture brightness of PowerEye

 @param brightness Brightness value
 @param block Callback results
 */
- (void)setEyeCameraImageBrightness:(NSInteger)brightness withCompletion:(PVCompletionBlock)block;

/**
 Get the picture brightness of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraImageBrightnessWithCompletion:(void (^_Nonnull)(NSInteger brightness, NSError *_Nullable error))block;

/**
 Set the PowerEye image sharpness

 @param sharpness Sharpness value
 @param block Callback results
 */
- (void)setEyeCameraImageSharpness:(NSInteger)sharpness withCompletion:(PVCompletionBlock)block;

/**
 Get the PowerEye image sharpness
 
 @param block Callback results
 */
- (void)getEyeCameraImageSharpnessWithCompletion:(void (^_Nonnull)(NSInteger sharpness, NSError *_Nullable error))block;

/**
 Set the camera image Saturation

 @param Saturation Saturation value
 @param block Callback results
 */
- (void)setEyeCameraImageSaturation:(NSInteger)saturation withCompletion:(PVCompletionBlock)block;

/**
 Get the camera image Saturation
 
 @param block Callback results
 */
- (void)getEyeCameraImageSaturationWithCompletion:(void (^_Nonnull)(NSInteger saturation, NSError *_Nullable error))block;

/**
 Set the PowerEye image contrast

 @param brightness Contrast value
 @param block Callback results
 */
- (void)setEyeCameraImageContrast:(NSInteger)contrast withCompletion:(PVCompletionBlock)block;

/**
 Get the PowerEye image contrast
 
 @param block Callback results
 */
- (void)getEyeCameraImageContrastWithCompletion:(void (^_Nonnull)(NSInteger contrast, NSError *_Nullable error))block;

/**
 Set the time-lapse shooting of PowerEye

 @param time Time(1~1799)
 @param block Callback results
 */
- (void)setEyeCameraTakePhotoDelyTime:(NSInteger)time withCompletion:(PVCompletionBlock)block;

/**
 Get the time-lapse shooting of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraTakePhotoDelyTimeWithCompletion:(void (^_Nonnull)(NSInteger time, NSError *_Nullable error))block;

/**
 Set the number of PowerEye time-lapse shooting

 @param num Number(2~100)
 @param block Callback results
 */
- (void)setEyeCameraTakePhotoDelyNum:(NSInteger)num withCompletion:(PVCompletionBlock)block;

/**
 Get the number of PowerEye time-lapse shooting
 
 @param block Callback results
 */
- (void)getEyeCameraTakePhotoDelyNumWithCompletion:(void (^_Nonnull)(NSInteger num, NSError *_Nullable error))block;

/**
 Set the superposition switch of PowerEye OSD

 @param open BOOL
 @param block Callback results
 */
- (void)setEyeCameraOSDSwitchOpenState:(PVEyeOSDSwitchState)state WithCompletion:(PVCompletionBlock)block;

/**
 Get the Superposition switch state of PowerEye OSD

 @param block Callback results
 */
- (void)getEyeCameraOSDSwitchOpenStatusWithCompletion:(void (^_Nonnull)(PVEyeOSDSwitchState state, NSError *_Nullable error))block;

/**
 Get all settings of PowerEye

 @param block Callback results
 */
- (void)getEyeCameraAllSettingWithCompletion:(PVCompletionBlock)block;

@end
