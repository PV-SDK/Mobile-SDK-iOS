//
//  VFVideoView.h
//  Helios
//
//  Created by 张圣辉 on 16/8/9.
//  Copyright © 2016年 ZHANGSHENGHUI. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif
#import "VFVideoViewDelegate.h"

/**
 * @brief 视频渲染基类，继承该类以实现自定义渲染
 */
#if TARGET_OS_IPHONE
@interface VFVideoView : UIView
#else
@interface VFVideoView : NSOpenGLView
#endif

/**
 *  视频帧Y通道宽度
 */
@property (atomic, assign) int frameYWidth;
/**
 *  视频帧Y通道高度
 */
@property (atomic, assign) int frameYHeight;
/**
 *  视频帧U通道宽度
 */
@property (atomic, assign) int frameUWidth;
/**
 *  视频帧U通道高度
 */
@property (atomic, assign) int frameUHeight;
/**
 *  视频帧V通道宽度
 */
@property (atomic, assign) int frameVWidth;
/**
 *  视频帧V通道高度
 */
@property (atomic, assign) int frameVHeight;
/**
 *  视频回调委托，用于获取视频数据及视频帧宽高
 */
@property (nonatomic, weak) id<VFVideoViewDelegate> delegate;

/**
 *  初始化渲染类
 *
 *  @param coder 包含nib数据的NSCoder类型数据
 *
 *  @return 渲染类实例
 */
- (id)initWithCoder:(NSCoder *)coder;

/**
 *  初始化渲染类
 *
 *  @param frameRect 指定画面大小的CGRect类型数据
 *
 *  @return 渲染类实例
 */
- (id)initWithFrame:(CGRect)frameRect;

/**
 *  更新要渲染的视频帧宽高，准备图像缓冲区
 *
 *  @return 大小发生变化返回YES，否则返回NO
 */
- (BOOL)UpdateFrameSize;

/**
 *  渲染并显示视频帧
 */
- (void)DisplayFrame;

/**
 *  以指定颜色清除屏幕
 *
 *  @param red 红色分量
 *  @param green 绿色分量
 *  @param blue 蓝色分量
 */
- (void)FillWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;

@end
