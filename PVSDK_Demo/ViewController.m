//
//  ViewController.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/12.
//  Copyright © 2017年 Layne. All rights reserved.
//


//-------------------PVSDK 导入后需要导入libc++.tbd库---------------------

#import "ViewController.h"
#import "LMJDropdownMenu.h"
#import <Masonry/Masonry.h>
#import <PVSDK/PVSDK.h>
#import "UartSettingView.h"
#import "CanSettingView.h"
#import "I2CSettingView.h"
#import "SpiSettingView.h"

#define ScreenWidth [UIScreen mainScreen].bounds.size.width
#define NUM @"0123456789"
#define ALPHA @"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define ALPHANUM @"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

@interface ViewController ()<LMJDropdownMenuDelegate,PVFlightControllerDelegate,PVMountControllerDelegate,UITextViewDelegate,UartSettingViewDelegate,CanSettingViewDelegate,SpiSettingViewDelegate,I2cSettingViewDelegate>
@property (weak, nonatomic) IBOutlet UILabel *connectStatusLabel;
@property (weak, nonatomic) IBOutlet UIButton *disconnectButton;
@property (weak, nonatomic) IBOutlet UITextView *reciveDataTextView;
@property (weak, nonatomic) IBOutlet UITextView *sendDataTextView;
@property (nonatomic,strong)UartSettingView *uartSettingView;
@property (nonatomic,strong)CanSettingView *canSettingView;
@property (nonatomic,strong)I2CSettingView *i2cSettingView;
@property (nonatomic,strong)SpiSettingView *spiSettingView;
@property (nonatomic,strong)PVFlightController *flightController;//飞行控制类
@property (nonatomic,strong)PVMountController *mountController;//挂载控制类
@property (nonatomic,assign)PVMountPortType portType;//挂载端口类型
@property (weak, nonatomic) IBOutlet UIView *settingView;//设置面板
@property (assign, nonatomic) PVSDK_MOUNTAPI_UART_PARAM uartParam;
@property (assign, nonatomic) PVSDK_MOUNTAPI_CAN_PARAM canParam;
@property (assign, nonatomic) PVSDK_MOUNTAPI_I2C_PARAM i2cParam;
@property (assign, nonatomic) PVSDK_MOUNTAPI_SPI_PARAM spiParam;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [self setupUI];
    [self mountController];
}

#pragma mark -- 懒加载

- (PVFlightController *)flightController
{
    if (_flightController==nil) {
        _flightController = [[PVFlightController alloc] init];
        _flightController.delegate = self;
    }
    return _flightController;
}

- (PVMountController *)mountController
{
    if (_mountController == nil) {
        _mountController = [[PVMountController alloc] init];
        _mountController.delegate = self;
    }
    return _mountController;
}

- (UartSettingView *)uartSettingView
{
    if (_uartSettingView == nil) {
        _uartSettingView = [[[NSBundle mainBundle] loadNibNamed:@"UartSettingView" owner:self options:nil] firstObject];
        _uartSettingView.delegate = self;
        [self.view addSubview:_uartSettingView];
        [_settingView addSubview:_uartSettingView];
        [_uartSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_settingView);
        }];
    }
    return _uartSettingView;
}

- (CanSettingView *)canSettingView
{
    if (_canSettingView == nil) {
        _canSettingView = [[[NSBundle mainBundle] loadNibNamed:@"CanSettingView" owner:self options:nil] firstObject];
        [self.view addSubview:_canSettingView];
        [_settingView addSubview:_canSettingView];
        [_canSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_settingView);
        }];
    }
    return _canSettingView;
}

- (I2CSettingView *)i2cSettingView
{
    if (!_i2cSettingView) {
        _i2cSettingView = [[[NSBundle mainBundle] loadNibNamed:@"I2CSettingView" owner:self options:nil] firstObject];
        [self.view addSubview:_i2cSettingView];
        [_settingView addSubview:_i2cSettingView];
        [_i2cSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_settingView);
        }];
    }
    return _i2cSettingView;
}

