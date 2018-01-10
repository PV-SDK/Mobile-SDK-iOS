//
//  PVBattery.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import <PVSDK/PVSDK.h>

typedef struct
{
    float firstCellVol;     ///< The voltage of the first cell
    float sencondCellVol;   ///< The voltage of the second cell
    float thirdCellVol;     ///< The voltage of the third cell
    float forthCellVol;     ///< The voltage of the fourth cell
    int cycleTimes;         ///< Cycle index
    float totalCapacity;    ///< Total battery capacity
    float temperature;      ///< Cell temperature
    int battery_remaining;  ///< Dump energy
    int antennaIndex;
}PVBatteryStatus;

@interface PVBattery : PVBaseComponent

/**
 Instantiation PVBattery
 
 @return PVBattery
 */
+ (instancetype)product;

/**
 *  Acquire the information about smart battery status
 *
 *  @param block results of status information
 */
- (void)getSmartBatteryStatusWithCompletion:(void (^)(PVBatteryStatus batteryStatus,NSError *error))block;

@end

