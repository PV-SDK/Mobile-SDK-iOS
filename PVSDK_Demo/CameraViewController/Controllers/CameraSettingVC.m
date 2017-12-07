//
//  CameraSettingVC.m
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/25.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "CameraSettingVC.h"
#import "CameraSettingParameterVC.h"

@interface CameraSettingVC ()
{
    NSInteger selectIndex;
}

@property (nonatomic, strong) NSArray *titles;

@end

@implementation CameraSettingVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self initData];
}

- (void)initData{
    self.titles = @[@"光圈设置", @"拍摄设置", @"通用设置"];
}

- (void)setShootState:(CameraSettingShootState_)shootState{
    _shootState = shootState;
}

#pragma mark - UITableViewDelegate,UITableViewDataSource
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.titles.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *CellIdentifier = @"";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = _titles[indexPath.row];
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    selectIndex = indexPath.row;
    [self performSegueWithIdentifier:@"ShowCameraSettingParameterVC" sender:self];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"ShowCameraSettingParameterVC"]) {
        CameraSettingParameterVC *parameterVC = segue.destinationViewController;
        [parameterVC configWithType:selectIndex State:(int)_shootState];
        parameterVC.title = self.titles[selectIndex];
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
