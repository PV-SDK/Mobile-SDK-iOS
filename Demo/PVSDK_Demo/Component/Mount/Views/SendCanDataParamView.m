//
//  SendCanDataParamView.m
//  PVSDK_Demo
//
//  Copyright © 2017 Layne. All rights reserved.
//

#import "SendCanDataParamView.h"

@implementation SendCanDataParamView

- (void)awakeFromNib
{
    [super awakeFromNib];
    _idTypeTextField.keyboardType = UIKeyboardTypeNumberPad;
    _formatTextField.keyboardType = UIKeyboardTypeNumberPad;
    _idTextField.keyboardType = UIKeyboardTypeNumberPad;
}


@end
