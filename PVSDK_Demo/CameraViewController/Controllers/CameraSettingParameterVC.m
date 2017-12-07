//
//  CameraSettingParameterVC.m
//  PVSDK_Demo
//
//  Created by Gavin.Guo on 2017/11/25.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "CameraSettingParameterVC.h"
#import "CameraSettingValueVC.h"

#import <PVSDK/PVSDK.h>

@interface CameraSettingParameterVC ()
<
UITableViewDelegate,UITableViewDataSource
>
{
    NSInteger selectIndex;
    CameraSettingType parameterType;
    CameraSetting_CameraState cameraState;
    
    NSInteger whiteBalanceValue;
}

@property (weak, nonatomic) IBOutlet UITableView *listView;
@property (nonatomic, strong) NSArray *parameters;
@property (nonatomic, strong) NSArray *values;
@property (nonatomic, strong) NSMutableArray *currentValues;

@property (nonatomic, strong) PVCamera *cameraManager;

@end

@implementation CameraSettingParameterVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
}

- (void)initData{
    whiteBalanceValue = -200;
}

- (void)configWithType:(CameraSettingType)type State:(CameraSetting_CameraState)state{
    parameterType = type;
    cameraState = state;
    
    self.cameraManager = [PVCamera new];
    
    [self configDataWithCameraType:type];
}

