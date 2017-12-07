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

/**
 相机类型

 - PVCameraTypeUnknown: Unknown
 - PVCameraTypeShunmeng:
 - PVCameraTypeZcamera:
 - PVCameraTypeEncoder_zcamera: Visible light camera
 - PVCameraTypeEncoder_flir: Infrared camera
 */
typedef NS_ENUM (NSUInteger, PVCameraType){
    PVCameraTypeUnknown             = 1,   
    PVCameraTypeShunmeng            = 2,   
    PVCameraTypeZcamera             = 3,   
    PVCameraTypeEncoder_zcamera     = 4,   
    PVCameraTypeEncoder_flir        = 5
};

/**
 拍摄模式

 - PVCameraModeShootPhoto: shoot mode
 - PVCameraModeRecordVideo: record mode
 */
typedef NS_ENUM (NSUInteger, PVCameraMode){
    PVCameraModeShootPhoto      = 0,
    PVCameraModeRecordVideo     = 1
};

/**
 Camera State

 - PVCameraStateExist: Camera exist
 - PVCameraStateRecStop: Finished recording
 - PVCameraStateRecing: Recording
 - PVCameraStateRecStartError: Failed to start recording
 - PVCameraStateRecStopError: Failed to finish recording
 - PVCameraStateRecModeSuccess: Switch to rec mode successfully.
 - PVCameraStateRecModeError: Failed to switch to rec mode
 - PVCameraStateShootSuccess: Shoot successfully
 - PVCameraStateShooting: Shooting
 - PVCameraStateShootError: Shooting error
 - PVCameraStateShootModeSuccess: Switch to shooting mode successfully
 - PVCameraStateShootModeError: Failed to switch to  shooting mode
 - PVCameraStateTimeout: Camera operation timeout
 - PVCameraStateShootErrorSDFull: SD card is full when taking photos
 - PVCameraStateShootErrorSDError: SD card error when taking photos
 - PVCameraStateShootErrorSDNull: SD card is empty when taking photos
 - PVCameraStateRecErrorSDFull: The SD card is full when recording
 - PVCameraStateRecErrorSDError: SD card error  when recording
 - PVCameraStateRecErrorSDNull: SD card is empty when recording
 - PVCameraStateFlirShootSuccess: Shoot successfully by infrared camera
 - PVCameraStateFlirRecing: Infrared camera  is recording
 - PVCameraStateFlirRecStop: Infrared camera stop recording
 - PVCameraStateChangeFlir: Completed switching to infrared camera
 - PVCameraStateChangeNormal: Switch to camera successfully
 - PVCameraStateFlirCalSuccess: Infrared camera calibrate successfully
 - PVCameraStateFlirCalFail: Failed to calibrate by infrared camera
 */
typedef NS_ENUM (NSUInteger, PVCameraState){
    PVCameraStateExist,            
    PVCameraStateRecStop,          
    PVCameraStateRecing,           
    PVCameraStateRecStartError,    
    PVCameraStateRecStopError,
    PVCameraStateRecModeSuccess,   
    PVCameraStateRecModeError,
    PVCameraStateShootSuccess,     
    PVCameraStateShooting,         
    PVCameraStateShootError,
    PVCameraStateShootModeSuccess, 
    PVCameraStateShootModeError,
    PVCameraStateTimeout,
    PVCameraStateShootErrorSDFull, 
    PVCameraStateShootErrorSDError,
    PVCameraStateShootErrorSDNull, 
    PVCameraStateRecErrorSDFull,   
    PVCameraStateRecErrorSDError,  
    PVCameraStateRecErrorSDNull,
    PVCameraStateFlirShootSuccess, 
    PVCameraStateFlirRecing,
    PVCameraStateFlirRecStop,
    PVCameraStateChangeFlir,       
    PVCameraStateChangeNormal,
    PVCameraStateFlirCalSuccess,   
    PVCameraStateFlirCalFail
};

@class PVCamera;
@protocol PVCameraDelegate <NSObject>

@optional

/**
 Return to this method when the camera's state changes

 @param camera camera
 @param cameraState camera state
 */
- (void)camera:(PVCamera *_Nonnull)camera didUpdateCameraState:(PVCameraState)cameraState;

/**
 Return to this method when the state of SDCard changes

 @param camera      camera
 @param sdCardState  SDCard state
 */
- (void)camera:(PVCamera *_Nonnull)camera didUpdateSDCardState:(PVCameraSDCardState *_Nonnull)sdCardState;

@end

@interface PVCamera : PVBaseComponent

@property (nonatomic,weak) id <PVCameraDelegate>delegate;

/**
 Configure camera Manager
 */
- (void)configCameraManager;

/**
 Set the camera mode

 @param mode camera mode
 */
- (void)setCameraMode:(PVCameraMode)mode;

