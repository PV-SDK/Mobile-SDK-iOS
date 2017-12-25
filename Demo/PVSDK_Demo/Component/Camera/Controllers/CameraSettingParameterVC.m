//
//  CameraSettingParameterVC.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "CameraSettingParameterVC.h"
#import "CameraSettingValueVC.h"

#import "ComponentHelper.h"

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

@property (nonatomic, copy) NSArray *parameters;
@property (nonatomic, copy) NSArray *values;
@property (nonatomic, strong) NSMutableArray *currentValues;

@property (nonatomic, strong) PVEyeCamera *eyeCameraManager;

@end

@implementation CameraSettingParameterVC

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self initData];
}

- (void)initData{
    whiteBalanceValue = -200;
}

- (void)configWithType:(CameraSettingType)type State:(CameraSetting_CameraState)state{
    parameterType = type;
    cameraState = state;
    
    self.eyeCameraManager = [ComponentHelper fetchEyeCamera];
    
    [self configDataWithCameraType:type];
}

- (void)configDataWithCameraType:(CameraSettingType)type{
    [self.eyeCameraManager getEyeCameraAllSettingWithCompletion:nil];
    WEAKSELF;
    if (type == CameraSettingTypeAperture) {
        self.parameters = @[@"ISO", @"Aperture size", @"EV", @"The photo shutter speed", @"Record shutter speed"];
        self.currentValues = [NSMutableArray arrayWithArray:@[@"",@"",@"",@"",@""]];
        
        //  Get PowerEye camera iso setting.
        [self.eyeCameraManager getEyeCameraISOWithCompletion:^(PVEyeCameraISO iso, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:0 withObject:[self getCurrentValueWithType:type Row:0 Index:iso - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye camera aperture size setting.
        [self.eyeCameraManager getEyeCameraApertureWithCompletion:^(PVEyeCameraAperture aperture, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:1 withObject:[self getCurrentValueWithType:type Row:1 Index:aperture - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye camera exposure setting.
        [self.eyeCameraManager getEyeCameraExposureWithCompletion:^(NSInteger exposure, NSError * _Nullable error) {
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
        
        //  Get PowerEye camera photo shutter speed setting.
        [self.eyeCameraManager getEyeCameraPhotoShutterSpeedWithCompletion:^(PVEyeCameraPhotoShutterSpeed shutterSpeed, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:3 withObject:[self getCurrentValueWithType:type Row:3 Index:shutterSpeed - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye camera video shutter speed setting.
        [self.eyeCameraManager getEyeCameraVideoShutterSpeedWithCompletion:^(PVEyeCameraVideoShutterSpeed videoShutterSpeed, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:4 withObject:[self getCurrentValueWithType:type Row:4 Index:videoShutterSpeed - 51]];
                [strongSelf.listView reloadData];
            }
        }];
    }else if (type == CameraSettingTypeShoot) {
        if (cameraState == CameraSetting_CameraStateTakePhoto) {
            self.parameters = @[@"Camera mode",@"Continuous shoot speed",@"Take photo dely time",@"Photo size",@"Photo quality"];
            self.currentValues = [NSMutableArray arrayWithArray:@[@"",@"",@"",@"",@""]];
            
            //  Get PowerEye camera mode setting.
            [self.eyeCameraManager getEyeCameraModeWithCompletion:^(PVEyeCameraMode cameraMode, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    [strongSelf.currentValues replaceObjectAtIndex:0 withObject:[self getCurrentValueWithType:type Row:0 Index:cameraMode - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
            
            //  Get PowerEye camera continuous shoot speed setting.
            [self.eyeCameraManager getEyeCameraContinuousShootSpeedWithCompletion:^(PVEyeCameraContinuousShootSpeed shootSpeed, NSError * _Nullable error) {
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
            
            //  Get PowerEye camera take photo dely time setting.
            [self.eyeCameraManager getEyeCameraTakePhotoDelyTimeWithCompletion:^(NSInteger time, NSError * _Nullable error) {
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
            
            //  Get PowerEye camera photo size setting.
            [self.eyeCameraManager getEyeCameraPhotoSizeWithCompletion:^(PVEyeCameraPhotoSize photoSize, NSError * _Nullable error) {
                if (error == nil) {
                    STRONGSELF;
                    [strongSelf.currentValues replaceObjectAtIndex:3 withObject:[self getCurrentValueWithType:type Row:3 Index:photoSize - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
            
            //  Get PowerEye camera photo qulity setting.
            [self.eyeCameraManager getEyeCameraPhotoQualityWithCompletion:^(PVEyeCameraPhotoQuality photoQuality, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    [strongSelf.currentValues replaceObjectAtIndex:4 withObject:[self getCurrentValueWithType:type Row:4 Index:photoQuality - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
        }else if (cameraState == CameraSetting_CameraStateRecord) {
            self.parameters = @[@"Video size"];
            self.currentValues = [NSMutableArray arrayWithArray:@[@""]];
            
            //  Get PowerEye camera video size setting.
            [self.eyeCameraManager getEyeCameraVideoSizeWithCompletion:^(PVEyeCameraVideoSize videoSize, NSError * _Nullable error) {
                STRONGSELF;
                if (error == nil) {
                    [strongSelf.currentValues replaceObjectAtIndex:0 withObject:[self getCurrentValueWithType:type Row:0 Index:videoSize - 51]];
                    [strongSelf.listView reloadData];
                }
            }];
        }
    }else if (type == CameraSettingTypeGeneral) {
        self.parameters = @[@"White balance mode",@"White balance values",@"Image brightness",@"Image saturation",@"Image contrast",@"Metering mode",@"AF mode",@"OSD switch open status",@"Image sharpness",@"SD Card remaining capacity",@"Format SD Card",@"Reset to camera factory"];
        self.currentValues = [NSMutableArray arrayWithArray:@[@"",@"",@"",@"",@"",@"",@"",@"",@"",@"",@"",@""]];
        
        //  Get PowerEye white balance mode setting.
        [self.eyeCameraManager getEyeCameraWhiteBalanceModeWithCompletion:^(PVEyeCameraWhiteBalanceMode whiteBalanceMode, NSError * _Nullable error) {
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
        
        //  Get PowerEye white balance values setting.
        [self.eyeCameraManager getEyeCameraWhiteBalanceWithCompletion:^(NSInteger whiteBalance, NSError * _Nullable error) {
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
        
        //  Get PowerEye image brightness setting.
        [self.eyeCameraManager getEyeCameraImageBrightnessWithCompletion:^(NSInteger brightness, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:2 withObject:[NSString stringWithFormat:@"%ld",(long)brightness]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye image saturation setting.
        [self.eyeCameraManager getEyeCameraImageSaturationWithCompletion:^(NSInteger saturation, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:3 withObject:[NSString stringWithFormat:@"%ld",(long)saturation]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye image contrast setting.
        [self.eyeCameraManager getEyeCameraImageContrastWithCompletion:^(NSInteger contrast, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:4 withObject:[NSString stringWithFormat:@"%ld",(long)contrast]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye metering mode setting.
        [self.eyeCameraManager getEyeCameraMeteringModeWithCompletion:^(PVEyeCameraMeteringMode meteringMode, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:5 withObject:[self getCurrentValueWithType:type Row:5 Index:meteringMode - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye camera video af mode setting.
        [self.eyeCameraManager getEyeCameraVideoAFWithCompletion:^(PVEyeCameraVideoAF videoAF, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:6 withObject:[self getCurrentValueWithType:type Row:6 Index:videoAF - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye OSD switch open status setting.
        [self.eyeCameraManager getEyeCameraOSDSwitchOpenStatusWithCompletion:^(PVEyeOSDSwitchState state, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                [strongSelf.currentValues replaceObjectAtIndex:7 withObject:[self getCurrentValueWithType:type Row:7 Index:state - 51]];
                [strongSelf.listView reloadData];
            }
        }];
        
        //  Get PowerEye image sharpness setting.
        [self.eyeCameraManager getEyeCameraImageSharpnessWithCompletion:^(NSInteger sharpness, NSError * _Nullable error) {
            STRONGSELF;
            if (error == nil) {
                NSInteger index = sharpness;
                if (sharpness >= 3 || sharpness < 0) {
                    index = 2;
                }
                [strongSelf.currentValues replaceObjectAtIndex:8 withObject:[self getCurrentValueWithType:type Row:8 Index:index]];
            }
        }];
        
        //  Get PowerEye SD Card remaining capacity setting.
        [self.eyeCameraManager getEyeCameraSDRemainingCapacityWithComplection:^(NSInteger remainingCapacity, NSError * _Nullable    error) {
            STRONGSELF;
            if (error == nil) {
                if (remainingCapacity == 0) {
                    [strongSelf.currentValues replaceObjectAtIndex:9 withObject:@"NO of SD Card"];
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
            //  SD Card remaining capacity
            return;
        }
        if (indexPath.row == 10) {
            //  Format SD Card
            [self.eyeCameraManager formatSDWithCompletion:^(NSError * _Nullable error) {
                if (error == nil) {
                    NSLog(@"Format of SD Card is successful!");
                }else{
                    NSLog(@"Format of SD Card is failed!");
                }
            }];
            return;
        }else if (indexPath.row == 11) {
            //  Reset to camera factory
            [self.eyeCameraManager resetToEyeCameraFactoryWithCompletion:^(NSError * _Nullable error) {
                if (error == nil) {
                    NSLog(@"Reset to camera factory is successful!");
                }else{
                    NSLog(@"Reset to camera factory is failed!");
                }
            }];
            return;
        }
    }
    [self performSegueWithIdentifier:@"ShowCameraSettingValueVC" sender:self];
}

-(NSString *)getCurrentValueWithType:(CameraSettingType)type Row:(NSInteger)row Index:(NSInteger)index{
    switch (type) {
            //MARK: Aperture setting
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
                case 1:     //  Aperture size
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
                case 3:     //  The photo shutter speed
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
                case 4:     //  Record shutter speed
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
            //MARK: Image Setting
        case CameraSettingTypeShoot:
            if (cameraState == CameraSetting_CameraStateTakePhoto) {
                switch (row) {
                    case 0:     //  Camera mode
                    {
                        NSArray *array = @[@"Single",
                                           @"Continuous",
                                           @"Dely"];
                        return array[index];
                    }
                    case 1:     //  Continuous shoot speed
                    {
                        NSArray *array = @[@"Low speed",
                                           @"In low speed",
                                           @"Medium speed"];
                        return array[index];
                    }
                    case 2:     //  Take photo dely time
                    {
                        NSArray *array = @[@"1",@"60"];
                        return array[index];
                    }
                        break;
                    case 3:     //  Photo size
                    {
                        NSArray *array = @[@"16M",
                                           @"12M",
                                           @"8M",
                                           @"5M",
                                           @"3M"];
                        return array[index];
                    }
                        break;
                    case 4:     //  Photo quality
                    {
                        NSArray *array = @[@"Basic",
                                           @"Fine detail",
                                           @"Hyperfine",
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
                    case 0:     //  Video size
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
            //MARK: General Setting
        case CameraSettingTypeGeneral:
            switch (row) {
                case 0:     //  White balance mode
                {
                    NSArray *array = @[@"Auto",@"Manual"];
                    return array[index];
                }
                    break;
                case 1:     //  White balance values
                {
                    NSArray *array = @[@"1",@"10",@"30",@"50",@"60",@"70",@"100"];
                    return array[index];
                }
                    break;

                case 2:     //  Image brightness
                {
                    NSArray *array = @[@"0",@"100"];
                    return array[index];
                }
                    break;
                case 3:     //  Image saturation
                {
                    NSArray *array = @[@"0",@"100"];
                    return array[index];
                }
                    break;
                case 4:     //  Image contrast
                {
                    NSArray *array = @[@"0", @"100"];
                    return array[index];
                }
                    break;
                case 5:     //  Metering mode
                {
                    NSArray *array = @[@"The central focus",@"The average metering"];
                    return array[index];
                }
                    break;
                case 6:     //  AF mode
                {
                    NSArray *array = @[@"Normal",@"Free to move"];
                    return array[index];
                }
                    break;
                case 7:     //  OSD switch open status
                {
                    NSArray *array = @[@"Hides",@"Show"];
                    return array[index];
                }
                    break;
                case 8:     //  Image sharpness
                {
                    NSArray *array = @[@"Weak",@"Medium",@"Intensity"];
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
