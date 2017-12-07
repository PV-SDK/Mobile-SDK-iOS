//
//  CameraSettingVC.h
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/25.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    CameraSettingShootState_TakePhoto  = 0,    //  拍照模式
    CameraSettingShootState_Record     = 1     //  录像模式
} CameraSettingShootState_;

@interface CameraSettingVC : UIViewController

@property (nonatomic, assign) CameraSettingShootState_ shootState;

@end
