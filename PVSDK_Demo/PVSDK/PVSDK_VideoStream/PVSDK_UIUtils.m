//
//  PVSDK_UIUtils.m
//  PowerVision
//
//  Created by Gavin.Guo on 17/11/24.
//  Copyright © 2016年 PowerVision. All rights reserved.
//

#import "PVSDK_UIUtils.h"

@implementation PVSDK_UIUtils
//将日期格式化为NSString对象
+ (NSString *)stringFromDate:(NSDate *)date formate:(NSString *)formate {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:formate];
    NSString *datestring = [dateFormatter stringFromDate:date];
    return datestring;
}

//将当前时间转成北京时间
+ (NSDate *)timeZoneToDate:(NSDate *)nowDate
{
    NSTimeZone *zone = [NSTimeZone systemTimeZone];
    NSInteger interval = [zone secondsFromGMTForDate: nowDate];
    NSDate *localeDate = [nowDate  dateByAddingTimeInterval: interval];
    return localeDate;
}

/**描述：获取手机总存储空间大小
 *  @return 手机存储空间大小
 */
+ (float)totalDiskSpace
{
    NSDictionary *fattributes = [[NSFileManager defaultManager] attributesOfFileSystemForPath:NSHomeDirectory() error:nil];
   long long space =  [[fattributes objectForKey:NSFileSystemSize] longLongValue];
    float spaceFloat = space/1024.0/1024/1024;
    return spaceFloat;
}

/**描述：获取手机可用存储空间大小
 *  @return 手机存储空间大小
 */
+ (float)freeDiskSpace
{
    struct statfs buf;
    unsigned long long freeSpace = -1;
    if (statfs("/var", &buf) >= 0) {
        freeSpace = (unsigned long long)(buf.f_bsize * buf.f_bavail);
    }
    return freeSpace/1024.0/1024/1024.0;
}

/**
 创建目录
 
 @param dirName 目录名
 @return NSString
 */
+ (NSString *)createDirectoryPath:(NSString *)dirName
{
    NSString *directory = [[PVSDK_UIUtils getDocumentPath] stringByAppendingPathComponent:dirName];
    BOOL isDir = YES;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:directory isDirectory:&isDir]) {
        [fileManager createDirectoryAtPath:directory withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return directory;
}

+ (NSString *)getDocumentPath {
    NSArray *documents = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentPath = documents[0];
    return documentPath;
}


@end
