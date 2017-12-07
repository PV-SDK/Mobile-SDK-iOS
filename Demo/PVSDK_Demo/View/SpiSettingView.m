//
//  SpiSettingView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/23.
//  Copyright © 2017 Layne. All rights reserved.
//

#import "SpiSettingView.h"
#import "LMJDropdownMenu.h"
#import "UIView+Size.h"

@interface SpiSettingView ()<LMJDropdownMenuDelegate>
@property (weak, nonatomic) IBOutlet UILabel *modeLabel;
@property (weak, nonatomic) IBOutlet UILabel *bpsLabel;
@property (weak, nonatomic) IBOutlet UILabel *firstBitLabel;
@property (weak, nonatomic) IBOutlet UILabel *dataSizeLabel;
@property (weak, nonatomic) IBOutlet UILabel *crcEnableLabel;

@property (nonatomic, strong) LMJDropdownMenu *modeMenu;
@property (nonatomic, strong) LMJDropdownMenu *bpsBitsMenu;
@property (nonatomic, strong) LMJDropdownMenu *firstBitMenu;
@property (nonatomic, strong) LMJDropdownMenu *dataSizeMenu;
@property (nonatomic, strong) LMJDropdownMenu *crcEnableMenu;

@end

@implementation SpiSettingView

- (void)awakeFromNib
{
    [super awakeFromNib];
    _modeMenu = [[LMJDropdownMenu alloc] init];
    _modeMenu.delegate = self;
    [_modeMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _modeMenu.left = _modeLabel.right;
    _modeMenu.top = _modeLabel.top;
    [_modeMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_modeMenu setMenuTitles:@[@"主模式",@"从模式"] rowHeight:25];
    [self addSubview:_modeMenu];
    
    _bpsBitsMenu = [[LMJDropdownMenu alloc] init];
    _bpsBitsMenu.delegate = self;
    [_bpsBitsMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _bpsBitsMenu.left = _bpsLabel.right+10;
    _bpsBitsMenu.top = _bpsLabel.top;
    [_bpsBitsMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_bpsBitsMenu setMenuTitles:@[@"1Mbps",@"2Mbps",@"4Mbps",@"8Mbps",@"16Mbps"] rowHeight:25];
    [self addSubview:_bpsBitsMenu];
    
    _firstBitMenu = [[LMJDropdownMenu alloc] init];
    _firstBitMenu.delegate = self;
    [_firstBitMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _firstBitMenu.left = _firstBitLabel.right+10;
    _firstBitMenu.top = _firstBitLabel.top;
    [_firstBitMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_firstBitMenu setMenuTitles:@[@"MSB",@"LSB"] rowHeight:25];
    [self addSubview:_firstBitMenu];
    
    _dataSizeMenu = [[LMJDropdownMenu alloc] init];
    _dataSizeMenu.delegate = self;
    [_dataSizeMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _dataSizeMenu.left = _dataSizeLabel.right+10;
    _dataSizeMenu.top = _dataSizeLabel.top;
    [_dataSizeMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_dataSizeMenu setMenuTitles:@[@"8位",@"16位"] rowHeight:25];
    [self addSubview:_dataSizeMenu];
    
    _crcEnableMenu = [[LMJDropdownMenu alloc] init];
    _crcEnableMenu.delegate = self;
    [_crcEnableMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _crcEnableMenu.left = _crcEnableLabel.right+10;
    _crcEnableMenu.top = _crcEnableLabel.top;
    [_crcEnableMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_crcEnableMenu setMenuTitles:@[@"不使能",@"使能"] rowHeight:25];
    [self addSubview:_crcEnableMenu];

}

- (void)dropdownMenu:(LMJDropdownMenu *)menu selectedCellNumber:(NSInteger)number
{
    SpiDownMenuType menuType = 0;
    if (menu == _modeMenu) {
        menuType = SpiDownMenuTypeMode;
    }
    if (menu == _bpsBitsMenu) {
        menuType = SpiDownMenuTypeBPS;
    }
    if (menu == _firstBitMenu) {
        menuType = SpiDownMenuTypeFirstBit;
    }
    if (menu == _dataSizeMenu) {
        menuType = SpiDownMenuTypeDataSize;
    }
    if (menu == _crcEnableMenu) {
        menuType = SpiDownMenuTypeCrcEnable;
    }

    if([self.delegate respondsToSelector:@selector(spiSettingView:dropMenuType:selectedCellNumber:)]){
        [self.delegate spiSettingView:self dropMenuType:menuType selectedCellNumber:number];
    }
}

@end
