//
//  FlightViewController.m
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/22.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "FlightViewController.h"
#import <PVSDK/PVSDK.h>

#import "CameraSettingVC.h"
#import "PVSDK_VideoStreamView.h"

//  延迟执行云台执行操作时间
#define GimabalCommandTimer 0.2f
//  延迟执行云台定位操作时间
#define GimabalDefaultTimer 0.5f

//  云台 Move Value
#define GimabalMoveValue 800.0f;

typedef enum : NSUInteger {
    GimabalDirectionDefault = 0,    //  默认
    GimabalDirectionUp      = 1,    //  向上
    GimabalDirectionDown    = 2,    //  向下
    GimabalDirectionLeft    = 3,    //  向左
    GimabalDirectionRight   = 4     //  向右
} GimabalDirection;

@interface FlightViewController ()
<
PVCameraDelegate,
PVRemoteControllerDelegate
>
{
    PVCameraShootState shootState;
}

@property (weak, nonatomic) IBOutlet UIView *cameraControlView;

@property (weak, nonatomic) IBOutlet UIButton *changeCameraModeButton;
@property (weak, nonatomic) IBOutlet UIButton *shootButton;

@property (nonatomic, assign) BOOL isStreamStartRecord;

@property (nonatomic, strong) PVCamera *cameraManager;
@property (nonatomic, strong) PVFlightController *flightController;
@property (nonatomic, strong) PVBattery *batteryManager;
@property (nonatomic, strong) PVRemoteController *remoteController;
@property (nonatomic, strong) PVGimabal *gimabalManager;

/**
 相机操作
 */
@property (nonatomic, assign) PVCameraHandleType handleType;

@property (nonatomic, strong) PVSDK_VideoStreamView *streamView;

@end

@implementation FlightViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    //  屏幕保持常亮
    [UIApplication sharedApplication].idleTimerDisabled = YES;
    
    [self configManager];
    //  配置相机管理器
    [self.cameraManager configCameraManager];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillResignActive:) name:@"ApplicationWillResignActive" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidBecomeActive:) name:@"ApplicationDidBecomeActive" object:nil];
}

- (void)applicationWillResignActive:(NSNotification *)notifi{
    //==============暂停相机图传==============
    [self.streamView.vfVideo Pause];
    //======================================
}

- (void)applicationDidBecomeActive:(NSNotification *)notifi{
    //==============暂停相机图传==============
    [self.streamView.vfVideo Play];
    //======================================
}

- (void)viewWillAppear:(BOOL)animated{
    //=========连接相机和开启数据流传输=========
    [self openVideoStream];
    //======================================
}

- (void)viewWillDisappear:(BOOL)animated
{
    //======断开相机连接和断开数据流传输=========
    [self closeVideoStream];
    //======================================
}

#pragma mark - 配置管理器
- (void)configManager
{
    self.flightController = [PVFlightController new];
    
    self.cameraManager = [PVCamera new];
    self.cameraManager.delegate = self;
    
    self.gimabalManager = [PVGimabal new];
    
    self.batteryManager = [PVBattery new];
    
    self.remoteController = [PVRemoteController new];
    self.remoteController.delegate = self;
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //  获取相机模式
        [self getCameraState];
    });
}

