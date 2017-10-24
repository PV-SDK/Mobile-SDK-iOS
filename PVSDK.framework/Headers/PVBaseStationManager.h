//
//  PVBaseStationManager.h
//  PVSDK
//
//  Created by Layne on 2017/5/18.
//  Copyright © 2017年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>

//////////////////////////////////////////////////
/// @brief 水下升级状态说明
///
/// 定义了基站升级时的状态
//////////////////////////////////////////////////
typedef enum _POWERRAY_BASE_UPGRADE_STATE {
    POWERRAY_BASE_UPGRADE_STATE_READ_BOOT_LOADER = 0, //识别bootloader成功
    POWERRAY_BASE_UPGRADE_STATE_GET_FLASH_SIZE = 1, //获得flash size成功
    POWERRAY_BASE_UPGRADE_STATE_ERASE = 2, //擦除基站原程序成功
    POWERRAY_BASE_UPGRADE_STATE_UPLOADING = 3, //上传文件中
    POWERRAY_BASE_UPGRADE_STATE_UPLOAD_OK = 4, //上传文件成功
    POWERRAY_BASE_UPGRADE_STATE_CHECK_FILE_OK = 5, //文件校验成功
    POWERRAY_BASE_UPGRADE_STATE_CHECK_FILE_FAIL = 6, //文件校验失败
    POWERRAY_BASE_UPGRADE_STATE_RESTART = 7, //基站重启
    POWERRAY_BASE_UPGRADE_STATE_DISCONNECTION = 8 //基站链接已断开
} POWERRAY_BASE_UPGRADE_STATE;

/**
 wifi连接状态

 - PVBaseStationWifiStateConnectError: 连接失败
 - PVBaseStationWifiStateQueryOK: 获取基站版本号成功
 */
typedef NS_ENUM(NSInteger,PVBaseStationWifiState) {

    PVBaseStationWifiStateConnectError=0,
    PVBaseStationWifiStateQueryOK=6,
};

@interface PVBaseStationManager : NSObject

/**
 *  基站升级
 *
 *  @param block 升级结果
 */
- (void)startRCFirmwareUpdate:(NSString *_Nullable)filePath WithComplection:(void (^_Nonnull)(POWERRAY_BASE_UPGRADE_STATE upgradeState,NSInteger upgradeProcess,NSError *_Nullable error))block;

/**
 *  获取基站固件版本
 *
 *  @param block 获取结果
 */
- (void)getBaseStationVersionWithComplection:(void (^_Nonnull)(int version,NSError *_Nullable error))block;

/**
 获取基站wifi固件版本

 @param block 获取版本回调
 */
- (void)getBaseStationWifiVisionWithIPaddress:(NSString *_Nullable)ip andPort:(int)port WithComplection:(void (^_Nonnull)(PVBaseStationWifiState wifistate, NSString *_Nullable version,NSError *_Nullable error))block;

@end
