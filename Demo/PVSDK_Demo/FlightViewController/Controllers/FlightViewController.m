//
//  FlightViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "FlightViewController.h"
#import "ComponentHelper.h"

#import "CameraSettingVC.h"
#import "PVVideoStreamView.h"

#define GimabalCommandTime 0.2f

#define GimabalDefaultTime 0.5f

#define GimabalMoveValue 800.0f;


typedef enum : NSUInteger {
    GimabalDirectionDefault = 0,    
    GimabalDirectionUp      = 1,    
    GimabalDirectionDown    = 2,    
    GimabalDirectionLeft    = 3,    
    GimabalDirectionRight   = 4
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
@property (weak, nonatomic) IBOutlet UIView *gimabalControlView;

@property (nonatomic, strong) PVCamera *cameraManager;
@property (nonatomic, strong) PVFlightController *flightController;
@property (nonatomic, strong) PVBattery *batteryManager;
@property (nonatomic, strong) PVRemoteController *remoteController;
@property (nonatomic, strong) PVGimabal *gimabalManager;

@property (nonatomic, assign) PVCameraHandleType handleType;

@property (nonatomic, strong) PVVideoStreamView *streamView;

@end

@implementation FlightViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [UIApplication sharedApplication].idleTimerDisabled = YES;
    
    [self configManager];
    
    [self.cameraManager configCameraManager];
    
    //  断开与飞机的连接的通知
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(notificationToPopViewController:) name:@"NotificationToPopRootViewController" object:nil];
    //  App 将要失去活跃状态的通知
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillResignActive:) name:@"ApplicationWillResignActive" object:nil];
    //  App 获得活跃状态的通知
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidBecomeActive:) name:@"ApplicationDidBecomeActive" object:nil];
}

#pragma mark - Notification-Selector
- (void)notificationToPopViewController:(NSNotification *)notifi{
    [self.navigationController popViewControllerAnimated:YES];
}
- (void)applicationWillResignActive:(NSNotification *)notifi
{
    [self.streamView.vfVideo Pause];
}
- (void)applicationDidBecomeActive:(NSNotification *)notifi
{
    [self.streamView.vfVideo Play];
}

- (void)viewWillAppear:(BOOL)animated
{
    [self openVideoStream];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self closeVideoStream];
}

#pragma mark - Configure manager
- (void)configManager
{
    self.flightController = [ComponentHelper fetchFlightController];
    
    self.cameraManager = [ComponentHelper fetchCamera];
    self.cameraManager.delegate = self;
    
    self.gimabalManager = [ComponentHelper fetchGimabal];
    
    self.batteryManager = [ComponentHelper fetchBattery];
    
    self.remoteController = [ComponentHelper fetchRemoteController];
    self.remoteController.delegate = self;
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //  Get camera state
        [self getCameraState];
    });
}

