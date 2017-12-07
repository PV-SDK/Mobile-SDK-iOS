//
//  CanFilterSettingView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/26.
//  Copyright © 2017 Layne. All rights reserved.
//

#import "CanFilterSettingView.h"

@interface CanFilterSettingView ()

@property (weak, nonatomic) IBOutlet UILabel *filterNumLabel;
@property (weak, nonatomic) IBOutlet UILabel *filterModeLabel;
@property (weak, nonatomic) IBOutlet UILabel *matchIdLabel;
@property (weak, nonatomic) IBOutlet UILabel *maskIdLabel;
@property (weak, nonatomic) IBOutlet UILabel *idTypeLabel;
@property (weak, nonatomic) IBOutlet UILabel *formatLabel;
@property (weak, nonatomic) IBOutlet UILabel *enableLabel;

@end

@implementation CanFilterSettingView

- (void)awakeFromNib
{
    [super awakeFromNib];
    
}

@end
