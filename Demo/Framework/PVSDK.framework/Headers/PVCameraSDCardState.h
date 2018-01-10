//
//  PVCameraSDCardState.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PVCameraSDCardState : NSObject

/**
 SD card error
 */
@property(nonatomic, assign) BOOL sdError;

/**
 Format SD card successfully
 */
@property(nonatomic, assign) BOOL isFormatSuccess;

/**
 Failed to format SD card
 */
@property(nonatomic, assign) BOOL isFormatFail;

/**
 The SD card is being formatted
 */
@property(nonatomic, assign) BOOL isFormatting;

/**
 The storage of  SD card is full
 */
@property(nonatomic, assign) BOOL isFull;

/**
 SD card has been inserted
 */
@property(nonatomic, assign) BOOL isInstalled;

/**
 Total capacity of memory card
 */
@property(nonatomic, assign) int totalCapacity;

/**
 Available capacity of memory card
 */
@property(nonatomic,assign) int remainingCapacity;

+ (PVCameraSDCardState *)shareCameraSDCardState;

@end
