//
//  MBProgressHUD+DetailLabelAlignment.m
//  PVSDK
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "MBProgressHUD+DetailLabelAlignment.h"

@implementation MBProgressHUD (DetailLabelAlignment)

- (void)setDetailLabelAlignment:(NSTextAlignment)alignment
{
    self->detailsLabel.textAlignment = alignment;
}

@end
