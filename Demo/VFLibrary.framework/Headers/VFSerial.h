//
//  VFSerial.h
//  VFLibrary
//
//  Created by ZHANGSHENGHUI on 15/11/30.
//  Copyright © 2015年 Shenzhen Vxfly Intelligent Information Technology Co., Ltd. All rights reserved.
//
#import <VFLibrary/VFSerialDelegate.h>
#import <Foundation/Foundation.h>

/**
 *  @brief 串口透传类，用于使用串口透传功能
 */
@interface VFSerial : NSObject
{
    
}

/**
 *  VFSerial的delegate对象
 */
@property (nonatomic, weak) id<VFSerialDelegate> delegate;

/**
 *  返回默认的VFSerial单例对象，该对象会被自动构建，若构建时当前USB可用则使用USB传输模式
 */
+ (instancetype)defaultSerial;

/**
 *  重新构建默认的VFSerial单例对象并返回，若构建时当前USB可用则使用USB传输模式
 */
+ (instancetype)reconstructDefaultSerial;

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
 *  是否已连接
 */
@property (readonly) BOOL IsConnected;

/**
 *  尝试连接远端串口，成功连接将调用delegate中的didConnect函数，连接超时将调用delegate中的didConnectFailed函数
 *
 *  @param host 天空端pDDL模块串口TCPServer的IP地址
 *  @param port 天空端pDDL模块串口TCPServer的监听端口
 *  @param timeout 连接超时时间，单位为秒
 *
 *  @return 连接发起成功为YES，发起失败为NO
 */
- (BOOL)TryConnectToHost:(NSString*)host andPort:(NSInteger)port WithTimeout:(NSTimeInterval)timeout;

/**
 *  断开连接
 */
- (void)Disconnect;

/**
 *  发送二进制数据
 *
 *  @param data NSData格式的二进制数据
 *
 *  @return 是否成功存入缓冲区，Socket已连接则返回YES，未连接返回NO
 */
- (BOOL)SendData:(NSData*)data;

/**
 *  发送字符串
 *
 *  @param string NSString格式的字符串，将以Ascii格式发送
 *
 *  @return 是否成功存入缓冲区，Socket已连接则返回YES，未连接返回NO
 */
- (BOOL)SendString:(NSString*)string;

/**
 *  发送十六进制字符串
 *
 *  @param string NSString格式的十六进制字符串，将被转换成二进制数据发送
 *
 *  @return 是否成功存入缓冲区，Socket已连接则返回YES，未连接返回NO
 */
- (BOOL)SendHexString:(NSString*)string;

/**
 *  将字符串转换成二进制数据，采用Ascii编码
 *
 *  @param string 要转换的NSString格式字符串
 *
 *  @return 转换后得到的二进制数据
 */
+ (NSData*)DataFromString:(NSString*)string;

/**
 *  将二进制数据转换成字符串，采用Ascii解码
 *
 *  @param data 要转换的NSData格式二进制数据
 *
 *  @return 转换后得到的字符串
 */
+ (NSString*)StringFromData:(NSData*)data;

/**
 *  将十六进制字符串转换成二进制数据
 *
 *  @param string 要转换的NSString格式十六进制字符串
 *
 *  @return 转换后得到的二进制数据
 */
+ (NSData*)DataFromHexString:(NSString*)string;

/**
 *  将二进制数据转换成十六进制字符串
 *
 *  @param data 要转换的NSData格式二进制数据
 *
 *  @return 转换后得到的十六进制字符串
 */
+ (NSString*)HexStringFromData:(NSData*)data;

@end