/**
 Get the camera mode

 @param block CallBack results
 */
- (void)getCameraModeWithCompletion:(void (^_Nonnull)(PVCameraMode cameraMode))block;

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
- (void)resetToCameraFactoryWithCompletion:(PVCompletionBlock)block;

/**
 Get the camera current mode

 @param block CallBack Results
 */
- (void)getCameraCurrentState:(void (^_Nonnull)(PVCameraState camerastate, NSError *_Nullable error))block;

/**
 Get the capacity of camera SD card

 @param block CallBack Results
 */
- (void)getEyeSDRemainingCapacityWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

/**
 Get the capacity of camera SD card(unsolicited)
 
 @param block Callback results
 */
- (void)getEyeSDRemainingCapacityNORequestWithComplection:(void (^_Nonnull)(NSInteger remainingCapacity, NSError *_Nullable error))block;

/**
 Set the Video Size of PowerEye

 @param videoSize Video Size
 @param block Callback results
 */
- (void)setEyeCameraVideoSize:(PVCameraVideoSize)videoSize withCompletion:(PVCompletionBlock)block;

/**
 Get the Vedio Size of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraVideoSizeWithCompletion:(void (^_Nonnull)(PVCameraVideoSize videoSize, NSError *_Nullable error))block;

/**
 Set the AF recording of PowerEye

 @param videoAF AF Value
 @param block Callback results
 */
- (void)setEyeCameraVideoAF:(PVCameraVideoAF)videoAF withCompletion:(PVCompletionBlock)block;

/**
 Get the AF recording of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraVideoAFWithCompletion:(void (^_Nonnull)(PVCameraVideoAF videoAF, NSError *_Nullable error))block;

/**
 Get the Camera shutter speed of PowerEye

 @param videoShutterSpeed Camera shutter speed
 @param block Callback results
 */
- (void)setEyeCameraVideoShutterSpeed:(PVCameraVideoShutterSpeed)videoShutterSpeed withCompletion:(PVCompletionBlock)block;

/**
 Get the Camera shutter speed of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraVideoShutterSpeedWithCompletion:(void (^_Nonnull)(PVCameraVideoShutterSpeed videoShutterSpeed, NSError *_Nullable error))block;

/**
 Set the photo size of PowerEye

 @param videoCAFLevel  photo size
 @param block          callback results
 */
- (void)setEyeCameraPhotoSize:(PVCameraPhotoSize)photoSize withCompletion:(PVCompletionBlock)block;

/**
 Get the photo size of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraPhotoSizeWithCompletion:(void (^_Nonnull)(PVCameraPhotoSize photoSize, NSError *_Nullable error))block;

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
- (void)setEyeCameraPhotoShutterSpeed:(PVCameraPhotoShutterSpeed)shutterSpeed withCompletion:(PVCompletionBlock)block;

/**
 Get the Photo shutter speed of PowerEye
 
 @param block Callback results
 */
- (void)getEyeCameraPhotoShutterSpeedWithCompletion:(void (^_Nonnull)(PVCameraPhotoShutterSpeed shutterSpeed, NSError *_Nullable error))block;

/**
 Set the Camera aperture size of PowerEye

 @param aperture f-number
 @param block Callback results
 */
- (void)setEyePVCameraAperture:(PVCameraAperture)aperture withCompletion:(PVCompletionBlock)block;

/**
 Get the Camera aperture size of PowerEye
 
 @param block Callback results
 */
- (void)getEyePVCameraApertureWithCompletion:(void (^_Nonnull)(PVCameraAperture aperture, NSError *_Nullable error))block;

/**
 Set the white balance of PowerEye

 @param whiteBalancemode（manual/automatic）
 @param block Callback results
 */
- (void)setEyeWhiteBalanceMode:(PVEyeCameraWhiteBalanceMode)whiteBalanceMode withCompletion:(PVCompletionBlock)block;

/**
 Get the white balance of PowerEye
 
 @param block Callback results
 */
- (void)getEyeWhiteBalanceModeWithCompletion:(void (^_Nonnull)(PVEyeCameraWhiteBalanceMode whiteBalanceMode, NSError *_Nullable error))block;

/**
 Set the exposure compensation of PowerEye

 @param exposure value （-96~96）
 @param block Callback results
 */
- (void)setEyeExposure:(NSInteger)exposure withCompletion:(PVCompletionBlock)block;

/**
 Get the exposure compensation
 
 @param block Callback results
 */
- (void)getEyeExposureWithCompletion:(void (^_Nonnull)(NSInteger exposure, NSError *_Nullable error))block;

/**
 *  Set the white balance parameters of PowerEye camera in manual mode
 *
 *  @param whiteBalancevalue(-100~100)
 *  @param block Callback results
 */
