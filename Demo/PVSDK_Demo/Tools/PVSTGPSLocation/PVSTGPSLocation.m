//
//  PVSTGPSLocation.m
//  PVSDK
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "PVSTGPSLocation.h"

@interface PVSTGPSLocation () <CLLocationManagerDelegate>
{
    CLLocationManager *_locationManager;
    LocationResultCallBack _locationResultBlock;
    BOOL _isStop;
}

@end

@implementation PVSTGPSLocation

static PVSTGPSLocation *picker = nil;

+ (instancetype)shareGPSLocationPicker
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        picker = [[PVSTGPSLocation alloc] init];
    });
    return picker;
}

+ (id)allocWithZone:(struct _NSZone *)zone
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        picker = [super allocWithZone:zone];
    });
    return picker;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status{
    switch (status) {
        case kCLAuthorizationStatusNotDetermined:
            if ([[[UIDevice currentDevice] systemVersion] doubleValue] > 8.0) {
                [_locationManager requestWhenInUseAuthorization];
            } else {
                [_locationManager startUpdatingLocation];
            }
            break;
        case kCLAuthorizationStatusDenied:
            //请打开系统设置中\"隐私->定位服务\",允许使用您的位置。
            break;
        case kCLAuthorizationStatusRestricted:
            //定位服务无法使用！
            break;
            
        default:
            [_locationManager startUpdatingLocation];//开启位置更新
            break;
    }
}

#pragma mark - 启动定位
- (void)startLocationAndCompletion:(LocationResultCallBack)completion
{
    //初始化CLLocationManager
    if (_locationManager) {
        _isStop = NO;
        _locationManager = nil;
    }
    if (_locationResultBlock) {
        _locationResultBlock = nil;
    }
    NSLog(@"启动定位");
    
    _locationResultBlock = completion;
    
    _locationManager = [[CLLocationManager alloc] init];
    _locationManager.delegate = self;
    _locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    _locationManager.distanceFilter = kCLDistanceFilterNone;
    if ([[[UIDevice currentDevice] systemVersion] doubleValue] > 8.0)
    {
        [_locationManager requestAlwaysAuthorization];// 前后台同时定位
    }
    [_locationManager startUpdatingLocation];
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations
{
    if (_isStop) {
        return;
    }
    
    //  得到 Location
    CLLocation *coord = [locations objectAtIndex:0];
    
    NSLog(@"采集到的坐标经度:%f, 维度:%f  精度%f", coord.coordinate.longitude, coord.coordinate.latitude, coord.horizontalAccuracy);
    //  判断采集到的精度
    if (_locationResultBlock && !_isStop) {
        _locationResultBlock(coord, nil);
    }
}

#pragma mark - Localtion Failed
- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    NSLog(@"定位失败:%@", error);
    if (!_isStop && _locationResultBlock) {
        _locationResultBlock(kZeroLocation, error);
    }
}

- (void)stop
{
    _isStop = YES;
    [_locationManager stopUpdatingLocation];
}

- (void)geocodeAddressWithCoordinate:(CLLocationCoordinate2D)loc completion:(void (^)(NSString *))completion
{
    CLGeocoder *geoCoder = [[CLGeocoder alloc] init];
    CLLocation *mycurLocaton=[[CLLocation alloc]initWithLatitude:loc.latitude longitude:loc.longitude];
    
    //  反解析
    [geoCoder reverseGeocodeLocation:mycurLocaton completionHandler:^(NSArray *places,NSError *error){
        //  取得第一个地标，地标中存储了详细的地址信息，注意：一个地名可能搜索出多个地址
        CLPlacemark *placemark = [places firstObject];
        NSDictionary *addressDic = placemark.addressDictionary;//详细地址信息字典,包含以下部分信息
        NSString *address = @"";
        if (addressDic && addressDic[@"FormattedAddressLines"]) {
            address = addressDic[@"FormattedAddressLines"][0];
        }
        completion(address);
    }];
}

@end
