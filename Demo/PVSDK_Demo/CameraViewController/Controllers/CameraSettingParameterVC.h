//
//  CameraSettingParameterVC.h
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/25.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    CameraSettingTypeAperture   = 0,
    CameraSettingTypeShoot      = 1,
    CameraSettingTypeGeneral    = 2
} CameraSettingType;

typedef enum : NSUInteger {
    CameraSetting_CameraStateTakePhoto  = 0,
    CameraSetting_CameraStateRecord     = 1 
} CameraSetting_CameraState;

@interface CameraSettingParameterVC : UIViewController

- (void)configWithType:(CameraSettingType)type State:(CameraSetting_CameraState)state;

@end
