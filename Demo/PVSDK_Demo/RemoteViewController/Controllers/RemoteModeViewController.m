//
//  RemoteModeViewController.m
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/12/2.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "RemoteModeViewController.h"

@interface RemoteModeViewController ()
<
UITableViewDelegate,UITableViewDataSource
>
@property (weak, nonatomic) IBOutlet UITableView *listView;
@property (nonatomic, strong) PVRemoteController *remoteController;
@property (nonatomic, strong) NSArray *items;

@end

@implementation RemoteModeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self initData];
    [self configManager];
}

- (void)initData{
    self.items = @[@"美国手",@"日本手"];
}
- (void)configManager{
    self.remoteController = [PVRemoteController new];
}

//  TODO: [Command] 设置遥控器模式
- (void)setRCModeWithRemoteMode:(PVRCMode)mode
{
    WEAKSELF;
    [self.remoteController setRCMode:mode withCompletion:^(NSError * _Nullable error) {
        STRONGSELF;
        if (error == nil) {
            [strongSelf.navigationController popViewControllerAnimated:YES];
        }
    }];
}


#pragma mark - UITableViewDelegate,UITableViewDataSource
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.items.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *CellIdentifier = @"";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = self.items[indexPath.row];
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    //  设置遥控器模式
    if (indexPath.row == 0) {
        [self setRCModeWithRemoteMode:PVRCModeUSA];
    }else{
        [self setRCModeWithRemoteMode:PVRCModeJapan];
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
