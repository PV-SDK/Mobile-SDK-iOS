//
//  MainViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#define DEBUG_METHOD 0

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
PVFlightControllerDelegate
>
{
    NSArray *titleArray;
}
@property (weak, nonatomic) IBOutlet UIButton *connectThePowerEyeButton;
- (IBAction)didClickToConnectThePowerEye:(UIButton *)sender;

@property (nonatomic, assign) PowerEyeConnectState connectState;

@property (nonatomic, strong) PVFlightController *flightController;

@end

@implementation MainViewController

- (IBAction)didClickToConnectThePowerEye:(UIButton *)sender {
    sender.userInteractionEnabled = NO;
    if (self.connectState == PowerEyeConnectStateDisConnected) {
        [self.flightController startConnectFlight];
    }else if (self.connectState == PowerEyeConnectStateConnected) {
        [self.flightController stopConnectFlight];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

#pragma mark - PVFlightControllerDelegate
- (void)flightController:(PVFlightController *)fc didUpdateFlightState:(PVFlightControllerState *)state stateType:(PVStateUpdate)stateUpdate
{
    switch (stateUpdate) {
        case PVFlightConnectStateUpdate:
            [self updateConnectStatus:state.flightConnectState];
            break;
            
        default:
            break;
    }
}
#pragma mark - Update Connect State
- (void)updateConnectStatus:(PVFlightConnectState)state
{
    if (state == PVFlightConnectStateConnected) {
        self.connectState = PowerEyeConnectStateConnected;
        [self.connectThePowerEyeButton setTitle:@"Disconnect The PowerEye" forState:UIControlStateNormal];
        [self performSegueWithIdentifier:@"ShowFlightViewController" sender:self];
    } else {
        self.connectState = PowerEyeConnectStateDisConnected;
        [self.connectThePowerEyeButton setTitle:@"Connect The PowerEye" forState:UIControlStateNormal];
        if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[FlightViewController class]]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"NotificationToPopRootViewController" object:nil];
            ShowResult(@"Notification：PowerEye is disconnect!");
        }
        if (DEBUG_METHOD) {
            [self performSegueWithIdentifier:@"ShowFlightViewController" sender:self];
        }
    }
    self.connectThePowerEyeButton.userInteractionEnabled = YES;
}

#pragma mark - Lazying...
-(PVFlightController *)flightController{
    if (_flightController == nil) {
        _flightController = [ComponentHelper fetchFlightController];
        _flightController.delegate = self;
    }
    return _flightController;
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
