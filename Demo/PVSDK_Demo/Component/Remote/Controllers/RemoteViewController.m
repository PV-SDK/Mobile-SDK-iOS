//
//  RemoteViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "RemoteViewController.h"
#import <PVSDK/PVSDK.h>
#import "RemoteModeViewController.h"

@interface RemoteViewController ()
<
UITableViewDelegate,UITableViewDataSource
>

@property (weak, nonatomic) IBOutlet UITableView *listView;
@property (nonatomic, strong) PVFlightRemote *flightRemoteManager;

@property (nonatomic, copy) NSArray *items;
@property (nonatomic, strong) NSMutableArray *values;

@end

@implementation RemoteViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = @"Remote";
    
    [self initData];
    [self configManager];
}
- (void)initData{
    self.items = @[@"Remote Mode"];
    self.values = [@[@""] mutableCopy];
}
- (void)configManager{
    self.flightRemoteManager = [ComponentHelper fetchFlightRemote];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //  Get remote mode
        [self getRemoteMode];
    });
}

#pragma mark - Check the airplant connect status.
- (BOOL)checkFlightConnected{
    if ([ComponentHelper fetchProductHelper].connectState == PVConnectState_Connection_Connected || [ComponentHelper fetchProductHelper].connectState == PVConnectState_Connection_Timeout_Replay) {
        return YES;
    }else{
        return NO;
    }
}

//TODO: [Command] Get remote mode
- (void)getRemoteMode
{
    if ([self checkFlightConnected]) {
        [self.flightRemoteManager getRemoteModeWithComplection:^(PVFlightRemoteMode remoteMode, NSError * _Nullable error) {
            if (error == nil) {
                if (remoteMode == PVFlightRemoteModeUSA) {
                    [self.values replaceObjectAtIndex:0 withObject:@"American Hand"];
                }else if (remoteMode == PVFlightRemoteModeJapan) {
                    [self.values replaceObjectAtIndex:0 withObject:@"Japan Hand"];
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
        remoteModeVC.flightRemoteMode = [self.values[0] integerValue];
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
