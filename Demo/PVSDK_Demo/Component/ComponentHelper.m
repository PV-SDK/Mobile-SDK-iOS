//
//  ComponentHelper.m
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "ComponentHelper.h"

@implementation ComponentHelper

+(nullable PVSDKManager *)fetchSDKManager{
    return [PVSDKManager manager];
}
+(nullable PVProductHelper *)fetchProductHelper{
    return [PVProductHelper helper];
}
+(nullable PVFlightHelper *)fetchFlightHelper{
    return [PVFlightHelper helper];
}
+(nullable PVEyeCamera *)fetchEyeCamera{
    return [PVEyeCamera product];
}
+(nullable PVBattery *)fetchBattery{
    return [PVBattery product];
}
+(nullable PVGimabal *)fetchGimabal{
    return [PVGimabal product];
}
+(nullable PVFlightRemote *)fetchFlightRemote{
    return [PVFlightRemote product];
}
+(nullable PVMount *)fetchMount{
    return [PVMount product];
}
+(nullable PVLocation *)fetchLocation{
    return [PVLocation product];
}
+(nullable PVNavigation *)fetchNavigation{
    return [PVNavigation product];
}

@end
