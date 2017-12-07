//
//  VFConfig.h
//  VFLibrary
//
//  Created by ZHANGSHENGHUI on 15/11/25.
//  Copyright © 2015年 Shenzhen Vxfly Intelligent Information Technology Co., Ltd. All rights reserved.
//
#import <VFLibrary/VFConfigDelegate.h>
#import <Foundation/Foundation.h>

/**
 *  @brief 无线模块配置类，用于配置无线传输模块
 */
@interface VFConfig : NSObject
{


}

/**
 *  地面端是否已连接
 */
@property (readonly) BOOL IsGroundConnected;

/**
 *  天上端是否已连接
 */
@property (readonly) BOOL IsAirConnected;

/**
 *  VFConfig的delegate对象
 */
@property (nonatomic, weak) id<VFConfigDelegate> delegate;

/**
 *  返回默认的VFConfig单例对象，该对象会被自动构建，若构建时当前USB可用则使用USB传输模式
 */
+ (instancetype)defaultConfig;

/**
 *  重新构建默认的VFConfig单例对象并返回，若构建时当前USB可用则使用USB传输模式
 */
+ (instancetype)reconstructDeafultConfig;

/**
 *  初始化实例
 *
 *  @param usesUSB 指定是否使用USB传输模式
 *
 *  @return 实例
 */
- (id)initUsesUSB:(BOOL)usesUSB;

/**
 *  检查当前是否使用USB传输模式
 *
 *  @result 是否使用USB传输模式
 */
- (BOOL)usesUSB;

/**
 *  尝试连接地面端，成功连接将调用delegate中的didGroundConnect函数，失败或超时将调用delegate中的didGroundConnectFailed函数
 *
 *  @param timeout 连接超时时间，单位为秒
 */
- (void)TryConnectGroundWithTimeout:(NSTimeInterval)timeout;

/**
 *  断开与地面端的连接
 */
- (void)DisconnectWithGround;

/**
 *  请求获取地面端AP模块SSID，SSID将通过delegate中的didGetApSSID函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetApSSID;

/**
 *  请求获取地面端AP模块无线密码，无线密码将通过delegate中的didGetApPassword函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetApPassword;

/**
 *  请求设置地面端AP模块SSID，设置结果将通过delegate中的didSetApSSIDWithResult函数返回
 *
 *  @param ssid 要设置的新SSID
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetApSSID:(NSString*)ssid;

/**
 *  请求设置地面端AP模块无线密码，设置结果将通过delegate中的didSetApPasswordWithResult函数返回
 *
 *  @param password 要设置的新无线密码
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetApPassword:(NSString*)password;

/**
 *  请求应用当前地面端AP模块配置，请求成功将导致地面端AP模块重启（手机会失去无线网络连接）
 *
 *  @return 请求发送是否成功
 */
- (BOOL)ApplyApConfig;

/**
 *  请求获取地面端国家码，国家码将通过delegate中的didGetGroundCountryCode函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundCountryCode;

/**
 *  请求设置地面端国家码，设置结果将通过delegate中的didSetGroundCountryCodeWithResult函数返回
 *
 *  @param  countryCode 要设置的国家码
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetGroundCountryCode:(NSInteger)countryCode;

/**
 *  请求获取地面端产品型号，产品型号将通过delegate中的didGetGroundModel函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundModel;

/**
 *  请求获取地面端产品序列号，产品序列号将通过delegate中的didGetGroundSN函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundSN;

/**
 *  请求获取地面端pDDL硬件版本号，硬件版本号将通过delegate中的didGetGroundDlHWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundDlHWVersion;

/**
 *  请求获取地面端pDDL软件版本号，软件版本号将通过delegate中的didGetGroundDlSWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundDlSWVersion;

/**
 *  请求获取地面端主控硬件版本号，硬件版本号将通过delegate中的didGetGroundHWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundHWVersion;

/**
 *  请求获取地面端主控软件版本号，软件版本号将通过delegate中的didGetGroundSWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundSWVersion;

/**
 *  请求获取地面端pDDL无线状态，信号强度、信噪比、背景噪声将通过delegate中的didGetGroundDlRSSI:SNR:NOISE函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundDlRadioStatus;

/**
 *  请求获取地面端SQThresh，SQThresh将通过delegate中的didGetGroundDlSQThresh函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundDlSQThresh;

/**
 *  请求设置地面端SQThresh，设置结果将通过delegate中的didSetGroundDlSQThreshWithResult函数返回
 *
 *  @param  sqThresh 要设置的SQThresh
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetGroundDlSQThresh:(NSInteger)sqThresh;

/**
 *  请求获取地面端电池电量，电池电量将通过delegate中的didGetGroundBatteryQuantity函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundBatteryQuantity;

/**
 *  请求地面端pDDL模块恢复出厂设置，请求结果将通过delegate中的didResetGroundWithResult函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)ResetGround;

/**
 *  请求重启地面端pDDL模块，请求结果将通过delegate中的didRebootGroundWithResult函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)RebootGround;

/**
 *  请求重新配对地面端，请求结果将通过delegate中的didRepairGroundWithResult函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)RepairGround;


/**
 *  尝试连接天空端，成功连接将调用delegate中的didAirConnect函数，失败或超时将调用delegate中的didAirConnectFailed函数
 *
 *  @param timeout 连接超时时间，单位为秒
 */
- (void)TryConnectAirWithTimeout:(NSTimeInterval)timeout;

/**
 *  断开与天空端的连接
 */
- (void)DisconnectWithAir;

