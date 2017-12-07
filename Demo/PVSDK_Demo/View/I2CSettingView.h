//
//  I2CSettingView.h
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/23.
//  Copyright © 2017 Layne. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM (NSUInteger, I2cDownMenuType){
    I2cDownMenuTypeMode,
    I2cDownMenuTypeBPS,
};


@class I2CSettingView;
@protocol I2cSettingViewDelegate <NSObject>

- (void)i2cSettingView:(I2CSettingView *)i2cView dropMenuType:(I2cDownMenuType)type selectedCellNumber:(NSInteger)number;

@end


@interface I2CSettingView : UIView

@property (nonatomic,weak) id<I2cSettingViewDelegate>delegate;

@property (weak, nonatomic) IBOutlet UITextField *deviceAddressTextField;

@end
