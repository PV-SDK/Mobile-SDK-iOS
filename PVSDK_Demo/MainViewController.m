//
//  MainViewController.m
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/22.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#define isTest 0

#import "MainViewController.h"
#import <PVSDK/PVSDK.h>

#import "FlightViewController.h"
#import "MountViewController.h"

typedef enum : NSUInteger {
    FlightConnectStateDisConnected  = 0,    //  断开连接
    FlightConnectStateConnected     = 1     //  已连接
} FlightConnectState;

@interface MainViewController ()
<
PVFlightControllerDelegate,
UITableViewDelegate,UITableViewDataSource
>
{
    NSArray *titleArray;
}
@property (weak, nonatomic) IBOutlet UITableView *listView;

@property (nonatomic, assign) FlightConnectState connectState;

@property (nonatomic, strong) PVFlightController *flightController;

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    //  初始化数据源
    [self initData];
    
    //  初始化飞机控制器
    [self initFlightController];
    
    //  连接飞机
    [self connectFlight];
}

#pragma mark - 初始化数据源
- (void)initData{
    titleArray = @[@"FlightViewController",@"MountViewController"];
}

#pragma mark - 初始化飞机控制器
- (void)initFlightController{
    self.flightController = [PVFlightController new];
    self.flightController.delegate = self;
}

#pragma mark - Connect Flight
- (void)connectFlight{
    if (self.connectState == FlightConnectStateDisConnected) {
        [self.flightController startConnectFlight];
    }
}

#pragma mark - Disconnect Flight
- (void)disconnectFlight{
    if (self.connectState == FlightConnectStateConnected) {
        [self.flightController stopConnectFlight];
    }
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
        self.connectState = FlightConnectStateConnected;
        NSLog(@"已连接");
    } else {
        self.connectState = FlightConnectStateDisConnected;
        NSLog(@"未连接");
    }
}
#pragma mark - UITableViewDelegate,UITableViewDataSource
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return 2;
}
-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section{
    return 0.01;
}
-(CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section{
    return 0.01;
}
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 44;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *CellIdentifier = @"";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc]
                initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = titleArray[indexPath.row];
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    if (self.connectState == FlightConnectStateDisConnected) {
        //  未连接
        return;
    }
    static NSString *PushToFirstVCIdentifier = @"ShowFirstViewController";
    static NSString *PushToSecondVCIdentifier = @"ShowSecondViewController";
    switch (indexPath.row) {
        case 0:
        {
            [self performSegueWithIdentifier:PushToFirstVCIdentifier sender:self];
        }
            break;
        case 1:
        {
            [self performSegueWithIdentifier:PushToSecondVCIdentifier sender:self];
        }
            break;
            
        default:
            break;
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
