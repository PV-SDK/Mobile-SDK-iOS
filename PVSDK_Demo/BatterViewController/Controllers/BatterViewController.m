//
//  BatterViewController.m
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/12/2.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "BatterViewController.h"
#import <PVSDK/PVSDK.h>

@interface BatterViewController ()
<
UITableViewDelegate,UITableViewDataSource
>

@property (weak, nonatomic) IBOutlet UITableView *listView;
@property (nonatomic, strong) PVBattery *batteryManager;

@property (nonatomic, strong) NSArray *items;
@property (nonatomic, strong) NSMutableArray *values;

@end

@implementation BatterViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self configManager];
}

- (void)initData{
    self.items = @[@"第一节电芯电压",@"第二节电芯电压",@"第三节电芯电压",@"第四节电芯电压",@"循环次数",@"电池总容量",@"电池温度",@"电池当前剩余电量"];
    self.values = [@[@"",@"",@"",@"",@"",@"",@"",@""] mutableCopy];
}
- (void)configManager{
    self.batteryManager = [PVBattery new];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //  获取电池信息
        [self getBatteryInfo];
    });
}

//TODO: [Command] 获取电池信息
- (void)getBatteryInfo
{
    [self.batteryManager getSmartBatteryStatusWithCompletion:^(PVBatteryStatus batteryStatus, NSError *error) {
        if (error == nil) {
            [self.values replaceObjectAtIndex:0 withObject:[NSString stringWithFormat:@"%.3fV",batteryStatus.firstCellVol * 0.001f]];
            [self.values replaceObjectAtIndex:1 withObject:[NSString stringWithFormat:@"%.3fV",batteryStatus.sencondCellVol * 0.001f]];
            [self.values replaceObjectAtIndex:2 withObject:[NSString stringWithFormat:@"%.3fV",batteryStatus.thirdCellVol * 0.001f]];
            [self.values replaceObjectAtIndex:3 withObject:[NSString stringWithFormat:@"%.3fV",batteryStatus.forthCellVol * 0.001f]];
            [self.values replaceObjectAtIndex:4 withObject:[NSString stringWithFormat:@"%d次",batteryStatus.cycleTimes]];
            [self.values replaceObjectAtIndex:5 withObject:[NSString stringWithFormat:@"%.3fA·h",batteryStatus.totalCapacity / 3600]];
            [self.values replaceObjectAtIndex:6 withObject:[NSString stringWithFormat:@"%.1f℃",batteryStatus.temperature]];
            [self.values replaceObjectAtIndex:7 withObject:[NSString stringWithFormat:@"%d%%",batteryStatus.battery_remaining]];
            [self.listView reloadData];
        }
    }];
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
