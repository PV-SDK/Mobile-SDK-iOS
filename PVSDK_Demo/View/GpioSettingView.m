//
//  GpioSettingView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/27.
//  Copyright © 2017年 Layne. All rights reserved.
//

#import "GpioSettingView.h"

@interface GpioSettingView ()
@property (weak, nonatomic) IBOutlet UILabel *detailLabel;
@end

@implementation GpioSettingView

- (void)awakeFromNib
{
    [super awakeFromNib];
    _detailLabel.text = @"(1)设备编号 0:gpio1 1:gpio2 2:gpio3\n(2)一个周期内低电平持续时间, 取值范围(0~0xffff)\n(3)一个周期内高电平持续时间,取值范围(0~0xffff)";
}

@end
