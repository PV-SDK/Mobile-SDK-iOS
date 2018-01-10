//
//  PVVideoStreamView.h
//  PowerVision
//
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
 Initialization view
 */
- (instancetype)initWithFrame:(CGRect)frame;

/**
 The shoot state
 */
@property (nonatomic, assign) PVCameraShootState shootState;

/**
 Open video stream
 
 @param block Open video stream call back
 */
- (void)openVideoStreamCallBack:(PVSendCommandBlock)block;

/**
 Close video stream

 @param isExit Is it an exit page
 @param block close video call back
 */
- (void)closeVideo:(BOOL)isExit CallBack:(PVSendCommandBlock)block;

@end
