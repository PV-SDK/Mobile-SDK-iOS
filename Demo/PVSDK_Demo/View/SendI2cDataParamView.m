//
//  SendI2cDataParamView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/26.
//  Copyright © 2017 Layne. All rights reserved.
//

#import "SendI2cDataParamView.h"

@implementation SendI2cDataParamView

- (void)awakeFromNib
{
    [super awakeFromNib];
    _ramAddressTextField.keyboardType = UIKeyboardTypeNumberPad;
    _addrTypeTextField.keyboardType = UIKeyboardTypeNumberPad;
}

@end
