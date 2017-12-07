
////////////////////////////////////////////////////////////////////////////////////////////////////////
///  Copyright © 2017年
///  All rights reserved.
///
///  @file      PVSDK.h
///  @brief     SDK统一引用头文件
///
///  @version   1.0.0
///  @author    Layne
///  @date      2017/5/31
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @mainpage
 * @subpage mount-page
 * @subpage flight-page
 *
 * @section 简介
 *
 * 本文档为PowerVision公司产品iOS配套SDK开发手册。SDK功能主要包括以下两部分:
 *
 * @li Flight       飞行控制库
 * @li Mount        模块配置库
 *
 * @section 关于库引用
 * 使用iOS版SDK需要在工程的链接选项中添加“libc++.tbd”库的引用，具体操作请参照“iOS应用快速开发指南”。
 *
 */


/**
 * @mainpage 导出接口
 * @subpage mount-page
 */

#import <UIKit/UIKit.h>

//! Project version number for PVSDK.
FOUNDATION_EXPORT double PVSDKVersionNumber;

//! Project version string for PVSDK.
FOUNDATION_EXPORT const unsigned char PVSDKVersionString[];

#import "PVFlightController.h"
#import "PVCamera.h"
#import "PVGimabal.h"
#import "PVMountController.h"
#import "PVCameraCallback.h"
#import "PVBattery.h"
#import "PVRemoteController.h"

