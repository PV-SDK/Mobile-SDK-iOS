//
//  ViewController.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/12.
//  Copyright © 2017 PowerVision. All rights reserved.
//


//-------------------PVSDK 导入后需要导入libc++.tbd库---------------------

#import "MountViewController.h"
#import "LMJDropdownMenu.h"
#import <Masonry/Masonry.h>
#import <PVSDK/PVSDK.h>
#import "UartSettingView.h"
#import "CanSettingView.h"
#import "I2CSettingView.h"
#import "SpiSettingView.h"
#import "SendCanDataParamView.h"
#import "SendI2cDataParamView.h"
#import "CanFilterSettingView.h"
#import "GpioSettingView.h"
#import "ReadSpiDataParamView.h"
#import "ReadI2cDataParamView.h"

#define ScreenWidth [UIScreen mainScreen].bounds.size.width
#define NUM @"0123456789"
#define ALPHA @"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define ALPHANUM @"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"

@interface MountViewController ()
<
LMJDropdownMenuDelegate,
PVFlightControllerDelegate,
PVMountControllerDelegate,
UITextViewDelegate,
UartSettingViewDelegate,
CanSettingViewDelegate,
SpiSettingViewDelegate,
I2cSettingViewDelegate
>
@property (weak, nonatomic) IBOutlet UIButton *readDataButton;
@property (weak, nonatomic) IBOutlet UIButton *sendDataButton;
@property (weak, nonatomic) IBOutlet UITextView *reciveDataTextView;
@property (weak, nonatomic) IBOutlet UITextView *sendDataTextView;
@property (weak, nonatomic) IBOutlet UIView *sendDataParamBackView;

@property (nonatomic,strong) UartSettingView *uartSettingView;
@property (nonatomic,strong) CanSettingView *canSettingView;
@property (nonatomic,strong) I2CSettingView *i2cSettingView;
@property (nonatomic,strong) SpiSettingView *spiSettingView;
@property (nonatomic,strong) CanFilterSettingView *canFilterSettingView;
@property (nonatomic,strong) GpioSettingView *gpioSettingView;
@property (nonatomic,strong) SendCanDataParamView *sendCanDataParamView;
@property (nonatomic,strong) SendI2cDataParamView *sendI2cDataParamView;

@property (weak, nonatomic) IBOutlet UIView *readDataParamBackView;
@property (nonatomic,strong) ReadI2cDataParamView *readI2cDataParamView;
@property (nonatomic,strong) ReadSpiDataParamView *readSpiDataParamView;

@property (nonatomic,strong) PVFlightController *flightController;   //飞行控制类
@property (nonatomic,strong) PVMountController *mountController;     //挂载控制类
@property (nonatomic,assign) PVMountPortType portType;               //挂载端口类型
@property (weak, nonatomic) IBOutlet UIView *settingView;           //设置面板

@property (assign, nonatomic) PVSDK_MOUNTAPI_UART_PARAM uartParam;
@property (assign, nonatomic) PVSDK_MOUNTAPI_CAN_PARAM canParam;
@property (assign, nonatomic) PVSDK_MOUNTAPI_I2C_PARAM i2cParam;
@property (assign, nonatomic) PVSDK_MOUNTAPI_SPI_PARAM spiParam;
@property (assign, nonatomic) PVSDK_MOUNTAPI_CAN_FILTER_PARAM canFilterParam;

@end

@implementation MountViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setupUI];
    [self mountController];
}

#pragma mark - Setup UI
- (void)setupUI
{
    LMJDropdownMenu * dropdownMenu = [[LMJDropdownMenu alloc] initWithFrame:CGRectMake(ScreenWidth-170, 40, 150, 40)];
    [dropdownMenu setMenuTitles:@[@"UART",@"CAN",@"I2C",@"SPI",@"GPIO",@"CAN滤波"] rowHeight:36];
    dropdownMenu.delegate = self;
    [self.view addSubview:dropdownMenu];
    self.sendDataTextView.delegate = (id)self;
    [self.sendDataParamBackView setHidden:YES];
}

#pragma mark - Alert Tips
- (void)showTipsAlertWithContent:(NSString *)content
{
    [[[UIAlertView alloc] initWithTitle:@"提示"
                                message:content
                               delegate:self
                      cancelButtonTitle:nil
                      otherButtonTitles:@"OK", nil] show];
}

//TODO: [Button Method] Empty the receive return data area
- (IBAction)didClickToClearReadSpace:(id)sender
{
    _reciveDataTextView.text = @"";
}

