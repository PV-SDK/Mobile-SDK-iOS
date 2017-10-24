//
//  PVCameraSDCardState.h
//  PVSDK
//
//  Created by Layne on 16/6/26.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PVCameraSDCardState : NSObject

/**
 *  SD卡错误
 */
@property(nonatomic, assign) BOOL sdError;

/**
 *  SD卡格式化成功
 */
@property(nonatomic, assign) BOOL isFormatSuccess;

/**
 *  SD卡格式化失败
 */
@property(nonatomic, assign) BOOL isFormatFail;

/**
 *  SD卡正在格式化
 */
@property(nonatomic, assign) BOOL isFormatting;

/**
 *  SD卡存储已满
 */
@property(nonatomic, assign) BOOL isFull;

/**
 *  SD卡已插入
 */
@property(nonatomic, assign) BOOL isInstalled;

/**
 *  内存卡总容量
 */
@property(nonatomic, assign) int totalCapacity;

/**
 *  内存卡可用容量
 */
@property(nonatomic,assign) int remainingCapacity;


@end