- (SpiSettingView *)spiSettingView
{
    if (!_spiSettingView) {
        _spiSettingView = [[[NSBundle mainBundle] loadNibNamed:@"SpiSettingView" owner:self options:nil] firstObject];
        [self.view addSubview:_spiSettingView];
        [_settingView addSubview:_spiSettingView];
        [_spiSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_settingView);
        }];
    }
    return _spiSettingView;
}


- (void)setupUI
{
    LMJDropdownMenu * dropdownMenu = [[LMJDropdownMenu alloc] init];
    [dropdownMenu setFrame:CGRectMake(ScreenWidth-158, 8, 150, 40)];
    [dropdownMenu setMenuTitles:@[@"UART",@"CAN",@"I2C",@"SPI",@"GPIO"] rowHeight:36];
    dropdownMenu.delegate = self;
    [self.view addSubview:dropdownMenu];
    self.sendDataTextView.delegate = (id)self;
    [_disconnectButton setHidden:YES];
}

- (void)setConnectStatus:(PVFlightConnectState)state
{
    if (state == PVFlightConnectStateConnected) {
        _connectStatusLabel.text = @"已连接";
        _connectStatusLabel.textColor = [UIColor colorWithRed:0/255.0 green:128/255.0 blue:0/255.0 alpha:1];
    } else {
        _connectStatusLabel.text = @"未连接";
        _connectStatusLabel.textColor = [UIColor grayColor];
    }
}

//连接设备
- (IBAction)connectToDeviceTouch:(UIButton *)sender {
    [self.flightController startConnectFlightBlockWithSuccess:nil failure:nil];//连接设备
}

//断开设备
- (IBAction)disconnectToDeviceTouch:(UIButton *)sender {
    
}

//读取数据
- (IBAction)readButtonTouch:(UIButton *)sender {
    if (_portType == PVMountPortTypeSPI) {
        PVSDK_MOUNTAPI_READSPI_DATA spiConfig;
        spiConfig.dataNumber = 16;
        spiConfig.ramAddr = 2;
        [_mountController readSpiData:spiConfig WithReadDataBlock:^(PVSDK_MOUNTAPI_SPI_RETURN_DATA data) {
            _reciveDataTextView.text = [NSString stringWithFormat:@"%s",data.data];
        }];
    }
    if (_portType == PVMountPortTypeI2C) {
        PVSDK_MOUNTAPI_READI2C_DATA i2cConfig;
        i2cConfig.addrType = 2;
        i2cConfig.dataNumber = 16;
        i2cConfig.ramAddr = 2;
       [_mountController readI2cData:i2cConfig WithReadDataBlock:^(PVSDK_MOUNTAPI_I2C_RETURN_DATA data) {
           _reciveDataTextView.text = [NSString stringWithFormat:@"%s",data.data];
       }];
    }
}

//发送数据
- (IBAction)sendButtonTouch:(UIButton *)sender {
    
    if (self.flightController.flightConnectState!=PVFlightConnectStateConnected) {
        [self showTipsAlert];
        return;
    }
    
    NSString *dataStr = _sendDataTextView.text;
    if (_portType == PVMountPortTypeUART) {
        PVSDK_MOUNTAPI_UART_DATA uartData;
        memcpy(uartData.data, [dataStr UTF8String], dataStr.length);
        uartData.encryption = 0;
        uartData.len = (int)dataStr.length;
        [_mountController sendUartData:uartData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            NSLog(@"Uart数据发送完成");
        }];
    }
    if (_portType == PVMountPortTypeCAN) {
        PVSDK_MOUNTAPI_CAN_DATA canData;
        memcpy(canData.data, [dataStr UTF8String], dataStr.length);
        canData.encryption = 0;
        canData.format = 0;
        canData.id = 10;
        canData.len = (int)dataStr.length;
        canData.type = 0;
        [_mountController sendCanData:canData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            NSLog(@"Can数据发送完成");
        }];
    }
    if (_portType == PVMountPortTypeI2C) {
        PVSDK_MOUNTAPI_I2C_DATA i2cData;
        i2cData.addrType = 0;
        memcpy(i2cData.data, [dataStr UTF8String], dataStr.length);
        i2cData.encryption = 0;
        i2cData.len = (int)dataStr.length;
        i2cData.ramAddr = 10;
        [_mountController sendI2cData:i2cData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            NSLog(@"Can数据发送完成");
        }];
    }
    if (_portType == PVMountPortTypeSPI) {
        PVSDK_MOUNTAPI_SPI_DATA spiData;
        memcpy(spiData.data, [dataStr UTF8String], dataStr.length);
        [_mountController sendSpiData:spiData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            NSLog(@"SPI---------state:%d    error:%d",returnInfo.state,returnInfo.error);
        }];
    }
    
}

