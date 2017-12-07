//
//  I2CSettingView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/23.
//  Copyright © 2017 Layne. All rights reserved.
//

#import "I2CSettingView.h"
#import "LMJDropdownMenu.h"
#import "UIView+Size.h"

@interface I2CSettingView ()<LMJDropdownMenuDelegate>
@property (weak, nonatomic) IBOutlet UILabel *modeLabel;
@property (weak, nonatomic) IBOutlet UILabel *bpsLabel;
@property (weak, nonatomic) IBOutlet UILabel *deviceAddrLabel;
@property (nonatomic, strong) LMJDropdownMenu *modeMenu;
@property (nonatomic, strong) LMJDropdownMenu *bpsMenu;
@end

@implementation I2CSettingView

- (void)awakeFromNib
{
    [super awakeFromNib];
    [super awakeFromNib];
    _modeMenu = [[LMJDropdownMenu alloc] init];
    _modeMenu.delegate = self;
    [_modeMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _modeMenu.left = _modeLabel.right;
    _modeMenu.top = _modeLabel.top;
    [_modeMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_modeMenu setMenuTitles:@[@"主模式",@"从模式"] rowHeight:25];
    [self addSubview:_modeMenu];
    
    _bpsMenu = [[LMJDropdownMenu alloc] init];
    _bpsMenu.delegate = self;
    [_bpsMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _bpsMenu.left = _bpsLabel.right;
    _bpsMenu.top = _bpsLabel.top;
    [_bpsMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_bpsMenu setMenuTitles:@[@"100kbps",@"400kbps"] rowHeight:25];
    [self addSubview:_bpsMenu];

}

- (void)dropdownMenu:(LMJDropdownMenu *)menu selectedCellNumber:(NSInteger)number
{
    I2cDownMenuType menuType = 0;
    if (menu == _modeMenu) {
        menuType = I2cDownMenuTypeMode;
    }
    if (menu == _bpsMenu) {
        menuType = I2cDownMenuTypeBPS;
    }
    if([self.delegate respondsToSelector:@selector(i2cSettingView:dropMenuType:selectedCellNumber:)]){
        [self.delegate i2cSettingView:self dropMenuType:menuType selectedCellNumber:number];
    }
}



@end
