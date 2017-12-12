//
//  GpioSettingView.h
//  PVSDK_Demo
//
//  Copyright © 2017 Layne. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GpioSettingView : UIView

@property (weak, nonatomic) IBOutlet UITextField *deviceNumText;
@property (weak, nonatomic) IBOutlet UITextField *periodLowText;
@property (weak, nonatomic) IBOutlet UITextField *periodHighText;
@property (weak, nonatomic) IBOutlet UITextField *periodRatioTextField;

@end
