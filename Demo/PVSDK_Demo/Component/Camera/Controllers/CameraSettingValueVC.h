//
//  CameraSettingValueVC.h
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    CameraSettingParameterType_ISO                  = 0,     
    CameraSettingParameterType_ApertureSize         = 1,     
    CameraSettingParameterType_EV                   = 2,     
    CameraSettingParameterType_PZShutterSpeed       = 3,     
    CameraSettingParameterType_SXShutterSpeed       = 4,     
    CameraSettingParameterType_CameraMode           = 5,     
    CameraSettingParameterType_ContinuousShootSpeed = 6,     
    CameraSettingParameterType_LapseTime            = 7,     
    CameraSettingParameterType_PhotoSize            = 8,     
    CameraSettingParameterType_PictureQuality       = 9,     
    CameraSettingParameterType_VideoResolution      = 10,    
    CameraSettingParameterType_WhiteBalanceMode     = 11,    
    CameraSettingParameterType_WhiteBalanceValue    = 12,    
    CameraSettingParameterType_ImageBrightness      = 13,    
    CameraSettingParameterType_ImageSaturation      = 14,    
    CameraSettingParameterType_ImageContrast        = 15,    
    CameraSettingParameterType_MeteringMode         = 16,    
    CameraSettingParameterType_AFMode               = 17,    
    CameraSettingParameterType_OSDSwitch            = 18,    
    CameraSettingParameterType_ImageSharpness       = 19,    
    CameraSettingParameterType_PhotoRemainNum       = 20,    
    CameraSettingParameterType_FormatMemoryCard     = 21,    
    CameraSettingParameterType_Reset                = 22     
} CameraSettingParameterType;

@interface CameraSettingValueVC : UIViewController

@property (nonatomic, assign) CameraSettingParameterType parameterType;

@end
