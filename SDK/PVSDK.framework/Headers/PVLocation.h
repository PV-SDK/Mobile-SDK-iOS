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
 [PVLocationDelegate] Update the latitude and longitude information
 
 @param location PVLocation
 @param helper PVFlightHelper
 */
- (void)pv_location:(PVLocation *)location UpdateFlightLocationWithHelper:(PVFlightHelper *)helper;

/**
 [PVLocationDelegate] Update the number of satellite
 
 @param location PVLocation
 @param satelliteNum Satellite Num
 */
- (void)pv_location:(PVLocation *)location UpdateSatelliteNum:(int)satelliteNum;

@end

@interface PVLocation : PVBaseComponent

@property (nonatomic, weak) id <PVLocationDelegate>delegate;

/**
 Instantiation PVLocation
 
 @return PVLocation
 */
+ (instancetype)product;

@end

