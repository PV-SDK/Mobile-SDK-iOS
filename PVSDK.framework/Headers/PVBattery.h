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
    //第一节电芯电压
    float firstCellVol;
    //第二节电芯电压
    float sencondCellVol;
    //第三节电芯电压
    float thirdCellVol;
    //第四节电芯电压
    float forthCellVol;
    //循环次数
    int cycleTimes;
    //电池总容量
    float totalCapacity;
    //电池温度
    float temperature;
    //电池当前剩余电量
    int battery_remaining;
    
    int antennaIndex;
}PVBatteryStatus;

@interface PVBattery : PVBaseComponent

/**
 *  获取智能电池状态信息
 *
 *  @param block 状态信息结果
 */
- (void)getSmartBatteryStatusWithCompletion:(void (^)(PVBatteryStatus batteryStatus,NSError *error))block;

@end