/**
 *  请求获取天空端国家码，国家码将通过delegate中的didGetAirCountryCode函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirCountryCode;

/**
 *  请求设置天空端国家码，设置结果将通过delegate中的didSetAirCountryCodeWithResult函数返回
 *
 *  @param  countryCode 要设置的国家码
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetAirCountryCode:(NSInteger)countryCode;

/**
 *  请求获取天空端产品型号，产品型号将通过delegate中的didGetAirModel函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirModel;

/**
 *  请求获取天空端产品序列号，产品序列号将通过delegate中的didGetAirSN函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirSN;

/**
 *  请求获取天空端pDDL硬件版本号，硬件版本号将通过delegate中的didGetAirDlHWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirDlHWVersion;

/**
 *  请求获取天空端pDDL软件版本号，软件版本号将通过delegate中的didGetAirDlSWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirDlSWVersion;

/**
 *  请求获取天空端主控硬件版本号，硬件版本号将通过delegate中的didGetAirHWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirHWVersion;

/**
 *  请求获取天空端主控软件版本号，软件版本号将通过delegate中的didGetAirSWVersion函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirSWVersion;

/**
 *  请求获取天空端pDDL无线状态，信号强度、信噪比、背景噪声将通过delegate中的didGetGroundDlRSSI:SNR:NOISE函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirDlRadioStatus;

/**
 *  请求天空端pDDL模块恢复出厂设置，请求结果将通过delegate中的didResetAirWithResult函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)ResetAir;

/**
 *  请求重启天空端pDDL模块，请求结果将通过delegate中的didRebootAirWithResult函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)RebootAir;

/**
 *  请求重新配对天空端，请求结果将通过delegate中的didRepairAirWithResult函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)RepairAir;

/**
 *  请求获取天空端SQThresh，SQThresh将通过delegate中的didGetAirDlSQThresh函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirDlSQThresh;

/**
 *  请求设置天空端SQThresh，设置结果将通过delegate中的didSetAirDlSQThreshWithResult函数返回
 *
 *  @param  sqThresh 要设置的SQThresh
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetAirDlSQThresh:(NSInteger)sqThresh;

/**
 *  请求获取无线桥接状态码，状态码将通过delegate中的didGetDlConnectStatus函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetDlConnectStatus;

/**
 *  请求获取地面端无线桥接信号强度，信号强度将通过delegate中的didGetDlRSSI函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetDlRSSI;

/**
 *  请求获取天空端及地面端pDDL模块无线信道，无线信道将通过delegate中的didGetDlChannel函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetDlChannel;

/**
 *  请求设置天空端及地面端pDDL无线信道，设置结果将通过delegate中的didSetDlChannelWithResult函数返回
 *
 *  @param channel 无线信道，2405~2479
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetDlChannel:(NSInteger)channel;

/**
 *  请求获取地面端pDDL模块无线发射功率，发射功率将通过delegate的didGetGroundDlPower函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetGroundDlPower;

/**
 *  请求获取天空端pDDL模块无线发射功率，发射功率将通过delegate的didGetAirDlPower函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetAirDlPower;

/**
 *  请求设置天空端及地面端pDDL模块无线发射功率，设置结果将通过delegate中的didSetDlPowerWithResult函数返回
 *
 *  @param power 无线发射功率，单位dbm，7~30dbm
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetDlPower:(NSInteger)power;

/**
 *  应用pDDL配置，该操作需要耗时约3秒，期间设备无法接受其他命令，操作完成后结果将通过delegate中的didApplyDlConfigWithResult函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)ApplyDlConfig;

/**
 *  请求获取视频分辨率，视频分辨率将通过delegate中的didGetVideoResolution函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetVideoResolution;

/**
 *  请求设置视频分辨率，设置结果将通过delegate中的didSetVideoResolutionWithResult函数返回
 *
 *  @param resolution 视频分辨率标志，0表示720P30fps，1表示1080P30fps
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetVideoResolution:(NSInteger)resolution;

/**
 *  请求获取视频码流上限，码流上限将通过delegate中的didGetVideoRate函数返回
 *
 *  @return 请求发送是否成功
 */
- (BOOL)GetVideoRate;

/**
 *  请求设置视频流码率上限，设置结果将通过delegate中的didSetVideoRateWithResult函数返回
 *
 *  @param rate 视频流码率上限，单位Mbps，1~16
 *
 *  @return 请求发送是否成功
 */
- (BOOL)SetVideoRate:(NSInteger)rate;

/**
 *  请求进行信道扫描，扫描结果将通过delegate中的didScanDlChannels函数返回，该操作耗时15到30秒，不需要提前连接天空端或地面端
 *
 *  @return 请求发送是否成功
 */
- (BOOL)ScanDlChannels;

/**
 *  上传更新天空端pDDL固件，不需要提前连接天空端
 *
 *  @param  firmwarePath    pDDL固件文件路径
 *
 *  @return 固件上传是否成功
 */
+ (BOOL)updateAirDlFirmware:(NSString*)firmwarePath;

/**
 *  上传更新地面端pDDL固件，不需要提前连接地面端
 *
 *  @param  firmwarePath    pDDL固件文件路径
 *
 *  @return 固件上传是否成功
 */
+ (BOOL)updateGroundDlFirmware:(NSString*)firmwarePath;

/**
 *  更新天空端或地面端的固件
 *
 *  @param  firmwarePath    天空端或地面端固件文件路径
 *
 *  @return 成功更新硬件数量
 */
+ (int)updateFirmware:(NSString*)firmwarePath;


@end
