//
//  PVBattery.h
//  PVSDK
//
//  Created by Layne on 16/7/15.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <PVSDK/PVSDK.h>

typedef struct
{
    //The voltage of the first cell
    float firstCellVol;
    //The voltage of the second cell
    float sencondCellVol;
    //The voltage of the third cell
    float thirdCellVol;
    //The voltage of the fourth cell
    float forthCellVol;
    //Cycle index
    int cycleTimes;
    //Total battery capacity
    float totalCapacity;
    //Cell temperature
    float temperature;
    //Dump energy
    int battery_remaining;
    
    int antennaIndex;
}PVBatteryStatus;

@interface PVBattery : PVBaseComponent

/**
 *  Acquire the information about smart battery status
 *
 *  @param block results of status information
 */
- (void)getSmartBatteryStatusWithCompletion:(void (^)(PVBatteryStatus batteryStatus,NSError *error))block;
@end
