//
//  CameraSettingValueVC.h
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/25.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    CameraSettingParameterType_ISO                  = 0,     //  光圈设置【ISO】
    CameraSettingParameterType_ApertureSize         = 1,     //  光圈设置【光圈大小】
    CameraSettingParameterType_EV                   = 2,     //  光圈设置【EV】
    CameraSettingParameterType_PZShutterSpeed       = 3,     //  光圈设置【拍照快门速度】
    CameraSettingParameterType_SXShutterSpeed       = 4,     //  光圈设置【摄像快门速度】
    CameraSettingParameterType_CameraMode           = 5,     //  图像设置【相机模式】
    CameraSettingParameterType_ContinuousShootSpeed = 6,     //  图像设置【连拍速度】
    CameraSettingParameterType_LapseTime            = 7,     //  图像设置【延时拍照】
    CameraSettingParameterType_PhotoSize            = 8,     //  图像设置【照片大小】
    CameraSettingParameterType_PictureQuality       = 9,     //  图像设置【照片质量】
    CameraSettingParameterType_VideoResolution      = 10,    //  图像设置【视频分辨率】
    CameraSettingParameterType_WhiteBalanceMode     = 11,    //  通用设置【白平衡模式】
    CameraSettingParameterType_WhiteBalanceValue    = 12,    //  通用设置【白平衡】
    CameraSettingParameterType_ImageBrightness      = 13,    //  通用设置【图像亮度】
    CameraSettingParameterType_ImageSaturation      = 14,    //  通用设置【图像饱和度】
    CameraSettingParameterType_ImageContrast        = 15,    //  通用设置【图像对比度】
    CameraSettingParameterType_MeteringMode         = 16,    //  通用设置【测光模式】
    CameraSettingParameterType_AFMode               = 17,    //  通用设置【AF模式】
    CameraSettingParameterType_OSDSwitch            = 18,    //  通用设置【OSD开关】
    CameraSettingParameterType_ImageSharpness       = 19,    //  通用设置【图像锐度】
    CameraSettingParameterType_PhotoRemainNum       = 20,    //  通用设置【剩余拍照张数】
    CameraSettingParameterType_FormatMemoryCard     = 21,    //  通用设置【格式化内存卡】
    CameraSettingParameterType_Reset                = 22     //  通用设置【恢复出厂设置】
} CameraSettingParameterType;

@interface CameraSettingValueVC : UIViewController

@property (nonatomic, assign) CameraSettingParameterType parameterType;

@end
