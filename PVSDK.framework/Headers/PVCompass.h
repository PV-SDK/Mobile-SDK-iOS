//
//  PVCompass.h
//  PVSDK
//
//  Created by Layne on 16/7/13.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <PVSDK/PVSDK.h>

typedef NS_ENUM(NSInteger,PVCompassCalibrationState)
{
    PVCompassCalibrationStateInvilad,
    PVCompassCalibrationStateLeftDetected,
    PVCompassCalibrationStateLeftDone,
    PVCompassCalibrationStateRightDetected,
    PVCompassCalibrationStateRightDone,
    PVCompassCalibrationStateUpDetected,
    PVCompassCalibrationStateUpDone,
    PVCompassCalibrationStateDownDetected,
    PVCompassCalibrationStateDownDone,
    PVCompassCalibrationStateFrontDetected,
    PVCompassCalibrationStateFrontDone,
    PVCompassCalibrationStateBackDetected,
    PVCompassCalibrationStateBackDone,
    PVCompassCalibrationStateDone,
    PVCompassCalibrationStateFailed,
    PVCompassCalibrationStateOutOfRange,//超出校准范围
};


@interface PVCompass : PVBaseComponent

/**
 *  指南针是否正在校准
 */
@property(nonatomic, readonly) BOOL isCalibrating;

/**
 *  开始指南针校准
 *
 *  @param completion 结果回调
 */
- (void)startCalibrationWithCompletion:(void (^_Nonnull)(PVCompassCalibrationState compassCalibrationState,NSError *_Nullable error))block;

/**
 *  停止指南针校准
 *
 *  @param completion 结果回调
 */
- (void)stopCalibrationWithCompletion:(PVCompletionBlock)completion;

@end