//TODO: [Button Method] Read Command Receive Data
- (IBAction)didClickToReadData:(UIButton *)sender
{
    NSMutableString *dataStr = [NSMutableString string];
    if (_portType == PVMountPortTypeSPI) {
        PVSDK_MOUNTAPI_READSPI_DATA spiConfig;
        spiConfig.dataNumber = [_readSpiDataParamView.dataNumberTextField.text intValue];
        spiConfig.ramAddr = [_readSpiDataParamView.ramAddrTextField.text intValue];
        [_mountController readSpiData:spiConfig WithReadDataBlock:^(PVSDK_MOUNTAPI_SPI_RETURN_DATA data) {
            for (int i = 0; i < data.len; i++) {
                int x = data.data[i];
                [dataStr appendString:[NSString stringWithFormat:@" %02X",x]];
            }
            _reciveDataTextView.text = [NSString stringWithFormat:@"%@",dataStr];
        }];
    }
    if (_portType == PVMountPortTypeI2C) {
        PVSDK_MOUNTAPI_READI2C_DATA i2cConfig;
        i2cConfig.addrType = [_readI2cDataParamView.addrTypeTextField.text intValue];
        i2cConfig.dataNumber = [_readI2cDataParamView.dataNumberTextField.text intValue];
        i2cConfig.ramAddr = [_readI2cDataParamView.ramAddrTextField.text intValue];
        [_mountController readI2cData:i2cConfig WithReadDataBlock:^(PVSDK_MOUNTAPI_I2C_RETURN_DATA data) {
            for (int i = 0; i < data.len; i++) {
                int x = data.data[i];
                [dataStr appendString:[NSString stringWithFormat:@" %02X",x]];
            }
            _reciveDataTextView.text = [NSString stringWithFormat:@"%@",dataStr];
        }];
    }
}

//TODO: [Button Method] Send Command Data
- (IBAction)didClickToSendData:(UIButton *)sender
{
    if (self.flightController.flightConnectState!=PVFlightConnectStateConnected) {
        [self showTipsAlertWithContent:@"设备未连接"];
        return;
    }
    
    NSString *dataStr = _sendDataTextView.text;
    if (_portType == PVMountPortTypeUART) {
        PVSDK_MOUNTAPI_UART_DATA uartData;
        memcpy(uartData.data, [dataStr UTF8String], dataStr.length);
        uartData.encryption = 0;
        uartData.len = (int)dataStr.length;
        [_mountController sendUartData:uartData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            //            NSLog(@"Uart数据发送完成");
            [self showTipsAlertWithContent:@"Uart数据发送完成"];
        }];
    }
    if (_portType == PVMountPortTypeCAN) {
        NSString *idTypeStr = self.sendCanDataParamView.idTypeTextField.text;
        NSString *idStr = self.sendCanDataParamView.idTextField.text;
        NSString *formatStr = self.sendCanDataParamView.formatTextField.text;
        if ([idTypeStr isEqualToString:@""] || [idStr isEqualToString:@""] || [formatStr isEqualToString:@""]) {
            [self showTipsAlertWithContent:@"请完整填写数据请求参数"];
            return ;
        }
        PVSDK_MOUNTAPI_CAN_DATA canData;
        memcpy(canData.data, [dataStr UTF8String], dataStr.length);
        canData.encryption = 0;
        canData.format = [formatStr intValue];
        canData.id = [idStr intValue];
        canData.len = (int)dataStr.length;
        canData.type = [idTypeStr intValue];
        [_mountController sendCanData:canData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            [self showTipsAlertWithContent:@"Can数据发送完成"];
        }];
    }
    if (_portType == PVMountPortTypeI2C) {
        PVSDK_MOUNTAPI_I2C_DATA i2cData;
        i2cData.addrType = 0;
        memcpy(i2cData.data, [dataStr UTF8String], dataStr.length);
        i2cData.encryption = 0;
        i2cData.len = (int)dataStr.length;
        i2cData.ramAddr = 7;
        [_mountController sendI2cData:i2cData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            //            NSLog(@"I2c数据发送完成");
            [self showTipsAlertWithContent:@"I2c数据发送完成"];
        }];
    }
    if (_portType == PVMountPortTypeSPI) {
        PVSDK_MOUNTAPI_SPI_DATA spiData;
        spiData.encryption = 0;
        spiData.len = (int)dataStr.length;
        memcpy(spiData.data, [dataStr UTF8String], dataStr.length);
        [_mountController sendSpiData:spiData withSendResultBlock:^(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo) {
            //            NSLog(@"SPI---------state:%d    error:%d",returnInfo.state,returnInfo.error);
            [self showTipsAlertWithContent:@"Spi数据发送完成"];
        }];
    }
    if (_portType == PVMountPortTypeGPIO) {
        
    }
    
}

