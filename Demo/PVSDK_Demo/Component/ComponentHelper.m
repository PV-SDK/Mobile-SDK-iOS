//
//  ComponentHelper.m
//  PVSDK_Demo
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import "ComponentHelper.h"

@implementation ComponentHelper

+(nullable PVSDKManager *)fetchSDKManager{
    return [PVSDKManager shareSDKManager];
}
+(nullable PVFlightHelper *)fetchFlightHelper{
    return [PVFlightHelper new];
}
+(nullable PVEyeCamera *)fetchEyeCamera{
    return [PVEyeCamera new];
}
+(nullable PVBattery *)fetchBattery{
    return [PVBattery new];
}
+(nullable PVGimabal *)fetchGimabal{
    return [PVGimabal new];
}
+(nullable PVFlightRemote *)fetchFlightRemote{
    return [PVFlightRemote new];
}
+(nullable PVMount *)fetchMount{
    return [PVMount new];
}
+(nullable PVLocation *)fetchLocation{
    return [PVLocation new];
}
+(nullable PVNavigation *)fetchNavigation{
    return [PVNavigation new];
}

@end
