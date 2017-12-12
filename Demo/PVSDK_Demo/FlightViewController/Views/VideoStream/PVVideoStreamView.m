//
//  PVVideoStreamView.m
//  PVVSLibrary
//
//  Created by Gavin.Guo on 2017/11/23.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "PVVideoStreamView.h"

@interface PVVideoStreamView ()
<
VFVideoDelegate
>

@property (nonatomic, copy) PVSendCommandBlock openVideoStreamBlock;
@property (nonatomic, copy) PVSendCommandBlock closeVideoStreamBlock;

@property (nonatomic, copy) PVSendCommandBlock takePhotoBlock;
@property (nonatomic, copy) PVSendCommandBlock startRecordBlock;
@property (nonatomic, copy) PVSendCommandBlock stopRecordBlock;

@property (nonatomic, strong) VFOpenGLView *vfView;

@property (nonatomic, assign) BOOL streamState;
@property (nonatomic, assign) BOOL isExit;

@end


@implementation PVVideoStreamView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self _initVideoStreamView];
    }
    return self;
}

#pragma mark - 初始化 Video Stream
- (void)_initVideoStreamView
{
    self.vfView = [[VFOpenGLView alloc] initWithFrame:self.bounds];
    [self addSubview:self.vfView];
    
    //  初始化 Video
    [self initVideoStreamVideo:YES];
    
}

#pragma mark - 初始化 Video
-(void)initVideoStreamVideo:(BOOL)usesHwDecoder
{
    self.vfVideo = [[VFVideo alloc] initWithVideoView:(VFVideoView *)self.vfView];
    [self.vfVideo setCloseAfterLostFrame:60];   //设置丢帧60s关闭视频
    self.vfVideo.delegate = self;
}

#pragma mark - 开启图传
- (void)openVideoStreamCallBack:(PVSendCommandBlock)block
{
    self.openVideoStreamBlock = block;
    if (![self.vfVideo HasVideo]) {
        [self.vfVideo OpenVideo:@"" withTimeout:5.0 usesUSB:NO];
    }
}

#pragma mark - 关闭图传
- (void)closeVideo:(BOOL)isExit CallBack:(PVSendCommandBlock)block
{
    self.closeVideoStreamBlock = block;
    self.isExit = isExit;
    if (isExit) {
        if (self.shootState == PVCameraShootStateRecording) {
            [self.vfVideo StopRecord];
        } else {
            [self.vfVideo CloseVideo];
        }
    } else {
        [self.vfVideo CloseVideo];
    }
}

#pragma mark - Video Stream Video Delegate
//TODO: 正在打开视频流
-(void)willVFVideoOpen
{
    NSLog(@"正在打开视频流");
}

//TODO: 已打开视频流
-(void)didVFVideoOpenWithResult:(int)result
{
    if (self.openVideoStreamBlock) {
        if (result == 1) {
            self.streamState = YES;
            self.openVideoStreamBlock(PVCameraCommandReceiveSuccess, result);
        }else{
            self.streamState = NO;
            self.openVideoStreamBlock(PVCameraCommandReceiveFaild, result);
        }
    }
    
    if (result != 1) {
        __weak __typeof(self) weakSelf = self;
        if (!self.isExit) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5.0 * NSEC_PER_SEC)), dispatch_get_global_queue(0, 0), ^{
                __strong __typeof(self) strongSelf = weakSelf;
                [strongSelf.vfVideo OpenVideo:@"" withTimeout:5.0 usesUSB:NO];
            });
        }
    }
}

//TODO: 正在调用DrawFrame
- (void)willVFVideoDrawFrame
{
    
}

//TODO: DrawFrame调用完成
- (void)didVFVideoDrawFrameWithResult:(int)result
{
    
}

//TODO: 正在关闭已打开的视频流
- (void)willVFVideoClose
{
    NSLog(@"正在关闭已打开的视频流");
}

//TODO: 已关闭视频流
- (void)didVFVideoCloseWithResult:(int)result
{
    if (self.closeVideoStreamBlock) {
        if (result == 1) {
            self.closeVideoStreamBlock(PVCameraCommandReceiveSuccess, result);
        }else{
            self.closeVideoStreamBlock(PVCameraCommandReceiveFaild, result);
        }
    }
    __weak __typeof(self) weakSelf = self;
    if (!self.isExit) {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(){
            __strong __typeof(self) strongSelf = weakSelf;
            [strongSelf.vfVideo OpenVideo:@"" withTimeout:5.0 usesUSB:NO];
        });
    } else {
        
    }
}


@end
