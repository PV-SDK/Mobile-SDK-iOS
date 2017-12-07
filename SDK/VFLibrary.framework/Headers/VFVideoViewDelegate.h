//
//  VFOpenGLViewDelegate.h
//  Helios
//
//  Created by 张圣辉 on 16/8/8.
//  Copyright © 2016年 ZHANGSHENGHUI. All rights reserved.
//

#ifndef VFVideoViewDelegate_h
#define VFVideoViewDelegate_h

/**
 * @brief 视频渲染类回调委托，用于为视频渲染类提供视频数据
 */
@protocol VFVideoViewDelegate <NSObject>

- (int) getFrameObject:(void**)objectPtr;

- (int) getFrameYBuf:(unsigned char*)yBuf uBuf:(unsigned char*)uBuf vBuf:(unsigned char*)vBuf;

- (int) getFrameYWidth:(int*)yWidthPtr yHeight:(int*)yHeightPtr uWidth:(int*)uWidthPtr uHeight:(int*)uHeightPtr vWidth:(int*)vWidthPtr vHeight:(int*)vHeightPtr;

@end

#endif /* VFVideoViewDelegate_h */
