////////////////////////////////////////////////////////////////////////////////////////////////////////
///  Copyright © 2015年 Shenzhen Vxfly Intelligent Information Technology Co., Ltd.
///  All rights reserved.
///
///  @file      VFLibrary.h
///  @brief     SDK统一引用头文件
///
///  @version   1.6.1
///  @author    张圣辉
///  @date      2016/11/30
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @mainpage
 *
 * @section 简介
 *
 * 本文档为pDDL图传产品iOS版配套SDK的开发手册。SDK功能主要包括以下四部分：
 *
 * @li Video        视频播放库
 * @li Config       模块配置库
 * @li Serial       串口透传库
 * @li USBManager   USB接口管理库
 *
 * @section 关于库引用
 * 使用iOS版SDK需要在工程的链接选项中添加“c++”、“z”、“iconv”三个库的引用，具体操作请参照“iOS应用快速开发指南”。
 *
 * @section 关于USB功能
 * USB功能需要添加“ExternalAccessory.framework”库引用，并且在Info.plist文件内“Supported external accessory protocols”键下添加一项，键值为“com.vxfly.sdk”。
 */

#import <UIKit/UIKit.h>

//! Project version number for VFLibrary.
FOUNDATION_EXPORT double VFLibraryVersionNumber;

//! Project version string for VFLibrary.
FOUNDATION_EXPORT const unsigned char VFLibraryVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <VFLibrary/PublicHeader.h>

#import <VFLibrary/VFVideoViewDelegate.h>
#import <VFLibrary/VFVideoView.h>
#import <VFLibrary/VFOpenGLView.h>
#import <VFLibrary/VFVideoDelegate.h>
#import <VFLibrary/VFVideo.h>
#import <VFLibrary/VFConfigDelegate.h>
#import <VFLibrary/VFConfig.h>
#import <VFLibrary/VFSerialDelegate.h>
#import <VFLibrary/VFSerial.h>
#import <VFLibrary/VFUSBManager.h>
#import <VFLibrary/VFError.h>
//#import <VFLibrary/VFPlayer.h>


