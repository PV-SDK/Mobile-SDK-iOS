//
//  ComponentHelper.m
//  PVSDK_Demo
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import "ComponentHelper.h"

@implementation ComponentHelper

+(nullable PVCamera*) fetchCamera{
    return [PVCamera new];
}
+(nullable PVBattery*) fetchBattery{
    return [PVBattery new];
}
+(nullable PVGimabal*) fetchGimabal{
    return [PVGimabal new];
}
+(nullable PVFlightController*) fetchFlightController{
    return [PVFlightController new];
}
+(nullable PVRemoteController*) fetchRemoteController{
    return [PVRemoteController new];
}
+(nullable PVMountController*) fetchMountController{
    return [PVMountController new];
}

@end
