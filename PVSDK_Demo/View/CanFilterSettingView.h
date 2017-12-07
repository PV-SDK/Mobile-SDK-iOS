//
//  CanFilterSettingView.h
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/26.
//  Copyright © 2017 Layne. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CanFilterSettingView : UIView

@property (weak, nonatomic) IBOutlet UITextField *filterNumText;
@property (weak, nonatomic) IBOutlet UITextField *filterModeText;
@property (weak, nonatomic) IBOutlet UITextField *matchIdText;
@property (weak, nonatomic) IBOutlet UITextField *maskIdText;
@property (weak, nonatomic) IBOutlet UITextField *idTypeText;
@property (weak, nonatomic) IBOutlet UITextField *formatText;
@property (weak, nonatomic) IBOutlet UITextField *enableText;

@end
