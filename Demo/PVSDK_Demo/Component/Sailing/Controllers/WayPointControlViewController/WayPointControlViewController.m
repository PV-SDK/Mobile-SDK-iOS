//
//  WayPointControlViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import "WayPointControlViewController.h"
#import <PVSDK/PVSDK.h>
#import <CoreLocation/CoreLocation.h>
#import "UIViewController+BackButtonHandler.h"

////////////////////////////////////////////////////////////////////////
/// 地球半径：6371000M
///
/// 地球周长：2 * 6371000M  * π = 40030173
///
/// 纬度38°地球周长：40030173 * cos38 = 31544206M
///
/// 任意地球经度周长：40030173M
///
/// 经度（东西方向）1M实际度：360°/31544206M=1.141255544679108e-5=0.00001141
/// 纬度（南北方向）1M实际度：360°/40030173M=8.993216192195822e-6=0.00000899
///
/// 经度（东西方向）100M实际度：0.00001141°* 100=0.001141
/// 纬度（南北方向）100M实际度：0.00000899°* 100=0.000899
////////////////////////////////////////////////////////////////////////
#define PerMeter_Longitude 0.00001141
#define PerMeter_Latitude 0.00000899

#define PointDistanceMeter 20

#define WayPointStayTime 100.0f
#define WayPointHeight 50.0f

#import <PVSDK/PVSDK.h>

@interface WayPointControlViewController ()

@property (nonatomic, assign) CLLocationCoordinate2D currentLocation;

@property (nonatomic, strong) PVWayPointModel *locationOne;
@property (nonatomic, strong) PVWayPointModel *locationTwo;
@property (nonatomic, strong) PVWayPointModel *locationThree;
@property (nonatomic, strong) PVWayPointModel *locationFour;

@property (weak, nonatomic) IBOutlet UILabel *eyeCurrentLongitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *eyeCurrentLatitudeLabel;
///////////////////////////////////////////////////////////////////////
@property (weak, nonatomic) IBOutlet UILabel *pointOneLongitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *pointOneLatitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *pointTwoLongitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *pointTwoLatitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *pointThreeLongitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *pointThreeLatitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *pointFourLongitudeLabel;
@property (weak, nonatomic) IBOutlet UILabel *pointFourLatitudeLabel;
////////////////////////////////////////////////////////////////////////////////
@property (weak, nonatomic) IBOutlet UIView *navigationalStateView;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointStartLabel;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointOneLabel;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointOneToTwoLabel;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointTwoLabel;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointTwoToThreeLabel;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointThreeLabel;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointThreeToFourLabel;
@property (weak, nonatomic) IBOutlet UILabel *navigationPointFourLabel;
///////////////////////////////////////////////////////////////////////
@property (weak, nonatomic) IBOutlet UIButton *navigatingControlButton;

@property (nonatomic, assign) BOOL generateWaypoint;
@property (nonatomic, assign) BOOL isNavigationStart;

@property (nonatomic, assign) int currentPoint;
@property (nonatomic, assign) int reachedPoint;

- (IBAction)didClickToGenerateWaypoint:(UIButton *)sender;
- (IBAction)didClickToControlNavigating:(UIButton *)sender;

@end

@implementation WayPointControlViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateLocation:) name:@"NOTIFICATION_WayPointViewController_UpdateLocation" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateWayPointState:) name:@"NOTIFICATION_WayPointViewController_UpdateWayPointState" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sendWayPointResult:) name:@"NOTIFICATION_WayPointViewController_SendWayPointResult" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changeToLastMode:) name:@"NOTIFICATION_WayPointViewController_ChangeLastMode" object:nil];
}

- (void)updateLocation:(NSNotification *)notifi{
    CLLocationCoordinate2D location;
    location.longitude = [[notifi userInfo][@"longitude"] doubleValue];
    location.latitude = [[notifi userInfo][@"latitude"] doubleValue];
    
    self.currentLocation = location;
    
    self.eyeCurrentLongitudeLabel.text = [NSString stringWithFormat:@"%f",location.longitude];
    self.eyeCurrentLatitudeLabel.text = [NSString stringWithFormat:@"%f",location.latitude];
}

