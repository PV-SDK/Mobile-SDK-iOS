//
//  PVVideoStreamView.h
//  PowerVision
//
//  Created by Gavin.Guo on 2017/11/23.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <VFLibrary/VFLibrary.h>
#import <Photos/Photos.h>

typedef enum : NSUInteger {
    PVCameraShootStateTakePhoto = 0,
    PVCameraShootStateRecord    = 1,
    PVCameraShootStateRecording = 2
} PVCameraShootState;

typedef enum : NSUInteger {
    PVCameraCommandReceiveSuccess  = 0,
    PVCameraCommandReceiveFaild    = 1
} PVCameraCommandReceive;

typedef void(^PVSendCommandBlock)(PVCameraCommandReceive result, NSInteger error);

@interface PVVideoStreamView : UIView

@property (nonatomic, strong) VFVideo *vfVideo;

/**
 初始化视图
 */
- (instancetype)initWithFrame:(CGRect)frame;

/**
 拍照录像状态
 */
@property (nonatomic, assign) PVCameraShootState shootState;

/**
 打开视频流
 
 @param block 打开视频流指令的回调
 */
- (void)openVideoStreamCallBack:(PVSendCommandBlock)block;

/**
 关闭图传

 @param isExit 是否是退出页面
 @param block 关闭图传指令的回调
 */
- (void)closeVideo:(BOOL)isExit CallBack:(PVSendCommandBlock)block;

@end
