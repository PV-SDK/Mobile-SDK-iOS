//
//  PVLocation.h
//  PVSDK
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <PVSDK/PVSDK.h>

@class PVLocation;

@protocol PVLocationDelegate <NSObject>

@optional

/**
 [PVLocationDelegate] 更新经纬度信息

 @param location PVLocation
 @param eyeHelper PVFlightHelper
 */
- (void)pv_location:(PVLocation *)location UpdateFlightLocationWithHelper:(PVFlightHelper *)helper;

/**
 [PVLocationDelegate] 更新卫星颗数

 @param location PVLocation
 @param satelliteNum Satellite Num
 */
- (void)pv_location:(PVLocation *)location UpdateSatelliteNum:(int)satelliteNum;

@end

@interface PVLocation : PVBaseComponent

@property (nonatomic, weak) id <PVLocationDelegate>delegate;

@end
