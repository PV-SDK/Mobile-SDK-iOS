//
//  PVSDK_UIUtils.h
//  PowerVision
//
//  Created by Gavin.Guo on 16/5/10.
//  Copyright © 2016年 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <sys/mount.h>

@interface PVSDK_UIUtils : NSObject

/**
 将日期格式化为NSString对象

 @param date 日期
 @param formate 格式
 @return NSString
 */
+ (NSString *)stringFromDate:(NSDate *)date formate:(NSString *)formate;

/**
 将当前时间转成北京时间

 @param nowDate 当前时间
 @return 北京时间
 */
+ (NSDate *)timeZoneToDate:(NSDate *)nowDate;

/**
 获取手机总存储空间大小

 @return 手机存储空间大小
 */
+ (float)totalDiskSpace;

/**
 获取手机可用存储空间大小

 @return 手机可用存储空间大小
 */
+ (float)freeDiskSpace;

/**
 获取Documents目录

 @return Documents目录
 */
+ (NSString *)getDocumentPath;

/**
 创建目录
 
 @param dirName 目录名
 @return NSString
 */
+ (NSString *)createDirectoryPath:(NSString *)dirName;

@end
