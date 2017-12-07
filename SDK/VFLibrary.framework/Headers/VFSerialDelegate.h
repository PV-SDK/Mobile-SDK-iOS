//
//  VFSerialDelegate.h
//  VFLibrary
//
//  Created by ZHANGSHENGHUI on 15/11/30.
//  Copyright © 2015年 Shenzhen Vxfly Intelligent Information Technology Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @brief 串口透传事件回调Delegate
 */
@protocol VFSerialDelegate <NSObject>

@optional

/**
 *  已连接远端串口
 */
- (void)didConnect;

/**
 *  连接远端串口失败
 */
- (void)didConnectFailed;

/**
 *  与远端串口连接断开
 */
- (void)didDisconnect;

/**
 *  发送串口信息到远端
 *
 *  @param data 发送的二进制信息
 *
 */
- (void)didSendData:(NSData*)data;

/**
 *  接收到远端串口信息
 *
 *  @param data 接收到的二进制信息
 *
 */
- (void)didReceiveData:(NSData*)data;

@end
