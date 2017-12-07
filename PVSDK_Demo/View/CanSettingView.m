//
//  CanSettingView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/23.
//  Copyright © 2017 Layne. All rights reserved.
//

#import "CanSettingView.h"
#import "LMJDropdownMenu.h"
#import "UIView+Size.h"

@interface CanSettingView ()<LMJDropdownMenuDelegate>
@property (weak, nonatomic) IBOutlet UILabel *modeLabel;
@property (weak, nonatomic) IBOutlet UILabel *bpsLabel;
@property (nonatomic, strong) LMJDropdownMenu *modeBitsMenu;
@property (nonatomic, strong) LMJDropdownMenu *bpsBitsMenu;
@end

@implementation CanSettingView

- (void)awakeFromNib
{
    [super awakeFromNib];
    _modeBitsMenu = [[LMJDropdownMenu alloc] init];
    _modeBitsMenu.delegate = self;
    [_modeBitsMenu setFrame:CGRectMake(0, 0, 110, 21)];
    _modeBitsMenu.left = _modeLabel.right+10;
    _modeBitsMenu.top = _modeLabel.top;
    [_modeBitsMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_modeBitsMenu setMenuTitles:@[@"正常模式",@"静默模式",@"回环模式",@"静默回环模式"] rowHeight:25];
    [self addSubview:_modeBitsMenu];
    
    _bpsBitsMenu = [[LMJDropdownMenu alloc] init];
    _bpsBitsMenu.delegate = self;
    [_bpsBitsMenu setFrame:CGRectMake(0, 0, 110, 21)];
    _bpsBitsMenu.left = _bpsLabel.right+10;
    _bpsBitsMenu.top = _bpsLabel.top;
    [_bpsBitsMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_bpsBitsMenu setMenuTitles:@[@"5K",@"10K",@"20K",@"50K",@"100K",@"125K",@"250K",@"500K",@"800K",@"1000K"] rowHeight:25];
    [self addSubview:_bpsBitsMenu];
}

- (void)dropdownMenu:(LMJDropdownMenu *)menu selectedCellNumber:(NSInteger)number
{
    CanDownMenuType menuType = 0;
    if (menu == _modeBitsMenu) {
        menuType = canDownMenuTypeMode;
    }
    if (menu == _bpsBitsMenu) {
        menuType = canDownMenuTypeBPS;
    }
    if([self.delegate respondsToSelector:@selector(canSettingView:dropMenuType:selectedCellNumber:)]){
        [self.delegate canSettingView:self dropMenuType:menuType selectedCellNumber:number];
    }
    
}

@end
