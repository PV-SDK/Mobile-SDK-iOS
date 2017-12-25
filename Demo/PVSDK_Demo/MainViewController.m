//
//  MainViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#define DEBUG_METHOD 1

#import "MainViewController.h"
#import "ComponentHelper.h"

#import "FlightViewController.h"
#import "MountViewController.h"

typedef enum : NSUInteger {
    PowerEyeConnectStateDisConnected  = 0,
    PowerEyeConnectStateConnected     = 1
} PowerEyeConnectState;

@interface MainViewController ()
<
PVSDKManagerDelegate
>
{
    NSArray *titleArray;
}
@property (weak, nonatomic) IBOutlet UIButton *connectThePowerEyeButton;
- (IBAction)didClickToConnectThePowerEye:(UIButton *)sender;

@property (nonatomic, assign) PowerEyeConnectState connectState;

@property (nonatomic, strong) PVSDKManager *sdkManager;

@end

@implementation MainViewController

- (IBAction)didClickToConnectThePowerEye:(UIButton *)sender {
    sender.userInteractionEnabled = NO;
    if (self.connectState == PowerEyeConnectStateDisConnected) {
        [self.sdkManager startConnectToProduct];
    }else if (self.connectState == PowerEyeConnectStateConnected) {
        [self.sdkManager stopConnectToProduct];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //  Configure NavigationBar
    [self configNavigationBar];
}

- (void)configNavigationBar{
    self.navigationController.navigationBar.tintColor = [UIColor blackColor];
}

#pragma mark - PVSDKManagerDelegate
-(void)pv_sdkManager:(PVSDKManager *)manager didUpdateConnectStateWithHelper:(PVProductHelper *)helper{
    [self updateConnectStatus:helper.connectState];
}

- (void)pv_sdkManager:(PVSDKManager *)manager didUpdateFlightModeWithHelper:(PVFlightHelper *)helper{
    NSLog(@"Flight Mode:%lu",(unsigned long)helper.flightMode);
}

#pragma mark - Update Connect State
- (void)updateConnectStatus:(PVConnectState)state
{
    if (state == PVConnectState_Connection_Connected) {
        self.connectState = PowerEyeConnectStateConnected;
        [self.connectThePowerEyeButton setTitle:@"Disconnect The PowerEye" forState:UIControlStateNormal];
        [self performSegueWithIdentifier:@"ShowFlightViewController" sender:self];
    } else {
        self.connectState = PowerEyeConnectStateDisConnected;
        [self.connectThePowerEyeButton setTitle:@"Connect The PowerEye" forState:UIControlStateNormal];
        
        if (DEBUG_METHOD) {
            [self performSegueWithIdentifier:@"ShowFlightViewController" sender:self];
        }else{
//            if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[MainViewController class]]) {
//                [[NSNotificationCenter defaultCenter] postNotificationName:@"NotificationToPopRootViewController" object:nil];
//                return;
//            }
        }
    }
    self.connectThePowerEyeButton.userInteractionEnabled = YES;
}

#pragma mark - Lazying...
-(PVSDKManager *)sdkManager{
    if (_sdkManager == nil) {
        _sdkManager = [ComponentHelper fetchSDKManager];
        _sdkManager.delegate = self;
    }
    return _sdkManager;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


@end
