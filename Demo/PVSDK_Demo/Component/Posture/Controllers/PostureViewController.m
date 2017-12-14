//
//  PostureViewController.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "PostureViewController.h"

@interface PostureViewController ()
<
UITableViewDelegate,UITableViewDataSource
>

@property (weak, nonatomic) IBOutlet UITableView *listView;

@property (nonatomic, strong) NSArray *items;
@property (nonatomic, strong) NSArray *values;


@end

@implementation PostureViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self initDataSource];
}

- (void)initDataSource{
    //  上升速度
    self.items = @[@"X速度",@"Y速度",@"Z速度",@"加速度",@"俯仰",@"横滚",@"航向角度",@"角速度",@"飞机对地高度",@"海拔高度"];
    self.values = @[@"需要确定",@"需要确定",@"需要确定",@"需要确定",@"pitchSpeed",@"rollSpeed",@"yawSpeed",@"需要确定",@"altitude",@"groundHeight"];
}

#pragma mark - UITableViewDelegate,UITableViewDataSource
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return _items.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *CellIdentifier = @"";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = _items[indexPath.row];
    cell.detailTextLabel.text = _values[indexPath.row];
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
