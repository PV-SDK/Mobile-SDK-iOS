//
//  SendCanDataParamView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/26.
//  Copyright © 2017年 Layne. All rights reserved.
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