- (void)showTipsAlert
{
    [[[UIAlertView alloc] initWithTitle:@"提示"
                                message:@"请先连接设备"
                               delegate:self
                            cancelButtonTitle:nil
                            otherButtonTitles:@"OK", nil] show];
}

//参数查询按钮点击事件
- (IBAction)readParamButtonClick:(UIButton *)sender {
    if (_portType == PVMountPortTypeUART) {
        [_mountController queryUartParamWithBlock:^(PVSDK_MOUNTAPI_UART_PARAM param) {
            
        }];
    }
    if (_portType == PVMountPortTypeCAN) {
        [_mountController queryCanParamWithBlock:^(PVSDK_MOUNTAPI_CAN_PARAM param) {
            
        }];
    }
    if (_portType == PVMountPortTypeSPI) {
        [_mountController querySpiParamWithBlock:^(PVSDK_MOUNTAPI_SPI_PARAM param) {
            
        }];
    }
    if (_portType == PVMountPortTypeI2C) {
        [_mountController queryI2cParamWithBlock:^(PVSDK_MOUNTAPI_I2C_PARAM param) {
            
        }];
    }
    if (_portType == PVMountPortTypeGPIO) {
        
    }

    
}

//参数设置按钮点击事件
- (IBAction)setParamButtonClick:(UIButton *)sender {
    
    if (self.flightController.flightConnectState!=PVFlightConnectStateConnected) {
        [self showTipsAlert];
        return;
    }
    if (_portType == PVMountPortTypeUART) {
        [self.mountController setUartParam:_uartParam withSetResultBlock:^(PVSDK_MOUNTAPI_SET_PARAM param) {
            NSLog(@"设置状态：%d",param.state);
        }];
    }
    
    
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    NSCharacterSet *cs = [[NSCharacterSet characterSetWithCharactersInString:ALPHANUM] invertedSet];
    NSString *filtered = [[text componentsSeparatedByCharactersInSet:cs] componentsJoinedByString:@""];
    return [text isEqualToString:filtered];

}

#pragma mark - PVSDK Delegate(飞行器相关代理)
- (void)flightController:(PVFlightController *)fc didUpdateFlightState:(PVFlightControllerState *)state stateType:(PVStateUpdate)stateUpdate
{
    switch (stateUpdate) {
        case PVFlightConnectStateUpdate:
            [self setConnectStatus:state.flightConnectState];
            break;
            
        default:
            break;
    }
}

#pragma mark - PVSDK Delegate(挂载相关代理)
- (void)mounthController:(PVMountController *)mc reciveCanData:(PVSDK_MOUNTAPI_CAN_DATA)mData
{
    if (_portType == PVMountPortTypeCAN) {
        _reciveDataTextView.text = [NSString stringWithFormat:@"%s",mData.data];
    }
}

- (void)mounthController:(PVMountController *)mc reciveUartData:(PVSDK_MOUNTAPI_UART_DATA)mData
{
    if (_portType == PVMountPortTypeUART) {
        _reciveDataTextView.text = [NSString stringWithFormat:@"%s",mData.data];
    }
}

#pragma mark - LMJDropdownMenu Delegate

