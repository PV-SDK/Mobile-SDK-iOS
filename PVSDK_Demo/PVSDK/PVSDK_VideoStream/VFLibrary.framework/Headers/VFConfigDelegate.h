//
//  VFSerialDelegate.h
//  VFLibrary
//
//  Created by ZHANGSHENGHUI on 15/11/30.
//  Copyright © 2015年 Shenzhen Vxfly Intelligent Information Technology Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @brief 无线模块配置事件回调Delegate
 */
@protocol VFConfigDelegate <NSObject>

@optional

/**
 *  已连接地面端
 */
- (void)didGroundConnect;

/**
 *  连接地面端失败
 */
- (void)didGroundConnectFailed;

/**
 *  与地面端连接断开
 */
- (void)didGroundDisconnect;

/**
 *  成功获取地面端国家码
 *
 *  @param countryCode 地面端当前国家码
 *
 */
- (void)didGetGroundCountryCode:(NSInteger)countryCode;

/**
 *  已设置地面端国家码
 *
 *  @param result 设置成功为YES，失败为NO
 *
 */
- (void)didSetGroundCountryCodeWithResult:(BOOL)result;

/**
 *  成功获取地面端AP模块SSID
 *
 *  @param ssid 地面端AP模块当前SSID
 *
 */
- (void)didGetApSSID:(NSString*)ssid;

/**
 *  成功获取地面端AP模块无线密码
 *
 *  @param password 地面端AP模块当前密码
 *
 */
- (void)didGetApPassword:(NSString*)password;

/**
 *  已设置地面端AP模块SSID
 *
 *  @param result 设置成功为YES，失败为NO
 *
 */
- (void)didSetApSSIDWithResult:(BOOL)result;

/**
 *  已设置地面端AP模块无线密码
 *
 *  @param result 设置成功为YES，失败为NO
 *
 */
- (void)didSetApPasswordWithResult:(BOOL)result;

/**
 *  已获取地面端产品型号
 *
 *  @param model 产品型号
 */
- (void)didGetGroundModel:(NSString*)model;

/**
 *  已获取地面端产品序列号
 *
 *  @param sn 产品序列号
 */
- (void)didGetGroundSN:(NSString*)sn;

/**
 *  已获取地面端pDDL硬件版本号
 *
 *  @param hwVersion 硬件版本号
 */
- (void)didGetGroundDlHWVersion:(NSString*)hwVersion;

/**
 *  已获取地面端pDDL软件版本号
 *
 *  @param swVersion 硬件版本号
 */
- (void)didGetGroundDlSWVersion:(NSString*)swVersion;

/**
 *  已获取地面端主控硬件版本号
 *
 *  @param hwVersion 硬件版本号
 */
- (void)didGetGroundHWVersion:(NSString*)hwVersion;

/**
 *  已获取地面端主控软件版本号
 *
 *  @param swVersion 硬件版本号
 */
- (void)didGetGroundSWVersion:(NSString*)swVersion;

/**
 *  已获取地面端无线状态
 *
 *  @param rssi  无线信号强度
 *  @param snr   无线信噪比
 *  @param noise 无线背景噪声
 */
- (void)didGetGroundDlRSSI:(NSInteger)rssi SNR:(NSInteger)snr NOISE:(NSInteger)noise;

/**
 *  已获取地面端电池电量
 *
 *  @param batteryQuantity 电池电量百分比
 */
- (void)didGetGroundBatteryQuantity:(double)batteryQuantity;

/**
 *  成功获取地面端SQThresh
 *
 *  @param sqThresh 地面端当前SQThresh
 */
- (void)didGetGroundDlSQThresh:(NSInteger)sqThresh;

/**
 *  已设置地面端SQThresh
 *
 *  @param result 设置成功为YES，失败为NO
 *
 */
- (void)didSetGroundDlSQThreshWithResult:(BOOL)result;

/**
 *  已将地面端恢复出厂设置
 *
 *  @param result 恢复成功为YES，失败为NO
 */
- (void)didResetGroundWithResult:(BOOL)result;

/**
 *  已将地面端重启
 *
 *  @param result 重启成功为YES，失败为NO
 */
- (void)didRebootGroundWithResult:(BOOL)result;

/**
 *  已将地面端重新配对
 *
 *  @param result 重新配对成功为YES，失败为NO
 */
- (void)didRepairGroundWithResult:(BOOL)result;



/**
 *  已连接天空端
 */
- (void)didAirConnect;

/**
 *  连接天空端失败
 */
- (void)didAirConnectFailed;

/**
 *  与天空端连接断开
 */
- (void)didAirDisconnect;

/**
 *  成功获取天空端国家码
 *
 *  @param countryCode 地面端当前国家码
 *
 */
- (void)didGetAirCountryCode:(NSInteger)countryCode;

/**
 *  已设置天空端国家码
 *
 *  @param result 设置成功为YES，失败为NO
 *
 */