#pragma mark - Command
//TODO: [Command] Open Video Stream
- (void)openVideoStream
{
    if (_streamView == nil) {
        [self.view insertSubview:self.streamView belowSubview:self.cameraControlView];
    }
    [_streamView openVideoStreamCallBack:^(PVCameraCommandReceive result, NSInteger error) {
        NSLog(@"【OpenVideoStream】Receive:%lu,ErrorID:%ld",(unsigned long)result, (long)error);
        if (result == PVCameraCommandReceiveSuccess) {
            
        }
    }];
}
//TODO: [Command] Close Video Stream
- (void)closeVideoStream
{
    [_streamView closeVideo:YES CallBack:^(PVCameraCommandReceive result, NSInteger error) {
        NSLog(@"【CloseVideo】Receive:%lu,ErrorID:%ld",(unsigned long)result, (long)error);
        if (result == PVCameraCommandReceiveSuccess) {
            
        }
    }];
}
//TODO: [Command] 获取相机状态
- (void)getCameraState
{
    if (self.flightController.flightConnectState == PVFlightConnectStateConnected || self.flightController.flightConnectState == PVFlightConnectStateHeartTimeoutReply) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self.cameraManager getCameraCurrentState:^(PVCameraState camerastate, NSError * _Nullable error) {
                switch (camerastate) {
                    case PVCameraStateRecing:
                        NSLog(@"正在录像状态______");
                        shootState = PVCameraShootStateRecording;
                        [self updateCameraShootButoonState:shootState];
                        break;
                    case PVCameraStateShootSuccess:
                        shootState = PVCameraShootStateTakePhoto;
                        [self updateCameraShootButoonState:shootState];
                        break;
                    case PVCameraStateRecModeSuccess:
                        shootState = PVCameraShootStateRecord;
                        [self updateCameraShootButoonState:shootState];
                        break;
                    case PVCameraStateShootModeSuccess:
                        shootState = PVCameraShootStateTakePhoto;
                        [self updateCameraShootButoonState:shootState];
                        break;
                        
                    default:
                        break;
                }
            }];
        });
    }
}

//TODO: [Command] 云台控制
- (void)setGimabalWithDirection:(GimabalDirection)direction
{
    PVGimabalAttitude attitude;
    
    switch (direction) {
        case GimabalDirectionDefault:
        {
            attitude.roll = 0.0f;
            attitude.pitch = 0.0f;
            attitude.yaw = 0.0f;
        }
            break;
        case GimabalDirectionUp:
        {
            attitude.roll = 0.0f;
            attitude.pitch = -GimabalMoveValue;
            attitude.yaw = 0.0f;
        }
            break;
        case GimabalDirectionDown:
        {
            attitude.roll = 0.0f;
            attitude.pitch = GimabalMoveValue;
            attitude.yaw = 0.0f;
        }
            break;
        case GimabalDirectionLeft:
        {
            attitude.roll = 0.0f;
            attitude.pitch = 0.0f;
            attitude.yaw = GimabalMoveValue;
        }
            break;
        case GimabalDirectionRight:
        {
            attitude.roll = 0.0f;
            attitude.pitch = 0.0f;
            attitude.yaw = -GimabalMoveValue;
        }
            break;
        default:
            break;
    }
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalCommandTimer * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [_gimabalManager updateGimabalAttitude:attitude];
    });
}

#pragma mark - 更新拍摄按钮状态
- (void)updateCameraShootButoonState:(PVCameraShootState)state
{
    if (state == PVCameraShootStateTakePhoto) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.shootButton setTitle:@"拍照" forState:UIControlStateNormal];
        });
    }else if (state == PVCameraShootStateRecording){
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.shootButton setTitle:@"停止录像" forState:UIControlStateNormal];
        });
    }else if (state == PVCameraShootStateRecord){
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.shootButton setTitle:@"开始录像" forState:UIControlStateNormal];
        });
    }
}

#pragma mark - Button Method
//TODO: [Button Method] Change Camera Mode
- (IBAction)didClickToChangeCameraMode:(UIButton *)sender
{
    if (shootState == PVCameraShootStateTakePhoto) {
        [self.cameraManager setCameraMode:PVCameraModeRecordVideo];
    }else if (shootState == PVCameraShootStateRecord) {
        [self.cameraManager setCameraMode:PVCameraModeShootPhoto];
        /*
        [self.streamView changeCameraModeCallBack:^(PVCameraCommandReceive result, NSInteger error) {
            [self updateCameraShootButoonState:self.streamView.shootState];
        }];
         */
    }
}
//TODO: [Button Method] Shoot
- (IBAction)didClickToShoot:(UIButton *)sender
{
    if (shootState == PVCameraShootStateTakePhoto) {
        //  拍照
        [self.cameraManager takePhoto];
    }else if (shootState == PVCameraShootStateRecord){
        //  开始录像
        [self.cameraManager startRecordVideo];
    }else if (shootState == PVCameraShootStateRecording){
        //  停止录像
        [self.cameraManager stopRecordVideo];
    }
}
//TODO: [Button Method] Show Camera Parameter
- (IBAction)didClickToShowCameraParameter:(UIButton *)sender
{
    if (shootState == PVCameraShootStateRecording) {
        return;
    }
    [self performSegueWithIdentifier:@"PushToCameraSettingVC" sender:self];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"PushToCameraSettingVC"]) {
        CameraSettingVC *settingVC = segue.destinationViewController;
        settingVC.shootState = (int)shootState;
    }
}