//TODO: [Button Method] Parameters of the query
- (IBAction)didClickToReadParam:(UIButton *)sender
{
    
    if (_portType == PVMountPortTypeUART) {
        [_mountController queryUartParamWithBlock:^(PVSDK_MOUNTAPI_UART_PARAM param) {
            [self showTipsAlertWithContent:[NSString stringWithFormat:@"波特率:%d 数据位数:%d 停止位数:%d 校验:%d  流控:%d",param.bps,param.dataBits,param.stopBits,param.parity,param.flowCtrl]];
        }];
    }
    if (_portType == PVMountPortTypeCAN) {
        [_mountController queryCanParamWithBlock:^(PVSDK_MOUNTAPI_CAN_PARAM param) {
            [self showTipsAlertWithContent:[NSString stringWithFormat:@"模式:%d  波特率:%d",param.mode,param.bps]];
        }];
    }
    if (_portType == PVMountPortTypeSPI) {
        [_mountController querySpiParamWithBlock:^(PVSDK_MOUNTAPI_SPI_PARAM param) {
            [self showTipsAlertWithContent:[NSString stringWithFormat:@"模式:%d  速率:%d  有效位先发:%d  数据大小:%d  CRC使能:%d",param.mode,param.bps,param.firstBit,param.dataSize,param.crcEnable]];
        }];
    }
    if (_portType == PVMountPortTypeI2C) {
        [_mountController queryI2cParamWithBlock:^(PVSDK_MOUNTAPI_I2C_PARAM param) {
            [self showTipsAlertWithContent:[NSString stringWithFormat:@"模式:%d  波特率:%d  设备地址:%d",param.mode,param.bps,param.deviceAddr]];
        }];
    }
    if (_portType == PVMountPortTypeGPIO) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"请输入要查询的设备编号" message:@"" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
        [alert setAlertViewStyle:UIAlertViewStylePlainTextInput];
        UITextField *txtName = [alert textFieldAtIndex:0];
        txtName.placeholder = @"设备编号（1，2，3）";
        [alert show];
    }
    if (_portType == 5) {
        [_mountController queryCanFilterParamWithBlock:^(PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM param) {
            NSMutableString *contentStr = [NSMutableString string];
            for (int i = 0; i< param.totalNumber; i++) {
                PVSDK_MOUNTAPI_CAN_FILTER_PARAM filterParam = param.filter[i];
                NSString *content = [NSString stringWithFormat:@"编号:%d 模式:%d 匹配值:%d 掩饰码:%d 类型:%d 格式:%d \n",filterParam.number,filterParam.mode,filterParam.matchId,filterParam.maskId,filterParam.type,filterParam.format];
//                NSLog(@"编号:%d 模式:%d 匹配值:%d 掩饰码:%d 类型:%d 格式:%d",filterParam.number,filterParam.mode,filterParam.matchId,filterParam.maskId,filterParam.type,filterParam.format);
                [contentStr appendString:content];
            }
            [self showTipsAlertWithContent:contentStr];
        }];
    }
    
}

