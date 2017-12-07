//
//  RemoteViewController.m
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/12/2.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "RemoteViewController.h"
#import <PVSDK/PVSDK.h>
#import "RemoteModeViewController.h"

@interface RemoteViewController ()
<
UITableViewDelegate,UITableViewDataSource
//PVRemoteControllerDelegate
>

@property (weak, nonatomic) IBOutlet UITableView *listView;
@property (nonatomic, strong) PVRemoteController *remoteController;

@property (nonatomic, strong) NSArray *items;
@property (nonatomic, strong) NSMutableArray *values;

@end

@implementation RemoteViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = @"遥控器";
    
    [self initData];
    [self configManager];
}
- (void)initData{
    self.items = @[@"遥控器模式"];
    self.values = [@[@""] mutableCopy];
}
- (void)configManager{
    self.remoteController = [PVRemoteController new];
    //    self.remoteController.delegate = self;
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //  获取遥控器模式
        [self getRemoteMode];
    });
}

#pragma mark - 检查飞机连接状态
- (BOOL)checkFlightConnected{
    if ([PVFlightController new].flightConnectState == PVFlightConnectStateConnected || [PVFlightController new].flightConnectState == PVFlightConnectStateHeartTimeoutReply) {
        return YES;
    }else{
        return NO;
    }
}

//TODO: [Command] 获取遥控器模式
- (void)getRemoteMode
{
    if ([self checkFlightConnected]) {
        [self.remoteController getRCModeWithComplection:^(PVRCMode rcMode, NSError * _Nullable error) {
            if (error == nil) {
                if (rcMode == PVRCModeUSA) {
                    [self.values replaceObjectAtIndex:0 withObject:@"美国手"];
                }else if (rcMode == PVRCModeJapan) {
                    [self.values replaceObjectAtIndex:0 withObject:@"日本手"];
                }
                [self.listView reloadData];
            }
        }];
    }
}

#pragma mark - UITableViewDelegate,UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.items.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *CellIdentifier = @"";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.detailTextLabel.textColor = [UIColor blueColor];
    cell.textLabel.text = self.items[indexPath.row];
    cell.detailTextLabel.text = self.values[indexPath.row];
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    if (![self.values[0] isEqualToString:@""]) {
        [self performSegueWithIdentifier:@"PushToSetRemoteModeVC" sender:self];
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"ShowCameraSettingValueVC"]) {
        RemoteModeViewController *remoteModeVC = [RemoteModeViewController new];
        remoteModeVC.remoteMode = [self.values[0] integerValue];
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
