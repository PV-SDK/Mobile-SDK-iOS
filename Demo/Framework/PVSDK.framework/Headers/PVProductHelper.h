//
//  PVProductHelper.h
//  PVSDK
//
//  Created by Gavin.Guo on 2017/12/19.
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    PVProductType_PowerEye = 0,   ///< PowerEye
} PVProductType;

typedef NS_ENUM(NSUInteger, PVConnectState) {
    PVConnectState_Connection_Connecting                 = 0,    ///< Link connecting.                                   [链路连接中]
    PVConnectState_Connection_Connected                  = 1,    ///< Link connected successfully.                       [链路已连接]
    PVConnectState_Connection_Disconnected               = 2,    ///< The connection of link  was interrupted.           [链路连接断开]
    PVConnectState_Connection_Timeout                    = 3,    ///< The connection of link was timed out.              [链路连接超时]
    PVConnectState_Connection_Failed                     = 4,    ///< Failed to connect the link.                        [链路连接失败]
    PVConnectState_Heartbeat_Timeout                     = 5,    ///< Heartbeat timeout.                                 [心跳超时]
    PVConnectState_Standard_Remotecontrol_Connected      = 6,    ///< Standard remote controller has been connected.     [标准遥控器已连接]
    PVConnectState_Motionsensing_Remoteconrol_Connected  = 7,    ///< Gesture-based remote controller has been connected.[体感遥控器已连接]
    PVConnectState_Drone_Connecting                      = 8,    ///< Aircraft connecting.                               [飞机连接中]
    PVConnectState_Drone_Connected                       = 9,    ///< The aircraft has been connected.                   [飞机已连接]
    PVConnectState_Drone_Disconnected                    = 10,   ///< The connection of aircraft was interrupted.        [飞机连接断开]
    PVConnectState_Drone_Connect_Timeout                 = 11,   ///< The connection of aircraft was timed out.          [飞机连接超时]
    PVConnectState_Drone_Connect_Failed                  = 12,   ///< Failed to connect the aircraft.                    [飞机连接失败]
    PVConnectState_Ray_Connected                         = 13,   ///<                                                    [体水下机器人已连接]
    PVConnectState_Connection_Timeout_Replay             = 14,   ///< Heartbeat has recovered.                           [心跳恢复]
    PVConnectState_Ray_Base_Station_Connect_Failed       = 15    ///<                                                    [水下基站连接失败]
};

@interface PVProductHelper : NSObject

@property (nonatomic, assign) PVProductType productType;

/**
 Connection status of aircraft
 */
@property (nonatomic, assign) PVConnectState connectState;

+ (PVProductHelper *)shareHelper;

@end