- (void)didSetAirCountryCodeWithResult:(BOOL)result;

/**
 *  已获取天空端产品型号
 *
 *  @param model 产品型号
 */
- (void)didGetAirModel:(NSString*)model;

/**
 *  已获取天空端产品序列号
 *
 *  @param sn 产品序列号
 */
- (void)didGetAirSN:(NSString*)sn;

/**
 *  已获取天空端pDDL硬件版本号
 *
 *  @param hwVersion 硬件版本号
 */
- (void)didGetAirDlHWVersion:(NSString*)hwVersion;

/**
 *  已获取天空端pDDL软件版本号
 *
 *  @param swVersion 硬件版本号
 */
- (void)didGetAirDlSWVersion:(NSString*)swVersion;

/**
 *  已获取天空端主控硬件版本号
 *
 *  @param hwVersion 硬件版本号
 */
- (void)didGetAirHWVersion:(NSString*)hwVersion;

/**
 *  已获取天空端主控软件版本号
 *
 *  @param swVersion 硬件版本号
 */
- (void)didGetAirSWVersion:(NSString*)swVersion;

/**
 *  已获取天空端无线状态
 *
 *  @param rssi  无线信号强度
 *  @param snr   无线信噪比
 *  @param noise 无线背景噪声
 */
- (void)didGetAirDlRSSI:(NSInteger)rssi SNR:(NSInteger)snr NOISE:(NSInteger)noise;

/**
 *  已将天空端恢复出厂设置
 *
 *  @param result 恢复成功为YES，失败为NO
 */
- (void)didResetAirWithResult:(BOOL)result;

/**
 *  已将天空端重启
 *
 *  @param result 重启成功为YES，失败为NO
 */
- (void)didRebootAirWithResult:(BOOL)result;

/**
 *  已将天空端重新配对
 *
 *  @param result 重新配对成功为YES，失败为NO
 */
- (void)didRepairAirWithResult:(BOOL)result;

/**
 *  成功获取天空端SQThresh
 *
 *  @param sqThresh 地面端当前SQThresh
 *
 */
- (void)didGetAirDlSQThresh:(NSInteger)sqThresh;

/**
 *  已设置天空端SQThresh
 *
 *  @param result 设置成功为YES，失败为NO
 *
 */
- (void)didSetAirDlSQThreshWithResult:(BOOL)result;

/**
 *  已完成信道扫描
 *
 *  @param optimumChannel 当前最佳信道，连接pDDL失败为-1，登录pDDL失败为-2，扫描信道失败为-3
 */
- (void)didScanDlChannels:(NSInteger)optimumChannel;

/**
 *  已获取无线桥接连接状态码
 *
 *  @param connectStatus 连接状态码
 */
- (void)didGetDlConnectStatus:(NSInteger)connectStatus;

/**
 *  已获取地面端无线桥接无线桥接信号强度
 *
 *  @param rssi 信号强度，单位为db，正常值为负值，1表示获取失败
 *
 */
- (void)didGetDlRSSI:(NSInteger)rssi;

/**
 *  已获取天空端及地面端pDDL模块的无线信道
 *
 *  @param channel 无线信道，2405~2479
 */
-(void)didGetDlChannel:(NSInteger)channel;

/**
 *  已设置天空端及地面端pDDL模块无线信道
 *
 *  @param result 设置成功为YES，失败为NO
 */
- (void)didSetDlChannelWithResult:(BOOL)result;

/**
 *  已获取地面端pDDL模块的无线发射功率
 *
 *  @param power 无线发射功率，7~30dbm
 */
-(void)didGetGroundDlPower:(NSInteger)power;

/**
 *  已获取天空端pDDL模块的无线发射功率
 *
 *  @param power 无线发射功率，7~30dbm
 */
-(void)didGetAirDlPower:(NSInteger)power;

/**
 *  已设置天空端及地面端pDDL模块无线发射功率
 *
 *  @param result 设置成功为YES，失败为NO
 */
- (void)didSetDlPowerWithResult:(BOOL)result;

/**
 *  已应用pDDL模块配置
 *
 *  @param result 应用成功为YES，失败为NO
 */
- (void)didApplyDlConfigWithResult:(BOOL)result;

/**
 *  已获取视频分辨率
 *
 *  @param resolution 视频分辨率类型，0表示720P30fps，1表示1080P30fps
 */
- (void)didGetVideoResolution:(NSInteger)resolution;

/**
 *  已设置视频分辨率
 *
 *  @param result 设置成功为YES，失败为NO
 */
- (void)didSetVideoResolutionWithResult:(BOOL)result;

/**
 *  已获取视频流最大码率
 *
 *  @param rate 视频流最大码率，单位为Mbps，1~16
 */
- (void)didGetVideoRate:(NSInteger)rate;

/**
 *  已设置视频流最大码率
 *
 *  @param result 设置成功为YES，失败为NO
 */
- (void)didSetVideoRateWithResult:(BOOL)result;

@end
