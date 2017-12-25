//
//  ComponentHelper.h
//  PVSDK_Demo
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PVSDK/PVSDK.h>

@class PVSDKManager;
@class PVFlightHelper;
@class PVEyeCamera;
@class PVBattery;
@class PVGimabal;
@class PVFlightRemote;
@class PVMount;
@class PVLocation;
@class PVNavigation;

@interface ComponentHelper : NSObject

+(nullable PVSDKManager *)fetchSDKManager;
+(nullable PVFlightHelper *)fetchFlightHelper;
+(nullable PVEyeCamera *)fetchEyeCamera;
+(nullable PVBattery *)fetchBattery;
+(nullable PVGimabal *)fetchGimabal;
+(nullable PVFlightRemote *)fetchFlightRemote;
+(nullable PVMount *)fetchMount;
+(nullable PVLocation *)fetchLocation;
+(nullable PVNavigation *)fetchNavigation;

@end