- (void)updateWayPointState:(NSNotification *)notifi{
    if ([notifi userInfo] != nil) {
        if (self.isNavigationStart) {
            [self.navigatingControlButton setTitle:@"Start navigating" forState:UIControlStateNormal];
            self.isNavigationStart = NO;
        }else{
            [self.navigatingControlButton setTitle:@"Stop navigating" forState:UIControlStateNormal];
            self.isNavigationStart = YES;
        }

        self.navigationalStateView.hidden = NO;
    }
    NSString *currentPointStr = [notifi userInfo][@"currentPoint"];
    NSString *reachedPointStr = [notifi userInfo][@"reachedPoint"];
    if (currentPointStr.length != 0) {
        self.currentPoint = [[notifi userInfo][@"currentPoint"] intValue];
        NSLog(@"CurrentPoint:%d",_currentPoint);
    }
    if (reachedPointStr.length != 0) {
        self.reachedPoint = [[notifi userInfo][@"reachedPoint"] intValue];
        NSLog(@"ReachedPoint:%d",_reachedPoint);
    }
    [self updateWayPointView];
}

- (void)updateWayPointView{
    
    if (_currentPoint == 1 && _reachedPoint == 0) {         //  -> 1
        self.navigationPointStartLabel.hidden = NO;
    }else if (_currentPoint == 1 && _reachedPoint == 1) {   //  1
        self.navigationPointOneLabel.hidden = NO;
    }else if (_currentPoint == 2 && _reachedPoint == 1) {   //  1 -> 2
        self.navigationPointOneToTwoLabel.hidden = NO;
    }else if (_currentPoint == 2 && _reachedPoint == 2) {   //  2
        self.navigationPointTwoLabel.hidden = NO;
    }else if (_currentPoint == 3 && _reachedPoint == 2) {   //  2 -> 3
        self.navigationPointTwoToThreeLabel.hidden = NO;
    }else if (_currentPoint == 3 && _reachedPoint == 3) {   //  3
        self.navigationPointThreeLabel.hidden = NO;
    }else if (_currentPoint == 4 && _reachedPoint == 3) {   //  3 -> 4
        self.navigationPointThreeToFourLabel.hidden = NO;
    }else if (_currentPoint == 4 && _reachedPoint == 4) {   //  4
        self.isNavigationStart = NO;
        self.navigationPointFourLabel.hidden = NO;
    }
}

- (void)sendWayPointResult:(NSNotification *)notifi{
    self.generateWaypoint = [[notifi userInfo][@"result"] isEqualToString:@"Success"] ? YES : NO;
}

