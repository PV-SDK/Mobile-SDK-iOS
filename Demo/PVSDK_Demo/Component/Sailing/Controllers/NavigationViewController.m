//
//  NavigationViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import "NavigationViewController.h"
#import "ComponentHelper.h"
#import "WayPointControlViewController.h"

@interface NavigationViewController ()
<
UITableViewDelegate,UITableViewDataSource,
PVNavigationDelegate,
PVLocationDelegate
>

@property (nonatomic, strong) PVNavigation *navigationManager;
@property (nonatomic, strong) PVLocation *locationManager;

@property (weak, nonatomic) IBOutlet UITableView *infoListView;
@property (weak, nonatomic) IBOutlet UITableView *controlListView;

@property (nonatomic, copy) NSArray *info_items;
@property (nonatomic, copy) NSArray *control_items;

@property (nonatomic, strong) NSMutableArray *info_values;

@end

@implementation NavigationViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self initData];
    [self configManager];
}

- (void)initData{
    self.info_items = @[@"经度",@"纬度",@"卫星颗数",@"俯仰角度",@"横滚角度",@"航向角度",@"大地坐标X轴速度",@"大地坐标Y轴速度",@"大地坐标Z轴速度",@"海拔",@"对地高度"];
    self.control_items = @[@"Way point of control",@"Automatic return"];
    self.info_values = [@[@"",@"",@"",@"",@"",@"",@"",@"",@"",@"",@""] mutableCopy];
//    self.info_values = [@[@"114.234513000",
//                          @"40.2312351200",
//                          @"15 moons",
//                          @"+3°",
//                          @"-5°",
//                          @"+23°",
//                          @"+2 m/s",@"+1 m/s",@"-3 m/s",
//                          @"327 m",@"298 m"
//                          ] mutableCopy];
}

- (void)configManager{
    self.navigationManager = [ComponentHelper fetchNavigation];
    self.navigationManager.delegate = self;
    
    self.locationManager = [ComponentHelper fetchLocation];
    self.locationManager.delegate = self;
}

#pragma mark - PVNavigationDelegate
-(void)pv_navigation:(PVNavigation *)navigation UpdateFlightAttitudeWithHelper:(PVProductHelper *)helper{
    PVFlightHelper *flightHelper = (PVFlightHelper *)helper;
    NSLog(@"Pitch:%f",flightHelper.attitude.pitch);
    NSLog(@"Roll:%f",flightHelper.attitude.roll);
    NSLog(@"Yaw:%f",flightHelper.attitude.yaw);
    
    [_info_values replaceObjectAtIndex:3 withObject:[NSString stringWithFormat:@"%f°",flightHelper.attitude.pitch]];
    [_info_values replaceObjectAtIndex:4 withObject:[NSString stringWithFormat:@"%f°",flightHelper.attitude.roll]];
    [_info_values replaceObjectAtIndex:5 withObject:[NSString stringWithFormat:@"%f°",flightHelper.attitude.yaw]];
    
    [_infoListView reloadData];
}
-(void)pv_navigation:(PVNavigation *)navigation SendWayPointState:(PVWayPointSendState)sendState{
    if (sendState == PVWayPointSendState_Success) {
        if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[WayPointControlViewController class]]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"NOTIFICATION_WayPointViewController_SendWayPointResult" object:nil userInfo:@{@"result":@"Success"}];
        }
    }else{
        if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[WayPointControlViewController class]]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"NOTIFICATION_WayPointViewController_SendWayPointResult" object:nil userInfo:@{@"result":@"Failed"}];
        }
    }
}
-(void)pv_navigation:(PVNavigation *)navigation UpdateWayPointCurrentPoint:(int)currentPoint{
    
    if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[WayPointControlViewController class]]) {
        [[NSNotificationCenter defaultCenter] postNotificationName:@"NOTIFICATION_WayPointViewController_UpdateWayPointState" object:nil userInfo:@{@"currentPoint":[NSString stringWithFormat:@"%d",currentPoint],@"reachedPoint":@""}];
    }
}
-(void)pv_navigation:(PVNavigation *)navigation UpdateWayPointReachedPoint:(int)reachedPoint{
    if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[WayPointControlViewController class]]) {
        [[NSNotificationCenter defaultCenter] postNotificationName:@"NOTIFICATION_WayPointViewController_UpdateWayPointState" object:nil userInfo:@{@"currentPoint":@"",@"reachedPoint":[NSString stringWithFormat:@"%d",reachedPoint]}];
    }
}
-(void)pv_navigation:(PVNavigation *)navigation ChangeLastModeResult:(BOOL)result{
    if (result) {
        if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[WayPointControlViewController class]]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"NOTIFICATION_WayPointViewController_ChangeLastMode" object:nil userInfo:@{@"result":@"Success"}];
        }
    }else{
        if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[WayPointControlViewController class]]) {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"NOTIFICATION_WayPointViewController_ChangeLastMode" object:nil userInfo:@{@"result":@"Failed"}];
        }
    }
}