#pragma mark - Command
//TODO: [Command] Open video stream
- (void)openVideoStream
{
    if (_streamView == nil) {
        [self.view insertSubview:self.streamView belowSubview:self.gimabalControlView];
    }
    [_streamView openVideoStreamCallBack:^(PVCameraCommandReceive result, NSInteger error) {
        NSLog(@"【Open video stream】Receive:%lu,ErrorID:%ld",(unsigned long)result, (long)error);
        if (result == PVCameraCommandReceiveSuccess) {
            
        }
    }];
}
//TODO: [Command] Close video stream
- (void)closeVideoStream
{
    [_streamView closeVideo:YES CallBack:^(PVCameraCommandReceive result, NSInteger error) {
        NSLog(@"【Close video】Receive:%lu,ErrorID:%ld",(unsigned long)result, (long)error);
        if (result == PVCameraCommandReceiveSuccess) {
            
        }
    }];
}
//TODO: [Command] Get camera state
- (void)getCameraState
{
    if (self.flightController.flightConnectState == PVFlightConnectStateConnected || self.flightController.flightConnectState == PVFlightConnectStateHeartTimeoutReply) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self.cameraManager getCameraCurrentState:^(PVCameraState camerastate, NSError * _Nullable error) {
                switch (camerastate) {
                    case PVCameraStateRecing:
                    {
                        NSLog(@"Current Camera State--> PVCameraStateRecing");
                        shootState = PVCameraShootStateRecording;
                        [self updateCameraShootButoonState:shootState];
                    }
                        break;
                    case PVCameraStateShootSuccess:
                    {
                        NSLog(@"Current Camera State--> PVCameraStateShootSuccess");
                        shootState = PVCameraShootStateTakePhoto;
                        [self updateCameraShootButoonState:shootState];
                    }
                        break;
                    case PVCameraStateRecModeSuccess:
                    {
                        NSLog(@"Current Camera State--> PVCameraStateRecModeSuccess");
                        shootState = PVCameraShootStateRecord;
                        [self updateCameraShootButoonState:shootState];
                    }
                        break;
                    case PVCameraStateShootModeSuccess:
                    {
                        NSLog(@"Current Camera State--> PVCameraStateShootModeSuccess");
                        shootState = PVCameraShootStateTakePhoto;
                        [self updateCameraShootButoonState:shootState];
                    }
                        break;
                        
                    default:
                        break;
                }
            }];
        });
    }
}

//TODO: [Command] Gimabal direction control
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
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalCommandTime * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [_gimabalManager updateGimabalAttitude:attitude];
    });
}

#pragma mark - Update camera shoot button state
- (void)updateCameraShootButoonState:(PVCameraShootState)state
{
    if (state == PVCameraShootStateTakePhoto) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.shootButton setTitle:@"Take photos" forState:UIControlStateNormal];
        });
    }else if (state == PVCameraShootStateRecording){
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.shootButton setTitle:@"Stop record" forState:UIControlStateNormal];
        });
    }else if (state == PVCameraShootStateRecord){
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.shootButton setTitle:@"Start record" forState:UIControlStateNormal];
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
    }
}
//TODO: [Button Method] Shoot
- (IBAction)didClickToShoot:(UIButton *)sender
{
    if (shootState == PVCameraShootStateTakePhoto) {
        [self.cameraManager takePhoto];
    }else if (shootState == PVCameraShootStateRecord){
        [self.cameraManager startRecordVideo];
    }else if (shootState == PVCameraShootStateRecording){
        [self.cameraManager stopRecordVideo];
    }
}
//TODO: [Button Method] Show camera parameter
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
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTime * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
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
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTime * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
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
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTime * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
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
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(GimabalDefaultTime * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self setGimabalWithDirection:GimabalDirectionDefault];
    });
}

