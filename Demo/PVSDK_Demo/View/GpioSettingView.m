//
//  GpioSettingView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/27.
//  Copyright © 2017 Layne. All rights reserved.
//

#import "GpioSettingView.h"

@interface GpioSettingView ()
@property (weak, nonatomic) IBOutlet UILabel *detailLabel;
@end

@implementation GpioSettingView

- (void)awakeFromNib
{
    [super awakeFromNib];
    _detailLabel.text = @"(1)设备编号 0:gpio1 1:gpio2 2:gpio3\n(2)一个周期内低电平持续时间, 取值范围(0~0xffff)\n(3)一个周期内高电平持续时间,取值范围(0~0xffff)\n(4)周期值分辨率,取值范围(0~0xffff),单位 1/64us";
}

@end