#pragma mark - Cradle head direction Control
//TODO: [Button Method] Cradle head Turn [↑]
- (IBAction)touchdownToUP:(UIButton *)sender
{
    [self setGimabalWithDirection:GimabalDirectionUp];
}
- (IBAction)touchupToUP:(UIButton *)sender
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTimer * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self setGimabalWithDirection:GimabalDirectionDefault];
    });
}

//TODO: [Button Method] Cradle head Turn [↓]
- (IBAction)touchdownToDown:(UIButton *)sender
{
    [self setGimabalWithDirection:GimabalDirectionDown];
}
- (IBAction)touchupToDown:(UIButton *)sender
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTimer * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self setGimabalWithDirection:GimabalDirectionDefault];
    });
}

//TODO: [Button Method] Cradle head Turn [←]
- (IBAction)touchdownToLeft:(UIButton *)sender
{
    [self setGimabalWithDirection:GimabalDirectionLeft];
}
- (IBAction)touchupToLeft:(UIButton *)sender
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTimer * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self setGimabalWithDirection:GimabalDirectionDefault];
    });
}

//TODO: [Button Method] Cradle head Turn [→]
- (IBAction)touchdownToRight:(UIButton *)sender
{
    [self setGimabalWithDirection:GimabalDirectionRight];
}
- (IBAction)touchupToRight:(UIButton *)sender
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTimer * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self setGimabalWithDirection:GimabalDirectionDefault];
    });
}

