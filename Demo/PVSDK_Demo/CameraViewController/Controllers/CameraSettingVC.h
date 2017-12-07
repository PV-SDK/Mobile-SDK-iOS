//
//  CameraSettingVC.h
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/25.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    CameraSettingShootStateTakePhoto  = 0,
    CameraSettingShootStateRecord     = 1
} CameraSettingShootState;

@interface CameraSettingVC : UIViewController

@property (nonatomic, assign) CameraSettingShootState shootState;

@end
