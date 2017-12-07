//
//  VFEAManager.h
//  USBTest
//
//  Created by 张圣辉 on 16/7/20.
//  Copyright © 2016年 Vxfly. All rights reserved.
//
#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <ExternalAccessory/ExternalAccessory.h>

/**
 * @brief USB管理类，用于管理USB接口
 */
@interface VFUSBManager : NSObject

/**
 * 初始化USB接口
 */
- (BOOL)initUSB;

/**
 * 打开USB接口
 */
- (BOOL)openUSB;

/**
 * 检查USB当前是否可写
 */
- (BOOL)writable;

/**
 * 向USB写入数据
 */
- (size_t)writeData:(const unsigned char*)data length:(size_t)length;

/**
 * 关闭USB接口
 */
- (BOOL)closeUSB;

/**
 * 检查USB当前可以用
 */
- (BOOL)isUSBAvailable;

/**
 * 支持单例模式
 */
+ (VFUSBManager*)defaultManager;

@end

#endif