#pragma mark - PVCameraDelegate
- (void)camera:(PVCamera *_Nonnull)camera didUpdateCameraState:(PVCameraState)cameraState
{
    switch (cameraState) {
            //正在录像
        case PVCameraStateRecing:
        {
            NSLog(@"开始录像");
            shootState = PVCameraShootStateRecording;
            [self updateCameraShootButoonState:shootState];
            /*
            [self.streamView startRecordCallBack:^(PVCameraCommandReceive result, NSInteger error) {
                NSLog(@"【StartRecordCallBack】Receive:%lu,ErrorID:%ld",(unsigned long)result, (long)error);
                if (result == PVCameraCommandReceiveSuccess) {
                    self.isStreamStartRecord = YES;
                    [self updateCameraShootButoonState:self.streamView.shootState];
                }
            }];
             */
        }
            break;
            //启动录像失败
        case PVCameraStateRecStartError:
            NSLog(@"启动录像失败....................2");
            break;
            //拍照中
        case PVCameraStateShooting:
            
            break;
            //拍照成功
        case PVCameraStateShootSuccess:
        {
            NSLog(@"拍照成功");
            /*
            [self.streamView takephotoCallBack:^(PVCameraCommandReceive result, NSInteger error) {
                NSLog(@"【TakephotoCallBack】Receive:%lu,ErrorID:%ld",(unsigned long)result, (long)error);
            }];
             */
        }
            break;
            //拍照错误
        case PVCameraStateShootError:

            break;
            //相机操作超时
        case PVCameraStateTimeout:
            switch (self.handleType) {
                case PVCameraHandleTypeSwitchRec:

                    break;
                case PVCameraHandleTypeSwitchShootPhoto:

                    break;
                case PVCameraHandleTypeStartRec:

                    break;
                case PVCameraHandleTypeStopRec:
                    
                    break;
                case PVCameraHandleTypeShootPhoto:
                    
                    break;
                    
                default:
                    break;
            }
            break;
            //录像结束
        case PVCameraStateRecStop:
        {
            NSLog(@"停止录像");
            shootState = PVCameraShootStateRecord;
            [self updateCameraShootButoonState:shootState];
            
            if (self.isStreamStartRecord) {
                /*
                [self.streamView stopRecordCallBack:^(PVCameraCommandReceive result, NSInteger error) {
                    NSLog(@"【StopRecordCallBack】Receive:%lu,ErrorID:%ld",(unsigned long)result, (long)error);
                    if (result == PVCameraCommandReceiveSuccess) {
                        self.isStreamStartRecord = NO;
                    }
                }];
                 */
            }
        }
            break;
            //结束录像失败
        case PVCameraStateRecStopError:
            NSLog(@"停止录像失败....................5");
            break;
            //切换拍照模式成功
        case PVCameraStateShootModeSuccess:
        {
            NSLog(@"切换拍照模式....................10");
            shootState = PVCameraShootStateTakePhoto;
            [self updateCameraShootButoonState:shootState];
            
            /*
            [self.streamView changeCameraModeCallBack:^(PVCameraCommandReceive result, NSInteger error) {
                
            }];
             */
        }
            break;
            //切换拍照模式失败:
        case PVCameraStateShootModeError:

            break;
            //切换录像模式成功
        case PVCameraStateRecModeSuccess:
            NSLog(@"切换录像模式....................10");
            shootState = PVCameraShootStateRecord;
            [self updateCameraShootButoonState:shootState];
            /*
            [self.streamView changeCameraModeCallBack:^(PVCameraCommandReceive result, NSInteger error) {
                
            }];
             */

            break;
            //切换录像模式失败
        case PVCameraStateRecModeError:
            NSLog(@"正在录像....................6");

            break;
            
            //拍照相机SD卡已满
        case PVCameraStateShootErrorSDFull:
            NSLog(@"拍照时SD卡满....................7");
            break;
            //录像时SD卡已满
        case PVCameraStateRecErrorSDFull:
            NSLog(@"录像时SD卡满....................7");
            switch (self.handleType) {
                case PVCameraHandleTypeStartRec:

                    
                    break;
                case PVCameraHandleTypeStopRec:

                    break;
                    
                default:
                    break;
            }
            break;
            //拍照相机SD卡出错
        case PVCameraStateShootErrorSDError:
            NSLog(@"拍照相机SD卡出错....................8");
            break;
            //录像相机SD卡出错
        case PVCameraStateRecErrorSDError:
            NSLog(@"录像相机SD卡出错....................8");
            switch (self.handleType) {
                case PVCameraHandleTypeStartRec:

                    break;
                case PVCameraHandleTypeStopRec:

                    break;
                    
                default:
                    break;
            }
            break;
        case PVCameraStateShootErrorSDNull:
            if (self.handleType == PVCameraHandleTypeShootPhoto) {
                NSLog(@"拍照时相机SD卡为空....................8");
            }
            break;
        case PVCameraStateRecErrorSDNull:
            NSLog(@"录像时SD卡为空....................8");
            switch (self.handleType) {
                case PVCameraHandleTypeStartRec:

                    
                    break;
                case PVCameraHandleTypeStopRec:

                    break;
                    
                default:
                    break;
            }
            
            break;
            
        default:
            break;
    }
}
- (void)camera:(PVCamera *_Nonnull)camera didUpdateSDCardState:(PVCameraSDCardState *_Nonnull)sdCardState
{
    NSLog(@"SDCardState:%@",sdCardState);
}

#pragma mark - PVRemoteControllerDelegate
- (void)remoteController:(PVRemoteController *_Nonnull)rc didUpdateRemotePosition:(CLLocationCoordinate2D)remotePosition
{
    NSLog(@"RemoteConnectState:%lu",(unsigned long)rc.remoteConnectState);
}

#pragma mark - Lazying...
-(PVSDK_VideoStreamView *)streamView
{
    if (_streamView == nil) {
        CGRect frame = CGRectMake(0, 32, self.view.bounds.size.width, self.view.bounds.size.height - 32);
        _streamView = [[PVSDK_VideoStreamView alloc] initWithFrame:frame];
    }
    return _streamView;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
