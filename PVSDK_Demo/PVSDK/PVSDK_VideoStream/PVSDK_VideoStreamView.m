//
//  PVVideoStreamView.m
//  PVVSLibrary
//
//  Created by Gavin.Guo on 2017/11/23.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "PVSDK_VideoStreamView.h"

#import "PVSDK_VideoStreamHeader.h"

#import "PVSDK_UIUtils.h"

@interface PVSDK_VideoStreamView ()
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


@implementation PVSDK_VideoStreamView

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

#pragma mark - 保存视频和视频截图到本地
//- (void)saveVideoAssetToLocal
//{
//    //防止遥控器重复获取到正在录像的状态
//    if (self.shootState != PVCameraShootStateTakePhoto) {
//        NSDate *nowDate = [PVSDK_UIUtils timeZoneToDate:[NSDate date]];
//        NSString *fileName = [PVSDK_UIUtils stringFromDate:nowDate formate:@"yyyy_MM_dd_HH_mm_ss"];
//
//        NSString *videoPath = [[self createDirectoryPath:PVVideoStream_AssetVideoDirectory] stringByAppendingFormat:@"/%@.MOV",fileName];
//        NSString *imagePath = [[self createDirectoryPath:PVVideoStream_AssetVideoDirectory] stringByAppendingFormat:@"/%@_preview.jpg",fileName];
//        
//        [self.vfVideo StartRecordToFileName:videoPath];
//        [self.vfVideo TakeScreenShotToFileName:imagePath];
//    }
//}

#pragma mark - 创建目录 【dirName 目录名】
- (NSString *)createDirectoryPath:(NSString *)dirName
{
    NSString *directory = [[PVSDK_UIUtils getDocumentPath] stringByAppendingPathComponent:dirName];
    BOOL isDir = YES;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:directory isDirectory:&isDir]) {
        [fileManager createDirectoryAtPath:directory withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return directory;
}

#pragma mark - 图传拍摄的图片保存到本地
- (void)saveImageAssetToLocal
{
    NSDate *nowDate = [PVSDK_UIUtils timeZoneToDate:[NSDate date]];
    NSString *imageDirectory = [self createDirectoryPath:PVVideoStream_AssetImageDirectory];
    NSString *fileName = [PVSDK_UIUtils stringFromDate:nowDate formate:@"yyyy_MM_dd_HH_mm_ss"];
    NSString *filePath = [imageDirectory stringByAppendingFormat:@"/%@.jpg",fileName];
    [self.vfVideo TakeScreenShotToFileName:filePath];
}
//#pragma mark - 切换相机模式
//- (void)changeCameraModeCallBack:(PVSendCommandBlock)block{
//    if (_shootState != PVCameraShootStateRecording) {
//        _shootState = (_shootState == PVCameraShootStateTakePhoto) ? PVCameraShootStateRecord : PVCameraShootStateTakePhoto;
//        block(PVCameraCommandReceiveSuccess, 1);
//    }else{
//        block(PVCameraCommandReceiveFaild, 0);
//    }
//}
#pragma mark - 开始录制图传
//- (void)startRecordCallBack:(PVSendCommandBlock)block
//{
//    self.startRecordBlock = block;
//    [self saveVideoAssetToLocal];
//}

#pragma mark - 停止录制图传
//- (void)stopRecordCallBack:(PVSendCommandBlock)block
//{
//    self.stopRecordBlock = block;
//    if (self.shootState == PVCameraShootStateRecording) {
//        [self.vfVideo StopRecord];
//    }
//}

#pragma mark - 拍照图传
//- (void)takephotoCallBack:(PVSendCommandBlock)block
//{
//    self.takePhotoBlock = block;
//    [self saveImageAssetToLocal];
//}

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

//TODO: 准备开始视频录像
- (void)willVFVideoStartRecord
{
    NSLog(@"准备开始视频录像");
}

//TODO: 已开始视频录像
- (void)didVFVideoStartRecordWithResult:(int)result
{
    if (self.startRecordBlock) {
        if (result == 1) {
            _shootState = PVCameraShootStateRecording;
            self.startRecordBlock(PVCameraCommandReceiveSuccess, result);
        }else{
            self.startRecordBlock(PVCameraCommandReceiveFaild, result);
        }
    }
}

//TODO: 正在停止视频录像
- (void)willVFVideoStopRecord
{
    
}

//TODO: 已停止视频录像
- (void)didVFVideoStopRecordWithResult:(int)result
{
    if (self.stopRecordBlock) {
        if (result == 1) {
            _shootState = PVCameraShootStateRecord;
            self.stopRecordBlock(PVCameraCommandReceiveSuccess, result);
        }else{
            self.stopRecordBlock(PVCameraCommandReceiveFaild, result);
        }
    }
    if (self.isExit) {
        [self.vfVideo CloseVideo];
    }
}

//TODO: 正在进行视频截图
- (void)willVFVideoTakeScreenShot
{
    
}

//TODO: 已完成视频截图
- (void)didVFVideoTakeScreenShotWithResult:(int)result
{
    if (self.shootState == PVCameraShootStateTakePhoto) {
        if (self.takePhotoBlock) {
            if (result == 1) {
                self.takePhotoBlock(PVCameraCommandReceiveSuccess, result);
            }else{
                self.takePhotoBlock(PVCameraCommandReceiveFaild, result);
            }
        }
    }
    NSLog(@"照片已保存到SD卡");
}

@end