- (void)changeToLastMode:(NSNotification *)notifi{
    if ([[notifi userInfo][@"result"] isEqualToString:@"Success"]) {
        if (_isNavigationStart) {
            [self.navigationController popViewControllerAnimated:YES];
            return;
        }
        if ([PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_MANUAL || [PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_ALTCTL || [PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_POSCTL) {
            [self generateWaypointWithLocation:_currentLocation];
        }
    }
}

- (IBAction)didClickToGenerateWaypoint:(UIButton *)sender {
    if ([PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_MANUAL || [PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_ALTCTL || [PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_POSCTL) {
        [self generateWaypointWithLocation:_currentLocation];
    }else{
        [[PVNavigation shareNavigation] setLastMode];
    }
}

- (void)generateWaypointWithLocation:(CLLocationCoordinate2D)location{
    PVWayPointModel *onePoint,*twoPoint,*threePoint,*fourPoint;
    
    CLLocationCoordinate2D locationOne,locationTwo,locationThree,locationFour;
    locationOne.longitude = location.longitude + (PerMeter_Longitude * PointDistanceMeter);
    locationOne.latitude = location.latitude;
    
    self.pointOneLongitudeLabel.text = [NSString stringWithFormat:@"%f",locationOne.longitude];
    self.pointOneLatitudeLabel.text = [NSString stringWithFormat:@"%f",locationOne.latitude];
    
    locationTwo.longitude = location.longitude + (PerMeter_Longitude * PointDistanceMeter);
    locationTwo.latitude = location.longitude + (PerMeter_Longitude * PointDistanceMeter);
    
    self.pointTwoLongitudeLabel.text = [NSString stringWithFormat:@"%f",locationTwo.longitude];
    self.pointTwoLatitudeLabel.text = [NSString stringWithFormat:@"%f",locationTwo.latitude];
    
    locationThree.longitude = location.longitude;
    locationThree.latitude = location.longitude + (PerMeter_Longitude * PointDistanceMeter);
    
    self.pointThreeLongitudeLabel.text = [NSString stringWithFormat:@"%f",locationThree.longitude];
    self.pointThreeLatitudeLabel.text = [NSString stringWithFormat:@"%f",locationThree.latitude];
    
    locationFour = location;
    
    self.pointFourLongitudeLabel.text = [NSString stringWithFormat:@"%f",location.longitude];
    self.pointFourLatitudeLabel.text = [NSString stringWithFormat:@"%f",location.latitude];
    
    onePoint.touchMapCoordinate = locationOne;
    onePoint.height = WayPointHeight;
    onePoint.stayTime = WayPointStayTime;
    
    twoPoint.touchMapCoordinate = locationTwo;
    twoPoint.height = WayPointHeight;
    twoPoint.stayTime = WayPointStayTime;
    
    threePoint.touchMapCoordinate = locationThree;
    threePoint.height = WayPointHeight;
    threePoint.stayTime = WayPointStayTime;
    
    fourPoint.touchMapCoordinate = locationFour;
    fourPoint.height = WayPointHeight;
    fourPoint.stayTime = WayPointStayTime;
    
    self.locationOne = onePoint;
    self.locationTwo = twoPoint;
    self.locationThree = threePoint;
    self.locationFour = fourPoint;
    
    [[PVNavigation shareNavigation] addLocationWayPoints:@[_locationOne,_locationTwo,_locationThree,_locationFour]];
}

- (IBAction)didClickToControlNavigating:(UIButton *)sender {
    if ([PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_MANUAL || [PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_ALTCTL || [PVFlightHelper shareHelper].flightMode == PVSDK_Mode_Changed_POSCTL) {
        if (_generateWaypoint) {
            if ([PVProductHelper shareHelper].connectState == PVConnectState_Connection_Connected) {
                
                [self wayPointControlWithToStart:!self.isNavigationStart];
                
                if (self.isNavigationStart) {
                    [sender setTitle:@"Start navigating" forState:UIControlStateNormal];
                    self.isNavigationStart = NO;
                }else{
                    [sender setTitle:@"Stop navigating" forState:UIControlStateNormal];
                    self.isNavigationStart = YES;
                }

            }else{
                ShowResult(@"飞机未连接！");
            }
        }else{
            ShowResult(@"请生成航点！");
        }
    }else{
        self.generateWaypoint = NO;
        ShowResult(@"飞机当前模式不满足航点飞行要求，请重新生成航点！");
    }
}

- (void)wayPointControlWithToStart:(BOOL)toStart{
    if (toStart) {
        [[PVNavigation shareNavigation] startToAutoMission];
    }else{
        [[PVNavigation shareNavigation] setLastMode];
    }
}

-(BOOL)navigationShouldPopOnBackButton{
    if (_isNavigationStart) {
        [[PVNavigation shareNavigation] setLastMode];
        return NO;
    }else{
        return YES;
    }
}

-(void)dealloc{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"NOTIFICATION_WayPointViewController_UpdateLocation" object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"NOTIFICATION_WayPointViewController_UpdateWayPointState" object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"NOTIFICATION_WayPointViewController_SendWayPointResult" object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"NOTIFICATION_WayPointViewController_ChangeLastMode" object:nil];
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
