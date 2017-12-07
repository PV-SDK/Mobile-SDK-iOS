//
//  UartSettingView.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/16.
//  Copyright © 2017 Layne. All rights reserved.
//

#import "UartSettingView.h"
#import "LMJDropdownMenu.h"
#import "UIView+Size.h"

@interface UartSettingView ()<LMJDropdownMenuDelegate>

@property (weak, nonatomic) IBOutlet UILabel *bpsLabel;
@property (weak, nonatomic) IBOutlet UILabel *dataBitsLabel;
@property (weak, nonatomic) IBOutlet UILabel *stopBitsLabel;
@property (weak, nonatomic) IBOutlet UILabel *parityLabel;
@property (weak, nonatomic) IBOutlet UILabel *flowCtrlLabel;
@property (nonatomic, strong) LMJDropdownMenu *bpsMenu;
@property (nonatomic, strong) LMJDropdownMenu *dataBitsMenu;
@property (nonatomic, strong) LMJDropdownMenu *stopBitsMenu;
@property (nonatomic, strong) LMJDropdownMenu *parityMenu;
@property (nonatomic, strong) LMJDropdownMenu *flowCtrlMenu;
@property (nonatomic, strong) UIButton *setButton;

@end

@implementation UartSettingView

- (void)awakeFromNib
{
    [super awakeFromNib];
    _bpsMenu = [[LMJDropdownMenu alloc] init];
    _bpsMenu.delegate = self;
    [_bpsMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _bpsMenu.left = _bpsLabel.right+10;
    _bpsMenu.top = _bpsLabel.top;
    [_bpsMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_bpsMenu setMenuTitles:@[@"9600",@"14400",@"19200",@"38400",@"57600",@"115200"] rowHeight:25];
    [self addSubview:_bpsMenu];
    
    _dataBitsMenu = [[LMJDropdownMenu alloc] init];
    _dataBitsMenu.delegate = self;
    [_dataBitsMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _dataBitsMenu.left = _dataBitsLabel.right+10;
    _dataBitsMenu.top = _dataBitsLabel.top;
    [_dataBitsMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_dataBitsMenu setMenuTitles:@[@"8位",@"9位"] rowHeight:25];
    [self addSubview:_dataBitsMenu];
    
    _stopBitsMenu = [[LMJDropdownMenu alloc] init];
    _stopBitsMenu.delegate = self;
    [_stopBitsMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _stopBitsMenu.left = _stopBitsLabel.right+10;
    _stopBitsMenu.top = _stopBitsLabel.top;
    [_stopBitsMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_stopBitsMenu setMenuTitles:@[@"1位",@"2位"] rowHeight:25];
    [self addSubview:_stopBitsMenu];
    
    _parityMenu = [[LMJDropdownMenu alloc] init];
    _parityMenu.delegate = self;
    [_parityMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _parityMenu.left = _parityLabel.right+10;
    _parityMenu.top = _parityLabel.top;
    [_parityMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_parityMenu setMenuTitles:@[@"无校验",@"奇校验",@"偶校验"] rowHeight:25];
    [self addSubview:_parityMenu];

    
    _flowCtrlMenu = [[LMJDropdownMenu alloc] init];
    _flowCtrlMenu.delegate = self;
    [_flowCtrlMenu setFrame:CGRectMake(0, 0, 80, 21)];
    _flowCtrlMenu.left = _flowCtrlLabel.right+10;
    _flowCtrlMenu.top = _flowCtrlLabel.top;
    [_flowCtrlMenu.mainBtn setTitle:@"请选择" forState:UIControlStateNormal];
    [_flowCtrlMenu setMenuTitles:@[@"无流控",@"RTS有效",@":CTS有效",@"RTS和CTS同时有效"] rowHeight:25];
    [self addSubview:_flowCtrlMenu];
}

- (void)dropdownMenu:(LMJDropdownMenu *)menu selectedCellNumber:(NSInteger)number
{
    UartDownMenuType menuType = 0;
    if (menu == _bpsMenu) {
        menuType = UartDownMenuTypeBPS;
    }
    if (menu == _dataBitsMenu) {
        menuType = UartDownMenuTypeDataBits;
    }
    if (menu == _stopBitsMenu) {
        menuType = UartDownMenuTypeStopBits;
    }
    if (menu == _parityMenu) {
        menuType = UartDownMenuTypeParityBits;
    }
    if (menu == _flowCtrlMenu) {
        menuType = UartDownMenuTypeFlowCtrl;
    }
    if([self.delegate respondsToSelector:@selector(uartSettingView:dropMenuType:selectedCellNumber:)]){
        [self.delegate uartSettingView:self dropMenuType:menuType selectedCellNumber:number];
    }
}


@end