//TODO: [Button Method] Parameter Settings
- (IBAction)didClickToSetParam:(UIButton *)sender
{
    
    if (self.flightController.flightConnectState!=PVFlightConnectStateConnected) {
        [self showTipsAlertWithContent:@"设备未连接"];
        return;
    }
    __weak typeof(self) weakSelf = self;
    if (_portType == PVMountPortTypeUART) {
        [self.mountController setUartParam:_uartParam withSetResultBlock:^(PVSDK_MOUNTAPI_SET_PARAM param) {
            NSLog(@"设置状态：%d",param.state);
            [weakSelf showTipsAlertWithContent:@"Uart参数设置成功"];
        }];
    }
    if (_portType == PVMountPortTypeCAN) {
        [self.mountController setCanParam:_canParam withSetResultBlock:^(PVSDK_MOUNTAPI_SET_PARAM param) {
            NSLog(@"设置状态：%d",param.state);
            [weakSelf showTipsAlertWithContent:@"Can参数设置成功"];
        }];
    }
    if (_portType == PVMountPortTypeI2C) {
        _i2cParam.deviceAddr = [_i2cSettingView.deviceAddressTextField.text intValue];
        [self.mountController setI2cParam:_i2cParam withSetResultBlock:^(PVSDK_MOUNTAPI_SET_PARAM param) {
            NSLog(@"设置状态：%d",param.state);
            [weakSelf showTipsAlertWithContent:@"I2c参数设置成功"];
        }];
    }
    if (_portType == PVMountPortTypeSPI) {
        [self.mountController setSpiParam:_spiParam withSetResultBlock:^(PVSDK_MOUNTAPI_SET_PARAM param) {
            NSLog(@"设置状态：%d",param.state);
            [weakSelf showTipsAlertWithContent:@"Spi参数设置成功"];
        }];
    }
    if (_portType == PVMountPortTypeGPIO) {
        PVSDK_MOUNTAPI_GPIO_PARAM gpioParam;
        gpioParam.deviceNumber = [_gpioSettingView.deviceNumText.text intValue];
        gpioParam.periodHigh = [_gpioSettingView.periodHighText.text intValue];
        gpioParam.periodLow = [_gpioSettingView.periodLowText.text intValue];
        gpioParam.periodRatio = [_gpioSettingView.periodRatioTextField.text intValue];
        [self.mountController setGpioParam:gpioParam withSetResultBlock:^(PVSDK_MOUNTAPI_SET_PARAM param) {
            [weakSelf showTipsAlertWithContent:@"GPIO参数设置成功"];
        }];
    }
    if (_portType == 5){//Can滤波
        _canFilterParam.number = [_canFilterSettingView.filterNumText.text intValue];
        _canFilterParam.mode = [_canFilterSettingView.filterModeText.text intValue];
        _canFilterParam.maskId = [_canFilterSettingView.maskIdText.text intValue];
        _canFilterParam.matchId = [_canFilterSettingView.matchIdText.text intValue];
        _canFilterParam.type = [_canFilterSettingView.idTypeText.text intValue];
        _canFilterParam.format = [_canFilterSettingView.formatText.text intValue];
        _canFilterParam.Enable = [_canFilterSettingView.enableText.text intValue];

        [self.mountController setCanFilterParam:_canFilterParam withSetResultBlock:^(PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM param) {
            [weakSelf showTipsAlertWithContent:@"Can滤波参数设置成功"];
        }];
    }
}

#pragma mark - UITextViewDelegate

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    NSCharacterSet *cs = [[NSCharacterSet characterSetWithCharactersInString:ALPHANUM] invertedSet];
    NSString *filtered = [[text componentsSeparatedByCharactersInSet:cs] componentsJoinedByString:@""];
    return [text isEqualToString:filtered];
    
}

#pragma mark - UIAlertViewDelegate

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (buttonIndex == 1) {
        UITextField *txt = [alertView textFieldAtIndex:0];
        [_mountController queryGpioParamWithGpioNumber:[txt.text intValue] WithBlock:^(PVSDK_MOUNTAPI_GPIO_PARAM param) {
            [self showTipsAlertWithContent:[NSString stringWithFormat:@"设备编号:%d  低电平持续时间:%d  高电平持续时间:%d  周期值分辨率:%d",param.deviceNumber,param.periodLow,param.periodHigh,param.periodRatio]];
        }];
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
- (void)dropdownMenu:(LMJDropdownMenu *)menu selectedCellNumber:(NSInteger)number
{
    _portType = (PVMountPortType)(number);
    
    [self.sendDataParamBackView setHidden:YES];
    [self.readDataParamBackView setHidden:YES];
    [_readDataButton setHidden:NO];//Uart数据不支持主动请求
    
    if (_portType == PVMountPortTypeUART) {
        [self.settingView bringSubviewToFront:self.uartSettingView];
        [_readDataButton setHidden:YES];//Uart数据不支持主动请求
    }
    if (_portType == PVMountPortTypeCAN) {
        [self.settingView bringSubviewToFront:self.canSettingView];
        [self.sendDataParamBackView setHidden:NO];
        [self.sendDataParamBackView bringSubviewToFront:self.sendCanDataParamView];
        [_readDataButton setHidden:YES];//Can数据不支持主动请求
    }
    if (_portType == PVMountPortTypeI2C) {
        [self.settingView bringSubviewToFront:self.i2cSettingView];
        [self.sendDataParamBackView setHidden:NO];
        [self.readDataParamBackView bringSubviewToFront:self.readI2cDataParamView];
        [self.readDataParamBackView setHidden:NO];
    }
    if (_portType == PVMountPortTypeSPI) {
        [self.settingView bringSubviewToFront:self.spiSettingView];
        [self.readDataParamBackView bringSubviewToFront:self.readSpiDataParamView];
        [self.readDataParamBackView setHidden:NO];
    }
    if (_portType == PVMountPortTypeGPIO) {
        [self.settingView bringSubviewToFront:self.gpioSettingView];
    }
    
    if (_portType == 5) {//CAN滤波
        [self.settingView bringSubviewToFront:self.canFilterSettingView];
    }
    
    if (self.flightController.flightConnectState!=PVFlightConnectStateConnected) {
        [self showTipsAlertWithContent:@"设备未连接"];
        return;
    }
    
    PVMountPortType portType = _portType;
    if (portType == 5) {
        portType = PVMountPortTypeCAN;
    }
    [self.mountController loadDevice:_portType WithComplection:^(PVSDK_MOUNTAPI_MOUNTSTATE_DEVICE result) {
        NSLog(@"========loadState:%d  %d  %d  %d  %d  %d  %d",result.uart,result.can,result.i2c,result.spi,result.gpio1,result.gpio2,result.gpio3);
    }];
}
- (void)dropdownMenuWillShow:(LMJDropdownMenu *)menu
{
    //    NSLog(@"--将要显示--");
}
- (void)dropdownMenuDidShow:(LMJDropdownMenu *)menu
{
    //    NSLog(@"--已经显示--");
}
- (void)dropdownMenuWillHidden:(LMJDropdownMenu *)menu
{
    //    NSLog(@"--将要隐藏--");
}
- (void)dropdownMenuDidHidden:(LMJDropdownMenu *)menu
{
    //    NSLog(@"--已经隐藏--");
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

#pragma mark -- 懒加载（Lazying...）

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
        _canSettingView.delegate = self;
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
        _i2cSettingView.delegate = self;
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
        _spiSettingView.delegate = self;
        [self.view addSubview:_spiSettingView];
        [_settingView addSubview:_spiSettingView];
        [_spiSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_settingView);
        }];
    }
    return _spiSettingView;
}

