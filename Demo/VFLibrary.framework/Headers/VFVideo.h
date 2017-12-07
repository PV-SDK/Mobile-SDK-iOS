//
//  VFVideo.h
//  VFLibrary
//
//  Created by 张圣辉 on 15/9/7.
//  Copyright (c) 2015年 Shenzhen Vxfly Intelligent Information Technology Co., Ltd. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "VFVideoView.h"
#import "VFVideoDelegate.h"


/**
 * @brief 视频播放类，用于视频接收、解码、播放控制
 */
@interface VFVideo: NSObject{
	
}

/**
 *  VFVideo的delegate对象
 */
@property (nonatomic, weak) NSObject<VFVideoDelegate> *delegate;

/**
 *  检查视频状态
 *
 *  @return 已打开视频，返回YES；未打开视频，返回NO
 */
- (BOOL)HasVideo;
/**
 *  检查播放状态
 *
 *  @return 处于播放状态，返回YES；不处于播放状态，返回NO
 */
- (BOOL)IsPlaying;
/**
 *  检查录像状态
 *
 *  @return 处于录像状态，返回YES；不处于录像状态，返回NO
 */
- (BOOL)IsRecording;
/**
 *  开始播放视频
 */
- (void)Play;
/**
 *  暂停播放视频
 */
- (void)Pause;
/**
 *  获取已打开的视频流的分辨率宽度
 *
 *  @return 视频分辨率宽度
 */
- (int)GetWidth;
/**
 *  获取已打开的视频流的分辨率高度
 *
 *  @return 视频分辨率高度
 */
- (int)GetHeight;

/**
 *  初始化VFVideo
 *
 *  @param videoView 用于渲染视频的VFVideoView
 *
 *  @return 初始化后的VFVideo对象
 */
- (id)initWithVideoView:(VFVideoView*)videoView;
/**
 *  打开视频流
 *
 *  @param videoPath 视频流的路径，可以为文件路径或者nil（为nil时连接图传设备）
 *  @param timeout   连接超时时间，单位为秒（仅对连接图传设备有效）
 *  @param usesUsb   指定是否使用USB连接
 */
- (void)OpenVideo:(NSString *)videoPath withTimeout:(NSTimeInterval)timeout usesUSB:(BOOL)usesUSB;
/**
 *  关闭已打开的视频流
 */
- (void)CloseVideo;
/**
 *  以阻塞方式关闭已打开的视频流，不触发回调
 */
- (void)CloseVideoSync;

/**
 *  对正在播放的视频截图，并保存到指定文件
 *
 *  @param fileName 视频截图文件路径（包含文件名，后缀为.jpg）
 */
- (void)TakeScreenShotToFileName:(NSString*)fileName;
/**
 *  对正在播放的视频录像，并保存到指定文件
 *
 *  @param fileName 视频录像文件路径（包含文件名，后缀为.mp4）
 */
- (void)StartRecordToFileName:(NSString*)fileName;
/**
 *  停止录像
 */
- (void)StopRecord;
/**
 *  设置在连续丢失视频帧后自动关闭视频
 *
 *  @param frameCount 连续丢帧数，0表示不自动关闭
 */
- (void)setCloseAfterLostFrame:(int)frameCount;
/**
 *  设置屏蔽错误帧，默认为不屏蔽，屏蔽错误帧可以减少网络环境较差时出现的马赛克，但可能导致视频卡顿
 *
 *  @param block YES表示屏蔽，否则不屏蔽
 */
- (void)setBlockErrorFrame:(BOOL)block;

/**
 *  检查当前是否正使用USB播放视频
 *
 *  @result 是否正使用USB
 */
- (BOOL)usesUSB;

@end
