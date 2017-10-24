//
//  PVSDKManager.h
//  PVSDK
//
//  Created by Layne on 2017/3/13.
//  Copyright © 2017年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PVFlightControllerState.h"

typedef NS_ENUM(NSUInteger,PVConnectState){
    /**
     *  链路连接中
     */
    PVConnectStateConnecting=0,
    /**
     *  链路已连接
     */
    PVConnectStateConnected=1,
    /**
     *  链路连接断开
     */
    PVConnectStateDisConnected=2,
    /**
     *  链路连接超时
     */
    PVConnectStateTimeout=3,
    /**
     *  链路连接失败
     */
    PVConnectStateFailed=4,
    
    /**
     *  心跳超时
     */
    PVConnectStateHeartTimeout=5,
    
    /**
     *  标准遥控器已连接
     */
    PVRemoteControlConnected=6,
    
    /**
     *  体感遥控器已连接
     */
    PVTGRemoteControlConnected=7,
    
    /**
     *  飞机连接中
     */
    PVAircraftConnecting = 8,
    /**
     *  飞机已连接
     */
    PVAircraftConnected = 9,
    /**
     *  飞机断开连接
     */
    PVAircraftDisConnect = 10 ,
    /**
     *  飞机连接超时
     */
    PVAircraftConnectTimeOut = 11,
    /**
     *  飞机连接失败
     */
    PVAircraftConnectFail = 12,
    /**
     *  水下机器人连接成功
     */
    PVSubmarineConnected = 13,
    /**
     *  心跳恢复
     */
    PVConnectStateHeartTimeoutReply=14,
    /**
     *  水下基站连接失败
     */
    PVConnectStateBaseStationConnectFail=15,
};

@class PVSDKManager;
@protocol PVSDKManagerDelegate <NSObject>

- (void)sdkManager:(PVSDKManager *)manager didUpdateConnectState:(PVConnectState)state;

@end

@interface PVSDKManager : NSObject

@property (nonatomic,weak)id <PVSDKManagerDelegate>delegate;

- (void)startConnectToProductWithMacAddress:(NSString *)macAddress ip:(NSString *)ip port:(int)port cameraIP:(NSString *)cameraIP cameraControlPort:(int)cameraControlPort cameraDataPort:(int)cameraDataPort;

- (void)reConnectTCPAndSDK;


@end
