//
//  UartSettingView.h
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/16.
//  Copyright © 2017 Layne. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM (NSUInteger, UartDownMenuType){
    UartDownMenuTypeBPS,
    UartDownMenuTypeDataBits,
    UartDownMenuTypeStopBits,
    UartDownMenuTypeParityBits,
    UartDownMenuTypeFlowCtrl,
};


@class UartSettingView;
@protocol UartSettingViewDelegate <NSObject>

- (void)uartSettingView:(UartSettingView *)uartView dropMenuType:(UartDownMenuType)type selectedCellNumber:(NSInteger)number;

@end

@interface UartSettingView : UIView

@property (nonatomic,weak)id <UartSettingViewDelegate>delegate;

@end
