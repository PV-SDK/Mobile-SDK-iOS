//
//  PVVideoStreamView.h
//  PowerVision
//
//  Created by Gavin.Guo on 2017/11/23.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <VFLibrary/VFLibrary.h>

typedef enum : NSUInteger {
    PVCameraShootStateTakePhoto = 0,    //  拍照模式
    PVCameraShootStateRecord    = 1,    //  录像模式
    PVCameraShootStateRecording = 2     //  录像中
} PVCameraShootState;

typedef enum : NSUInteger {
    PVCameraCommandReceiveSuccess  = 0,    //  成功
    PVCameraCommandReceiveFaild    = 1     //  失败
} PVCameraCommandReceive;

typedef void(^PVSendCommandBlock)(PVCameraCommandReceive result, NSInteger error);

@interface PVSDK_VideoStreamView : UIView

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
 切换相机模式

 @param block 切换相机模式指令的回调
 */
//- (void)changeCameraModeCallBack:(PVSendCommandBlock)block;

/**
 打开视频流
 
 @param block 打开视频流指令的回调
 */
- (void)openVideoStreamCallBack:(PVSendCommandBlock)block;

/**
 开始录制视频
 
 @param block 开始录制视频指令的回调
 */
//- (void)startRecordCallBack:(PVSendCommandBlock)block;

/**
 停止录像
 
 @param block 停止录像指令的回调
 */
//- (void)stopRecordCallBack:(PVSendCommandBlock)block;

/**
 拍照
 
 @param block 拍照指令的回调
 */
//- (void)takephotoCallBack:(PVSendCommandBlock)block;

/**
 关闭图传

 @param isExit 是否是退出页面
 @param block 关闭图传指令的回调
 */
- (void)closeVideo:(BOOL)isExit CallBack:(PVSendCommandBlock)block;

@end
