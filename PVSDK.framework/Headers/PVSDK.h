
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

// In this header, you should import all the public headers of your framework using statements like #import <PVSDK/PublicHeader.h>

#import "PVFlightController.h"
#import "PVMountController.h"
//#import "PVWayPoint.h"
//#import "PVWayPointMission.h"
//#import "PVCamera.h"
//#import "PVGimabal.h"
//#import "PVBattery.h"
//#import "PVCompass.h"
//#import "PVRemoteController.h"
//#import "PVCameraSettingsDef.h"
//#import "PVCameraSDCardState.h"
//#import "PVSDKManager.h"
//#import "PVSubmarineController.h"
//#import "PVRayRemoteController.h"
//#import "PVBaseStationManager.h"
//#import "PVBaseStationConfig.h"
//#import "PVBaseStationConfigDelegate.h"