#pragma mark - PVCameraDelegate
- (void)camera:(PVCamera *_Nonnull)camera didUpdateCameraState:(PVCameraState)cameraState
{
    switch (cameraState) {
        case PVCameraStateRecing:
        {
            NSLog(@"Camera State Receive--> PVCameraStateRecing");
            shootState = PVCameraShootStateRecording;
            [self updateCameraShootButoonState:shootState];
        }
            break;
            
        case PVCameraStateRecStartError:
            NSLog(@"Camera State Receive--> PVCameraStateRecStartError");
            break;
            
        case PVCameraStateShooting:
            NSLog(@"Camera State Receive--> PVCameraStateShooting");
            break;
            
        case PVCameraStateShootSuccess:
            NSLog(@"Camera State Receive--> PVCameraStateShootSuccess");
            break;
            
        case PVCameraStateShootError:
            NSLog(@"Camera State Receive--> PVCameraStateShootError");
            break;
            
        case PVCameraStateTimeout:
            switch (self.handleType) {
                case PVCameraHandleTypeSwitchRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeSwitchRec");
                    break;
                case PVCameraHandleTypeSwitchShootPhoto:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeSwitchShootPhoto");
                    break;
                case PVCameraHandleTypeStartRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStartRec");
                    break;
                case PVCameraHandleTypeStopRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStopRec");
                    break;
                case PVCameraHandleTypeShootPhoto:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeShootPhoto");
                    break;
                    
                default:
                    break;
            }
            break;
            
        case PVCameraStateRecStop:
        {
            NSLog(@"Camera State Receive--> PVCameraStateRecStop");
            shootState = PVCameraShootStateRecord;
            [self updateCameraShootButoonState:shootState];
        }
            break;
            
        case PVCameraStateRecStopError:
            NSLog(@"Camera State Receive--> PVCameraStateRecStopError");
            break;
            
        case PVCameraStateShootModeSuccess:
        {
            NSLog(@"Camera State Receive--> PVCameraStateShootModeSuccess");
            shootState = PVCameraShootStateTakePhoto;
            [self updateCameraShootButoonState:shootState];
        }
            break;
            
        case PVCameraStateShootModeError:
            NSLog(@"Camera State Receive--> PVCameraStateShootModeError");
            break;
            
        case PVCameraStateRecModeSuccess:
            NSLog(@"Camera State Receive--> PVCameraStateRecModeSuccess");
            shootState = PVCameraShootStateRecord;
            [self updateCameraShootButoonState:shootState];

            break;
        case PVCameraStateRecModeError:
            NSLog(@"Camera State Receive--> PVCameraStateRecModeError");
            break;
            
        case PVCameraStateShootErrorSDFull:
            NSLog(@"Camera State Receive--> PVCameraStateShootErrorSDFull");
            break;
            
        case PVCameraStateRecErrorSDFull:
            switch (self.handleType) {
                case PVCameraHandleTypeStartRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStartRec");
                    break;
                    
                case PVCameraHandleTypeStopRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStopRec");
                    break;
                    
                default:
                    break;
            }
            break;
            
        case PVCameraStateShootErrorSDError:
            NSLog(@"Camera State Receive--> PVCameraStateShootErrorSDError");
            break;
            
        case PVCameraStateRecErrorSDError:
            switch (self.handleType) {
                case PVCameraHandleTypeStartRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStartRec");
                    break;
                    
                case PVCameraHandleTypeStopRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStopRec");
                    break;
                    
                default:
                    break;
            }
            break;
            
        case PVCameraStateShootErrorSDNull:
            if (self.handleType == PVCameraHandleTypeShootPhoto) {
                NSLog(@"Camera State Receive--> PVCameraStateShootErrorSDNull");
            }
            break;
            
        case PVCameraStateRecErrorSDNull:
            NSLog(@"Camera State Receive--> PVCameraStateRecErrorSDNull");
            switch (self.handleType) {
                case PVCameraHandleTypeStartRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStartRec");
                    break;
                    
                case PVCameraHandleTypeStopRec:
                    NSLog(@"Camera State Receive--> PVCameraHandleTypeStopRec");
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
    NSLog(@"SDCard State Receive--> PVCameraHandleTypeStopRec");
}

#pragma mark - PVRemoteControllerDelegate
- (void)remoteController:(PVRemoteController *_Nonnull)rc didUpdateRemotePosition:(CLLocationCoordinate2D)remotePosition
{
    NSLog(@"Remote Connect State Receive--> %lu",(unsigned long)rc.remoteConnectState);
}

#pragma mark - Lazying...
-(PVVideoStreamView *)streamView
{
    if (_streamView == nil) {
        CGRect frame = CGRectMake(0, 32, self.view.bounds.size.width, self.view.bounds.size.height - 32);
        _streamView = [[PVVideoStreamView alloc] initWithFrame:frame];
    }
    return _streamView;
}

-(void)dealloc{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"NotificationToPopRootViewController" object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"ApplicationWillResignActive" object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"ApplicationDidBecomeActive" object:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
