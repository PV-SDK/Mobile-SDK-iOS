//
//  SpiSettingView.h
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/23.
//  Copyright © 2017 Layne. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM (NSUInteger, SpiDownMenuType){
    SpiDownMenuTypeMode,
    SpiDownMenuTypeBPS,
    SpiDownMenuTypeFirstBit,
    SpiDownMenuTypeDataSize,
    SpiDownMenuTypeCrcEnable,
};


@class SpiSettingView;
@protocol SpiSettingViewDelegate <NSObject>

- (void)spiSettingView:(SpiSettingView *)spiView dropMenuType:(SpiDownMenuType)type selectedCellNumber:(NSInteger)number;

@end


@interface SpiSettingView : UIView

@property (nonatomic,weak)id <SpiSettingViewDelegate>delegate;

@end
