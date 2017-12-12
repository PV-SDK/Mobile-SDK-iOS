//
//  ComponentHelper.h
//  PVSDK_Demo
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PVSDK/PVSDK.h>

@class PVCamera;
@class PVBattery;
@class PVGimabal;
@class PVFlightController;
@class PVRemoteController;
@class PVMountController;

@interface ComponentHelper : NSObject

+(nullable PVCamera*) fetchCamera;
+(nullable PVBattery*) fetchBattery;
+(nullable PVGimabal*) fetchGimabal;
+(nullable PVFlightController*) fetchFlightController;
+(nullable PVRemoteController*) fetchRemoteController;
+(nullable PVMountController*) fetchMountController;

@end
