//
//  WayPointControlViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "WayPointControlViewController.h"
#import <PVSDK/PVSDK.h>
#import "ComponentHelper.h"
#import <CoreLocation/CoreLocation.h>
#import "UIViewController+BackButtonHandler.h"

////////////////////////////////////////////////////////////////////////
/// Longitude（east west orientation）1m：360°/31544206M=1.141255544679108e-5=0.00001141
/// Latitude（north and south orientation）1m：360°/40030173M=8.993216192195822e-6=0.00000899
////////////////////////////////////////////////////////////////////////
#define PerMeter_Longitude 0.00001141
#define PerMeter_Latitude 0.00000899

#define PointDistanceMeter 20   //  The straight line distance between two destinations is not recommended for more than 900m.

#define WayPointStayTime 5.0f       //  Unit s
#define WayPointHeight 20.0f        //  Unit m

#import <PVSDK/PVSDK.h>

@interface WayPointControlViewController ()

@property (nonatomic, strong) PVNavigation *navigationManager;

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
    [self configManager];
    //  Notification about location updating
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateLocation:) name:@"NOTIFICATION_WayPointViewController_UpdateLocation" object:nil];
    //  Notifications of sending waypoint results
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sendWayPointResult:) name:@"NOTIFICATION_WayPointViewController_SendWayPointResult" object:nil];
    //  Notification about switching to the last mode
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changeToLastMode:) name:@"NOTIFICATION_WayPointViewController_ChangeLastMode" object:nil];
}

- (void)configManager{
    self.isNavigationStart = NO;
    self.navigationManager = [ComponentHelper fetchNavigation];
}
//TODO: Notification about location updating
- (void)updateLocation:(NSNotification *)notifi{
    CLLocationCoordinate2D location;
    location.longitude = [[notifi userInfo][@"longitude"] doubleValue];
    location.latitude = [[notifi userInfo][@"latitude"] doubleValue];
    
    self.currentLocation = location;
    
    self.eyeCurrentLongitudeLabel.text = [NSString stringWithFormat:@"%f",location.longitude];
    self.eyeCurrentLatitudeLabel.text = [NSString stringWithFormat:@"%f",location.latitude];
}
//TODO: Notifications of sending waypoint results
- (void)sendWayPointResult:(NSNotification *)notifi{
    self.generateWaypoint = [[notifi userInfo][@"result"] isEqualToString:@"Success"] ? YES : NO;
}
//TODO: Notification about switching to the last mode
- (void)changeToLastMode:(NSNotification *)notifi{
    
}

#pragma mark - Generate Way Point Method
- (IBAction)didClickToGenerateWaypoint:(UIButton *)sender {
    [self generateWaypointWithLocation:_currentLocation];
}
#pragma mark - Generate Way Point Location
- (void)generateWaypointWithLocation:(CLLocationCoordinate2D)location{
    PVWayPointModel *onePoint = [PVWayPointModel new];
    PVWayPointModel *twoPoint = [PVWayPointModel new];
    PVWayPointModel *threePoint = [PVWayPointModel new];
    PVWayPointModel *fourPoint = [PVWayPointModel new];
    
    //  [Warning!!!]The straight line distance between two destinations is not recommended for more than 900m.!!!
    
    CLLocationCoordinate2D locationOne,locationTwo,locationThree,locationFour;
    locationOne.longitude = location.longitude + (PerMeter_Longitude * PointDistanceMeter);
    locationOne.latitude = location.latitude;
    
    self.pointOneLongitudeLabel.text = [NSString stringWithFormat:@"%f",locationOne.longitude];
    self.pointOneLatitudeLabel.text = [NSString stringWithFormat:@"%f",locationOne.latitude];
    
    locationTwo.longitude = location.longitude + (PerMeter_Longitude * PointDistanceMeter);
    locationTwo.latitude = location.latitude + (PerMeter_Latitude * PointDistanceMeter);
    
    self.pointTwoLongitudeLabel.text = [NSString stringWithFormat:@"%f",locationTwo.longitude];
    self.pointTwoLatitudeLabel.text = [NSString stringWithFormat:@"%f",locationTwo.latitude];
    
    locationThree.longitude = location.longitude;
    locationThree.latitude = location.latitude + (PerMeter_Latitude * PointDistanceMeter);
    
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
    
    [self.navigationManager addLocationWayPoints:@[_locationOne,_locationTwo,_locationThree,_locationFour]];
}

- (IBAction)didClickToControlNavigating:(UIButton *)sender {
    if (self.isNavigationStart) {
        if ([sender.titleLabel.text isEqualToString:@"Stop navigating"]) {
            [self wayPointControlWithToStart:!self.isNavigationStart];
            [sender setTitle:@"Start navigating" forState:UIControlStateNormal];
        }
    }else{
        if (_generateWaypoint) {
            if ([ComponentHelper fetchFlightHelper].flightMode == PVSDK_Mode_Changed_Manual || [ComponentHelper fetchFlightHelper].flightMode == PVSDK_Mode_Changed_Altctl || [ComponentHelper fetchFlightHelper].flightMode == PVSDK_Mode_Changed_Posctl) {
                if ([sender.titleLabel.text isEqualToString:@"Start navigating"]) {
                    [self wayPointControlWithToStart:!self.isNavigationStart];
                    [sender setTitle:@"Stop navigating" forState:UIControlStateNormal];
                }
            }else{
                [self.navigationManager setLastMode];
                ShowResult(@"Not three modes of remote control!");
            }
        }else{
            ShowResult(@"Please set the waypoint!");
        }
    }
}

- (void)wayPointControlWithToStart:(BOOL)toStart{
    if (toStart) {
        [self.navigationManager startToAutoMission];
        _isNavigationStart = YES;
    }else{
        [self.navigationManager setLastMode];
        _isNavigationStart = NO;
    }
}

-(BOOL)navigationShouldPopOnBackButton{
    if (_isNavigationStart) {
        ShowResult(@"Please finish the flight first!");
        return NO;
    }else{
        return YES;
    }
}

-(void)dealloc{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"NOTIFICATION_WayPointViewController_UpdateLocation" object:nil];
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