- (void)dropdownMenu:(LMJDropdownMenu *)menu selectedCellNumber:(NSInteger)number{
    _portType = (PVMountPortType)(number+1);
    
    if (_portType == PVMountPortTypeUART) {
        [self.settingView bringSubviewToFront:self.uartSettingView];
    }
    if (_portType == PVMountPortTypeCAN) {
        [self.settingView bringSubviewToFront:self.canSettingView];
    }
    if (_portType == PVMountPortTypeI2C) {
        [self.settingView bringSubviewToFront:self.i2cSettingView];
    }
    if (_portType == PVMountPortTypeSPI) {
        [self.settingView bringSubviewToFront:self.spiSettingView];
    }
    if (_portType == PVMountPortTypeGPIO) {
    }
    if (self.flightController.flightConnectState!=PVFlightConnectStateConnected) {
        [self showTipsAlert];
        return;
    }
    [self.mountController loadDevice:_portType WithComplection:^(PVSDK_MOUNTAPI_MOUNTSTATE_DEVICE result) {
        NSLog(@"========loadState:%d  %d  %d  %d  %d",result.uart,result.can,result.i2c,result.spi,result.gpio);
    }];
}

- (void)dropdownMenuWillShow:(LMJDropdownMenu *)menu{
    NSLog(@"--将要显示--");
}
- (void)dropdownMenuDidShow:(LMJDropdownMenu *)menu{
    NSLog(@"--已经显示--");
}

- (void)dropdownMenuWillHidden:(LMJDropdownMenu *)menu{
    NSLog(@"--将要隐藏--");
}
- (void)dropdownMenuDidHidden:(LMJDropdownMenu *)menu{
    NSLog(@"--已经隐藏--");
}

#pragma mark -- UartSettingViewDelegate
- (void)uartSettingView:(UartSettingView *)uartView dropMenuType:(UartDownMenuType)type selectedCellNumber:(NSInteger)number
{
    NSLog(@"type：%lu,number:%ld",(unsigned long)type,(long)number);
    switch (type) {
        case UartDownMenuTypeBPS:
            _uartParam.bps = (int)number;
            break;
            
        case UartDownMenuTypeDataBits:
            _uartParam.dataBits = (int)number;
            break;

        case UartDownMenuTypeStopBits:
            _uartParam.stopBits = (int)number;
            break;

        case UartDownMenuTypeParityBits:
            _uartParam.parity = (int)number;
            break;

        case UartDownMenuTypeFlowCtrl:
            _uartParam.flowCtrl = (int)number;
            break;
            
        default:
            break;
    }
}

#pragma mark -- CanSettingViewDelegate
- (void)canSettingView:(CanSettingView *)canView dropMenuType:(CanDownMenuType)type selectedCellNumber:(NSInteger)number
{
    switch (type) {
        case canDownMenuTypeBPS:
            _canParam.bps = (int)number;
            break;
            
        case canDownMenuTypeMode:
            _canParam.mode = (int)number;
            break;
            
        default:
            break;
    }
}

#pragma mark -- SpiSettingViewDelegate
- (void)spiSettingView:(SpiSettingView *)spiView dropMenuType:(SpiDownMenuType)type selectedCellNumber:(NSInteger)number
{
    switch (type) {
        case SpiDownMenuTypeMode:
            _spiParam.mode = (int)number;
            break;
        case SpiDownMenuTypeBPS:
            _spiParam.bps = (int)number;
            break;
        case SpiDownMenuTypeFirstBit:
            _spiParam.firstBit = (int)number;
            break;
        case SpiDownMenuTypeDataSize:
            _spiParam.dataSize = (int)number;
            break;
        case SpiDownMenuTypeCrcEnable:
            _spiParam.crcEnable = (int)number;
            break;
            
        default:
            break;
    }
}

- (void)i2cSettingView:(I2CSettingView *)i2cView dropMenuType:(I2cDownMenuType)type selectedCellNumber:(NSInteger)number
{
    switch (type) {
        case I2cDownMenuTypeMode:
            _i2cParam.mode = (int)number;
            break;
        case I2cDownMenuTypeBPS:
            _i2cParam.bps = (int)number;
            break;
            
        default:
            break;
    }
    _i2cParam.deviceAddr = [i2cView.deviceAddressTextField.text intValue];
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