- (void)setEyeWhiteBalance:(NSInteger)whiteBalance withCompletion:(PVCompletionBlock)block;

/**
 Get the white balance parameters of PowerEye camera in manual mode
 
 @param block Callback results
 */
- (void)getEyeWhiteBalanceWithCompletion:(void (^_Nonnull)(NSInteger whiteBalance, NSError *_Nullable error))block;

/**
 Set the camera ISO of PowerEye
 
 @param ISOvalue
 @param block Callback results
 */
- (void)setEyeISO:(PVEyeCameraISO)iso withCompletion:(PVCompletionBlock)block;

/**
 Get the camera ISO of PowerEye
 
 @param block Callback results
 */
- (void)getEyeISOWithCompletion:(void (^_Nonnull)(PVEyeCameraISO iso, NSError *_Nullable error))block;

/**
 Set the Light-metering of PowerEye

 @param meteringMode Light-metering
 @param block Callback results
 */

- (void)setEyeMeteringMode:(PVEyeCameraMeteringMode)meteringMode withCompletion:(PVCompletionBlock)block;

/**
 Get the Light-metering mode of PowerEye
 
 @param block Callback results
 */
- (void)getEyeMeteringModeWithCompletion:(void (^_Nonnull)(PVEyeCameraMeteringMode meteringMode, NSError *_Nullable error))block;

/**
 Set the picture brightness of PowerEye

 @param brightness Brightness value
 @param block Callback results
 */
- (void)setImageBrightness:(NSInteger)brightness withCompletion:(PVCompletionBlock)block;

/**
 Get the picture brightness of PowerEye
 
 @param block Callback results
 */
- (void)getImageBrightnessWithCompletion:(void (^_Nonnull)(NSInteger brightness, NSError *_Nullable error))block;

/**
 Set the PowerEye image sharpness

 @param sharpness Sharpness value
 @param block Callback results
 */
- (void)setImageSharpness:(NSInteger)sharpness withCompletion:(PVCompletionBlock)block;

/**
 Get the PowerEye image sharpness
 
 @param block Callback results
 */
- (void)getImageSharpnessWithCompletion:(void (^_Nonnull)(NSInteger sharpness, NSError *_Nullable error))block;

/**
 Set the camera image Saturation

 @param Saturation Saturation value
 @param block Callback results
 */
- (void)setImageSaturation:(NSInteger)saturation withCompletion:(PVCompletionBlock)block;

/**
 Get the camera image Saturation
 
 @param block Callback results
 */
- (void)getImageSaturationWithCompletion:(void (^_Nonnull)(NSInteger saturation, NSError *_Nullable error))block;

/**
 Set the PowerEye image contrast

 @param brightness Contrast value
 @param block Callback results
 */
- (void)setImageContrast:(NSInteger)contrast withCompletion:(PVCompletionBlock)block;

/**
 Get the PowerEye image contrast
 
 @param block Callback results
 */
- (void)getImageContrastWithCompletion:(void (^_Nonnull)(NSInteger contrast, NSError *_Nullable error))block;

/**
 Set the time-lapse shooting of PowerEye

 @param time Time(1~1799)
 @param block Callback results
 */
- (void)setTakePhotoDelyTime:(NSInteger)time withCompletion:(PVCompletionBlock)block;

/**
 Get the time-lapse shooting of PowerEye
 
 @param block Callback results
 */
- (void)getTakePhotoDelyTimeWithCompletion:(void (^_Nonnull)(NSInteger time, NSError *_Nullable error))block;

/**
 Set the number of PowerEye time-lapse shooting

 @param num Number(2~100)
 @param block Callback results
 */
- (void)setTakePhotoDelyNum:(NSInteger)num withCompletion:(PVCompletionBlock)block;

/**
 Get the number of PowerEye time-lapse shooting
 
 @param block Callback results
 */
- (void)getTakePhotoDelyNumWithCompletion:(void (^_Nonnull)(NSInteger num, NSError *_Nullable error))block;

/**
 Set the superposition switch of PowerEye OSD

 @param open BOOL
 @param block Callback results
 */
- (void)setEyeOSDSwitchOpenState:(PVEyeOSDSwitchState)state WithCompletion:(PVCompletionBlock)block;

/**
 Get the Superposition switch state of PowerEye OSD

 @param block Callback results
 */
- (void)getEyeOSDSwitchOpenStatusWithCompletion:(void (^_Nonnull)(PVEyeOSDSwitchState state, NSError *_Nullable error))block;

/**
 Get all settings of PowerEye

 @param block Callback results
 */
- (void)getAllCameraSettingWithCompletion:(PVCompletionBlock)block;

/**
 Factory reset
 
 @param block Resetting result
 */
- (void)RecoveryfactoryWithComplection:(PVCompletionBlock)block;

@end
