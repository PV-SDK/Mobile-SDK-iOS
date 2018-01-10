//
//  PVVideoStreamView.m
//  PVVSLibrary
//
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
    
    //  Initialize the Video
    [self initVideoStreamVideo:YES];
    
}

#pragma mark - Initialize the video
-(void)initVideoStreamVideo:(BOOL)usesHwDecoder
{
    self.vfVideo = [[VFVideo alloc] initWithVideoView:(VFVideoView *)self.vfView];
    [self.vfVideo setCloseAfterLostFrame:60];   //  Close the video stream automatically if 60 frames are lost continuously

    self.vfVideo.delegate = self;
}

#pragma mark - Open the video stream
- (void)openVideoStreamCallBack:(PVSendCommandBlock)block
{
    self.openVideoStreamBlock = block;
    if (![self.vfVideo HasVideo]) {
        [self.vfVideo OpenVideo:@"" withTimeout:5.0 usesUSB:NO];
    }
}

#pragma mark - Close the video stream
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
//TODO: Opening video streams
-(void)willVFVideoOpen
{
    NSLog(@"Opening video streams");
}

//TODO: The video stream has been turned on
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

- (void)willVFVideoDrawFrame
{
    
}

- (void)didVFVideoDrawFrameWithResult:(int)result
{
    
}

//TODO: Closing the open video stream
- (void)willVFVideoClose
{
    NSLog(@"Closing the open video stream");
}

//TODO: Video streaming has been turned off
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
