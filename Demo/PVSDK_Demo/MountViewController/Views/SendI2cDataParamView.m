//
//  SendI2cDataParamView.m
//  PVSDK_Demo
//
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