- (void)configDataWithCameraType:(CameraSettingType)type{
    [self.cameraManager getAllCameraSettingWithCompletion:nil];
    WEAKSELF;
    if (type == CameraSettingTypeAperture) {
        self.parameters = @[@"ISO", @"光圈大小", @"EV", @"拍照快门速度", @"摄像快门速度"];
        self.currentValues = [NSMutableArray arrayWithArray:@[@"",@"",@"",@"",@""]];
        //  获取相机ISO值
        [self.cameraManager getEyeISOWithCompletion:^(PVEyeCameraISO iso, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:0 withObject:[self getCurrentValueWithType:type Row:0 Index:iso - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        //  获取相机光圈大小
        [self.cameraManager getEyePVCameraApertureWithCompletion:^(PVCameraAperture aperture, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:1 withObject:[self getCurrentValueWithType:type Row:1 Index:aperture - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        //  获取EV值
        [self.cameraManager getEyeExposureWithCompletion:^(NSInteger exposure, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                if (exposure > 96) {
                    exposure = 96;
                }
                if (exposure < -96) {
                    exposure = -96;
                }
                [strongSelf.currentValues replaceObjectAtIndex:2 withObject:[NSString stringWithFormat:@"%.1f",(long)exposure/32.0]];
                [strongSelf.listView reloadData];
            }
        }];
        //  获取拍照快门速度
        [self.cameraManager getEyeCameraPhotoShutterSpeedWithCompletion:^(PVCameraPhotoShutterSpeed shutterSpeed, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:3 withObject:[self getCurrentValueWithType:type Row:3 Index:shutterSpeed - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        //  获取摄像快门速度
        [self.cameraManager getEyeCameraVideoShutterSpeedWithCompletion:^(PVCameraVideoShutterSpeed videoShutterSpeed, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:4 withObject:[self getCurrentValueWithType:type Row:4 Index:videoShutterSpeed - 51]];
                [strongSelf.listView reloadData];
            }
        }];
    }else if (type == CameraSettingTypeShoot) {
        if (cameraState == CameraSetting_CameraStateTakePhoto) {
            self.parameters = @[@"相机模式",@"连拍速度",@"定时连拍",@"照片尺寸",@"照片质量"];
            self.currentValues = [NSMutableArray arrayWithArray:@[@"",@"",@"",@"",@""]];
            //  获取相机模式
            [self.cameraManager getEyeCameraModeWithCompletion:^(PVEyeCameraMode cameraMode, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    [strongSelf.currentValues replaceObjectAtIndex:0 withObject:[self getCurrentValueWithType:type Row:0 Index:cameraMode - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
            //  获取连拍速度
            [self.cameraManager getEyeCameraContinuousShootSpeedWithCompletion:^(PVEyeCameraContinuousShootSpeed shootSpeed, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    if ([strongSelf.currentValues[0] isEqualToString:@"Single"]) {
                        return;
                    }
                    if (shootSpeed >= 54) {
                        [strongSelf.currentValues replaceObjectAtIndex:1 withObject:@"高速"];
                    } else {
                        [strongSelf.currentValues replaceObjectAtIndex:1 withObject:[self getCurrentValueWithType:type Row:1 Index:shootSpeed - 51]];
                    }
                    [strongSelf.listView reloadData];
                }
            }];
            //  定时连拍
            [self.cameraManager getTakePhotoDelyTimeWithCompletion:^(NSInteger time, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    if (time < 1) {
                        time = 1;
                    }
                    if (time > 60) {
                        time = 60;
                    }
                    [strongSelf.currentValues replaceObjectAtIndex:2 withObject:[NSString stringWithFormat:@"%ld min",(long)time]];
                    [strongSelf.listView reloadData];
                }
            }];
            //  照片尺寸
            [self.cameraManager getEyeCameraPhotoSizeWithCompletion:^(PVCameraPhotoSize photoSize, NSError * _Nullable error) {
                if (error == nil) {
                    STRONGSELF;
                    [strongSelf.currentValues replaceObjectAtIndex:3 withObject:[self getCurrentValueWithType:type Row:3 Index:photoSize - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
            //  照片质量
            [self.cameraManager getEyeCameraPhotoQualityWithCompletion:^(PVEyeCameraPhotoQuality photoQuality, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    [strongSelf.currentValues replaceObjectAtIndex:4 withObject:[self getCurrentValueWithType:type Row:4 Index:photoQuality - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
        }else if (cameraState == CameraSetting_CameraStateRecord) {
            self.parameters = @[@"录像分辨率"];
            self.currentValues = [NSMutableArray arrayWithArray:@[@""]];
            //  获取录像分辨率
            [self.cameraManager getEyeCameraVideoSizeWithCompletion:^(PVCameraVideoSize videoSize, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    [strongSelf.currentValues replaceObjectAtIndex:0 withObject:[self getCurrentValueWithType:type Row:0 Index:videoSize - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
        }
    }else if (type == CameraSettingTypeGeneral) {
        self.parameters = @[@"白平衡模式",@"白平衡",@"图像亮度",@"图像饱和度",@"图像对比度",@"测光模式",@"AF模式",@"OSD开关",@"图像锐度",@"剩余拍照张数",@"格式化内存卡",@"恢复出厂设置"];
        self.currentValues = [NSMutableArray arrayWithArray:@[@"",@"",@"",@"",@"",@"",@"",@"",@"",@"",@"",@""]];
        //  获取相机白平衡模式
        [self.cameraManager getEyeWhiteBalanceModeWithCompletion:^(PVEyeCameraWhiteBalanceMode whiteBalanceMode, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:0 withObject:[self getCurrentValueWithType:type Row:0 Index:whiteBalanceMode - 51]];
                if (whiteBalanceMode == 51) {
                    [strongSelf.currentValues replaceObjectAtIndex:1 withObject:@""];
                }else{
                    if (whiteBalanceValue != 200) {
                        [strongSelf.currentValues replaceObjectAtIndex:1 withObject:[NSString stringWithFormat:@"%ld",(long)whiteBalanceValue]];
                    }
                }
                [strongSelf.listView reloadData];
            }
        }];
        //获取白平衡值
        [self.cameraManager getEyeWhiteBalanceWithCompletion:^(NSInteger whiteBalance, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                if (whiteBalance < -100) {
                    whiteBalance = -100;
                }
                if (whiteBalance > 100) {
                    whiteBalance = 100;
                }
                
                whiteBalanceValue = whiteBalance;
                
                if ([strongSelf.currentValues[0] isEqualToString:@"Auto"]) {
                    return;
                }
                [strongSelf.currentValues replaceObjectAtIndex:1 withObject:[NSString stringWithFormat:@"%ld",(long)whiteBalance]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //获取图像亮度
        [self.cameraManager getImageBrightnessWithCompletion:^(NSInteger brightness, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:2 withObject:[NSString stringWithFormat:@"%ld",(long)brightness]];
                [strongSelf.listView reloadData];
            }
        }];
        //获取图像饱和度
        [self.cameraManager getImageSaturationWithCompletion:^(NSInteger saturation, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:3 withObject:[NSString stringWithFormat:@"%ld",(long)saturation]];
                [strongSelf.listView reloadData];
            }
        }];
        //获取图像对比度
        [self.cameraManager getImageContrastWithCompletion:^(NSInteger contrast, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:4 withObject:[NSString stringWithFormat:@"%ld",(long)contrast]];
                [strongSelf.listView reloadData];
            }
        }];
        //获取测光模式
        [self.cameraManager getEyeMeteringModeWithCompletion:^(PVEyeCameraMeteringMode meteringMode, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:5 withObject:[self getCurrentValueWithType:type Row:5 Index:meteringMode - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        //获取AF模式
        [self.cameraManager getEyeCameraVideoAFWithCompletion:^(PVCameraVideoAF videoAF, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:6 withObject:[self getCurrentValueWithType:type Row:6 Index:videoAF - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        //获取OSD开关
        [self.cameraManager getEyeOSDSwitchOpenStatusWithCompletion:^(PVEyeOSDSwitchState state, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:7 withObject:[self getCurrentValueWithType:type Row:7 Index:state - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        //获取图像锐度
        [self.cameraManager getImageSharpnessWithCompletion:^(NSInteger sharpness, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                NSInteger index = sharpness;
                if (sharpness >= 3 || sharpness < 0) {
                    index = 2;
                }
                [strongSelf.currentValues replaceObjectAtIndex:8 withObject:[self getCurrentValueWithType:type Row:8 Index:index]];
            }
        }];
        //获取PowerEye拍照张数
        [self.cameraManager getEyeSDRemainingCapacityWithComplection:^(NSInteger remainingCapacity, NSError * _Nullable    error) {
            STRONGSELF;
            if (error == nil) {
                if (remainingCapacity == 0) {
                    [strongSelf.currentValues replaceObjectAtIndex:9 withObject:@"无SD卡"];
                }else{
                    [strongSelf.currentValues replaceObjectAtIndex:9 withObject:[NSString stringWithFormat:@"%ld",(long)remainingCapacity]];
                }
                [strongSelf.listView reloadData];
            }
        }];
    }
    
    [self.listView reloadData];
}

#pragma mark - UITableViewDelegate,UITableViewDataSource
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return _parameters.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *CellIdentifier = @"";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = self.parameters[indexPath.row];
    cell.detailTextLabel.text = self.currentValues[indexPath.row];
    cell.detailTextLabel.textColor = [UIColor blueColor];
    
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    selectIndex = indexPath.row;
    if (parameterType == CameraSettingTypeGeneral) {
        if (indexPath.row == 9) {
            //  剩余拍照张数
            return;
        }
        if (indexPath.row == 10) {
            //  格式化SD卡
            [self.cameraManager formatSDWithCompletion:^(NSError * _Nullable error) {
                if (error == nil) {
                    NSLog(@"格式化SD卡成功");
                }else{
                    NSLog(@"格式化SD卡失败");
                }
            }];
            return;
        }else if (indexPath.row == 11) {
            //  恢复出厂设置
            [self.cameraManager resetToCameraFactoryWithCompletion:^(NSError * _Nullable error) {
                if (error == nil) {
                    NSLog(@"恢复出厂设置成功");
                }else{
                    NSLog(@"恢复出厂设置失败");
                }
            }];
            return;
        }
    }
    [self performSegueWithIdentifier:@"ShowCameraSettingValueVC" sender:self];
}

-(NSString *)getCurrentValueWithType:(CameraSettingType)type Row:(NSInteger)row Index:(NSInteger)index{
    switch (type) {
            //MARK: 光圈设置
        case CameraSettingTypeAperture:
            switch (row) {
                case 0:     //  ISO
                {
                    NSArray *array = @[@"Auto",
                                       @"100",
                                       @"125",
                                       @"160",
                                       @"200",
                                       @"250",
                                       @"320",
                                       @"400",
                                       @"500",
                                       @"640",
                                       @"800",
                                       @"1000",
                                       @"1250",
                                       @"1600",
                                       @"2000",
                                       @"2500",
                                       @"3200",
                                       @"4000",
                                       @"5000",
                                       @"6400"];
                    return array[index];
                }
                    break;
                case 1:     //  光圈大小
                {
                    NSArray *array = @[@"2.5",
                                       @"2.8",
                                       @"3.2",
                                       @"3.5",
                                       @"4.0",
                                       @"4.5",
                                       @"5.0",
                                       @"5.6",
                                       @"6.3",
                                       @"7.1",
                                       @"8.0",
                                       @"9.0",
                                       @"10.0",
                                       @"11.0",
                                       @"13.0",
                                       @"14.0",
                                       @"16.0",
                                       @"18.0",
                                       @"20.0",
                                       @"22.0"];
                    return array[index];
                }
                    break;
                case 2:     //  EV
                {
                    NSArray *array = @[@"-3.0",
                                       @"-2.7",
                                       @"-2.3",
                                       @"-2.0",
                                       @"-1.7",
                                       @"-1.3",
                                       @"-1.0",
                                       @"-0.7",
                                       @"-0.3",
                                       @"0.0",
                                       @"0.3",
                                       @"0.7",
                                       @"1.0",
                                       @"1.3",
                                       @"1.7",
                                       @"2.0",
                                       @"2.3",
                                       @"2.7",
                                       @"3.0"];
                    return array[index];
                }
                    break;
                case 3:     //  拍照快门速度
                {
                    NSArray *array = @[@"Auto",
                                       @"1/2s",
                                       @"1/3s",
                                       @"1/4s",
                                       @"1/5s",
                                       @"1/8s",
                                       @"1/10s",
                                       @"1/15s",
                                       @"1/20s",
                                       @"1/25s",
                                       @"1/40s",
                                       @"1/50s",
                                       @"1/60s",
                                       @"1/80s",
                                       @"1/100s",
                                       @"1/125s",
                                       @"1/160s",
                                       @"1/200s",
                                       @"1/250s",
                                       @"1/320s"];
                    return array[index];
                }
                    break;
                case 4:     //  摄像快门速度
                {
                    NSArray *array = @[@"Auto",
                                       @"1/240s",
                                       @"1/120s",
                                       @"1/100s",
                                       @"1/75s",
                                       @"1/62.5s",
                                       @"1/60s",
                                       @"1/50s",
                                       @"1/40s",
                                       @"1/33.3s",
                                       @"1/30s"];
                    return array[index];
                }
                    break;
                default:
                    return nil;
                    break;
            }
            //MARK: 图像设置
        case CameraSettingTypeShoot:
            if (cameraState == CameraSetting_CameraStateTakePhoto) {
                switch (row) {
                    case 0:     //  相机模式
                    {
                        NSArray *array = @[@"Single",
                                           @"Continuous",
                                           @"Dely"];
                        return array[index];
                    }
                    case 1:     //  连拍速度
                    {
                        NSArray *array = @[@"低速",
                                           @"中低速",
                                           @"中速"];
                        return array[index];
                    }
                    case 2:     //  定时连拍
                    {
                        NSArray *array = @[@"1",@"60"];
                        return array[index];
                    }
                        break;
                    case 3:     //  照片大小
                    {
                        NSArray *array = @[@"16M",
                                           @"12M",
                                           @"8M",
                                           @"5M",
                                           @"3M"];
                        return array[index];
                    }
                        break;
                    case 4:     //  照片质量
                    {
                        NSArray *array = @[@"基本",
                                           @"精细",
                                           @"超精细",
                                           @"JPEG+DNG"];
                        return array[index];
                    }
                        break;
                        
                    default:
                        return nil;
                        break;
                }
            }else{
                switch (row) {
                    case 0:
                    {
                        NSArray *array = @[@"4K 30",
                                           @"4K 24",
                                           @"2K 30",
                                           @"2K 24",
                                           @"1920 30",
                                           @"1920 24",
                                           @"1440 30",
                                           @"1440 24",
                                           @"1080P 60",
                                           @"1080P 30",
                                           @"WVGAP 30"];
                        return array[index];
                    }
                        break;
                        
                    default:
                        return nil;
                        break;
                }
            }
            //MARK: 通用设置
        case CameraSettingTypeGeneral:
            switch (row) {
                case 0:     //  白平衡模式
                {
                    NSArray *array = @[@"Auto",@"Manual"];
                    return array[index];
                }
                    break;
                case 1:     //  白平衡
                {
                    NSArray *array = @[@"1",@"10",@"30",@"50",@"60",@"70",@"100"];
                    return array[index];
                }
                    break;

                case 2:     //  图像亮度
                {
                    NSArray *array = @[@"0",@"100"];
                    return array[index];
                }
                    break;
                case 3:     //  图像饱和度
                {
                    NSArray *array = @[@"0",@"100"];
                    return array[index];
                }
                    break;
                case 4:     //  图像对比度
                {
                    NSArray *array = @[@"0", @"100"];
                    return array[index];
                }
                    break;
                case 5:     //  测光模式
                {
                    NSArray *array = @[@"中央重点",@"平均测光"];
                    return array[index];
                }
                    break;
                case 6:     //  AF模式
                {
                    NSArray *array = @[@"正常",@"自由移动"];
                    return array[index];
                }
                    break;
                case 7:     //  OSD开关
                {
                    NSArray *array = @[@"隐藏",@"显示"];
                    return array[index];
                }
                    break;
                case 8:     //  图像锐度
                {
                    NSArray *array = @[@"弱",@"中",@"强"];
                    return array[index];
                }
                    break;
                    
                default:
                    return nil;
                    break;
            }
        default:
            return nil;
            break;
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"ShowCameraSettingValueVC"]) {
        CameraSettingValueVC *valueVC = segue.destinationViewController;
        if (parameterType == CameraSettingTypeAperture) {
            valueVC.parameterType = selectIndex;
        }else if (parameterType == CameraSettingTypeShoot) {
            if (cameraState == CameraSetting_CameraStateTakePhoto) {
                valueVC.parameterType = selectIndex + 5;
            }else if (cameraState == CameraSetting_CameraStateRecord) {
                valueVC.parameterType = selectIndex + 5 + 5;
            }
        }else if (parameterType == CameraSettingTypeGeneral) {
            valueVC.parameterType = selectIndex + 5 + 5 + 1;
        }
        valueVC.title = self.parameters[selectIndex];
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
