//
//  VFVideoDelegate.h
//  VFLibrary
//
//  Created by 张圣辉 on 15/9/7.
//  Copyright (c) 2015年 Shenzhen Vxfly Intelligent Information Technology Co., Ltd. All rights reserved.
//
#import <Foundation/Foundation.h>

/**
 *  @brief 视频解码事件回调Delegate
 */
@protocol VFVideoDelegate <NSObject>
/**
 *  正在打开视频流
 */
-(void) willVFVideoOpen;
/**
 *  已打开视频流
 *
 *  @param result   VF_Success：打开视频流成功
 *                  VF_HasVideo：已有视频正在播放
 *                  VF_Failed：打开视频流失败
 */
-(void) didVFVideoOpenWithResult:(int)result;
/**
 *  正在调用DrawFrame
 */
-(void) willVFVideoDrawFrame;
/**
 *  DrawFrame调用完成
 *
 *  @param result   VF_Success：解码并渲染视频帧成功
 *                  VF_BrokenFrame：解码成功但视频帧不完整，该帧被正常渲染
 *                  VF_SkipFrame：解码成功但视频帧不完整，该帧已被屏蔽
 *                  VF_RecvTimeout: 超时未收到帧信息
 *                  VF_NonsupportNalType: 收到不支持的帧类型
 *                  VF_RtspClosed: RTSP连接已关闭
 *                  VF_NoVideo: 没有打开视频
 */
-(void) didVFVideoDrawFrameWithResult:(int)result;
/**
 *  正在关闭已打开的视频流
 */
-(void) willVFVideoClose;
/**
 *  已关闭视频流
 *
 *  @param result   VF_Success: 成功关闭视频流
 *                  VF_LostFrame: 连续丢帧导致视频关闭
 *                  VF_NoVideo: 没有视频正在播放
 */
-(void) didVFVideoCloseWithResult:(int)result;
/**
 *  准备开始视频录像
 */
-(void) willVFVideoStartRecord;
/**
 *  已开始视频录像
 *
 *  @param result   VF_Success: 成功开始视频录像
 *                  VF_NoVideo: 没有视频正在播放
 *                  VF_InvalidFile: 缺少文件保存路径
 *                  VF_Failed: 未知原因视频录像失败
 */
-(void) didVFVideoStartRecordWithResult:(int)result;
/**
 *  正在停止视频录像
 */
-(void) willVFVideoStopRecord;
/**
 *  已停止视频录像
 *
 *  @param result   VF_Success: 视频录像停止成功
 *                  VF_NoVideo: 没有正在进行的录像
 *                  VF_Failed: 未知原因视频录像停止失败
 */
-(void) didVFVideoStopRecordWithResult:(int)result;
/**
 *  正在进行视频截图
 */
-(void) willVFVideoTakeScreenShot;

/**
 *  已完成视频截图
 *
 *  @param result   VF_Success: 视频截图成功
 *                  VF_NoVideo: 没有视频正在播放
 *                  VF_InvalidFile: 缺少文件保存路径
 *                  VF_Failed: 未知原因视频截图失败
 */
-(void) didVFVideoTakeScreenShotWithResult:(int)result;

@end