- (CanFilterSettingView *)canFilterSettingView
{
    if (!_canFilterSettingView) {
        _canFilterSettingView = [[[NSBundle mainBundle] loadNibNamed:@"CanFilterSettingView" owner:self options:nil] firstObject];
        [_settingView addSubview:_canFilterSettingView];
        [_canFilterSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_settingView);
        }];
    }
    return _canFilterSettingView;
}

- (GpioSettingView *)gpioSettingView
{
    if (!_gpioSettingView) {
        _gpioSettingView = [[[NSBundle mainBundle] loadNibNamed:@"GpioSettingView" owner:self options:nil] firstObject];
        [_settingView addSubview:_gpioSettingView];
        [_gpioSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_settingView);
        }];
    }
    return _gpioSettingView;
}

- (SendCanDataParamView *)sendCanDataParamView
{
    if (!_sendCanDataParamView) {
        _sendCanDataParamView = [[[NSBundle mainBundle] loadNibNamed:@"SendCanDataParamView" owner:self options:nil] firstObject];
        [_sendDataParamBackView addSubview:_sendCanDataParamView];
        [_sendCanDataParamView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.left.right.equalTo(_sendDataParamBackView);
            make.top.equalTo(_sendDataParamBackView).offset(20);
        }];
    }
    return _sendCanDataParamView;
}

- (SendI2cDataParamView *)sendI2cDataParamView
{
    if (!_sendI2cDataParamView) {
        _sendI2cDataParamView = [[[NSBundle mainBundle] loadNibNamed:@"SendI2cDataParamView" owner:self options:nil] firstObject];
        [_sendDataParamBackView addSubview:_sendI2cDataParamView];
        [_sendI2cDataParamView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.left.right.equalTo(_sendDataParamBackView);
            make.top.equalTo(_sendDataParamBackView).offset(20);
        }];
    }
    return _sendI2cDataParamView;
}

- (ReadI2cDataParamView *)readI2cDataParamView
{
    if (!_readI2cDataParamView) {
        _readI2cDataParamView = [[[NSBundle mainBundle] loadNibNamed:@"ReadI2cDataParamView" owner:self options:nil] firstObject];
        [_readDataParamBackView addSubview:_readI2cDataParamView];
        [_readI2cDataParamView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.left.right.equalTo(_readDataParamBackView);
            make.top.equalTo(_readDataParamBackView).offset(22);
        }];
    }
    return _readI2cDataParamView;
}

- (ReadSpiDataParamView *)readSpiDataParamView
{
    if (!_readSpiDataParamView) {
        _readSpiDataParamView = [[[NSBundle mainBundle] loadNibNamed:@"ReadSpiDataParamView" owner:self options:nil] firstObject];
        [_readDataParamBackView addSubview:_readSpiDataParamView];
        [_readSpiDataParamView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.left.right.equalTo(_readDataParamBackView);
            make.top.equalTo(_readDataParamBackView).offset(22);
        }];
    }
    return _readSpiDataParamView;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