#pragma mark - PVLocationDelegate
-(void)pv_location:(PVLocation *)location UpdateFlightLocationWithHelper:(PVProductHelper *)helper{
    PVFlightHelper *flightHelper = (PVFlightHelper *)helper;
    NSLog(@"Latitude:%f",flightHelper.aircraftLocation.latitude);
    NSLog(@"Longitude:%f",flightHelper.aircraftLocation.longitude);
    
    NSDictionary *locationDic = @{@"longitude":[NSString stringWithFormat:@"%f",flightHelper.aircraftLocation.longitude],
                                  @"latitude":[NSString stringWithFormat:@"%f",flightHelper.aircraftLocation.latitude]
                                  };
    
    if ([[self.navigationController.viewControllers lastObject] isKindOfClass:[WayPointControlViewController class]]) {
        [[NSNotificationCenter defaultCenter] postNotificationName:@"NOTIFICATION_WayPointViewController_UpdateLocation" object:nil userInfo:locationDic];
    }
    
    NSLog(@"SatelliteCount:%d",flightHelper.satelliteCount);
    
    NSLog(@"X-Speed:%f",flightHelper.xSpeed);
    NSLog(@"Y-Speed:%f",flightHelper.ySpeed);
    NSLog(@"Z-Speed:%f",flightHelper.zSpeed);

    NSLog(@"Altitude:%f",flightHelper.altitude);
    NSLog(@"GroundHeight:%f",flightHelper.groundHeight);

    [_info_values replaceObjectAtIndex:0 withObject:[NSString stringWithFormat:@"%f",flightHelper.aircraftLocation.latitude]];
    [_info_values replaceObjectAtIndex:1 withObject:[NSString stringWithFormat:@"%f",flightHelper.aircraftLocation.longitude]];
    
    [_info_values replaceObjectAtIndex:2 withObject:[NSString stringWithFormat:@"%d moons",flightHelper.satelliteCount]];
    
    [_info_values replaceObjectAtIndex:6 withObject:[NSString stringWithFormat:@"%f m/s",flightHelper.xSpeed]];
    [_info_values replaceObjectAtIndex:7 withObject:[NSString stringWithFormat:@"%f m/s",flightHelper.ySpeed]];
    [_info_values replaceObjectAtIndex:8 withObject:[NSString stringWithFormat:@"%f m/s",flightHelper.zSpeed]];
    
    [_info_values replaceObjectAtIndex:9 withObject:[NSString stringWithFormat:@"%f m",flightHelper.altitude]];
    [_info_values replaceObjectAtIndex:10 withObject:[NSString stringWithFormat:@"%f m",flightHelper.groundHeight]];
    
    [_infoListView reloadData];
}

#pragma mark - UITableViewDelegate,UITableViewDataSource
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    if (tableView.tag == 1001) {
        return _info_items.count;
    }else if (tableView.tag == 1002) {
        return _control_items.count;
    }
    return 0;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    if (tableView.tag == 1001) {
        static NSString *CellIdentifier = @"InfoListViewCell";
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
        if (cell == nil) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
        }
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        cell.textLabel.text = _info_items[indexPath.row];
        cell.detailTextLabel.text = _info_values[indexPath.row];
        return cell;
    }else if (tableView.tag == 1002){
        static NSString *CellIdentifier = @"ControlListViewCell";
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
        if (cell == nil) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
        }
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        cell.textLabel.text = _control_items[indexPath.row];
        return cell;
    }
    return nil;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    if (tableView.tag == 1002) {
        switch (indexPath.row) {
            case 0: //  航点控制
            {
                [self performSegueWithIdentifier:@"PushToWayPointControlViewController" sender:self];
            }
                break;
            case 1: //  自动返航
            {
                [self.navigationManager autoReturnToLand];
            }
                break;
            default:
                break;
        }
    }
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
