
////////////////////////////////////////////////////////////////////////////////////////////////////////
///  Copyright © 2017
///  All rights reserved.
///
///  @file      PVSDK.h
///  @brief     SDKunified reference header file
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
 * @section Brief Introduction
 *
 * This document is the SDK development manual for products made by PowerVision.SDK function mainly includes the following two parts：
 *
 * @li Flight Flight control library
 * @li Mount  Module configuration library
 *
 * @section About the reference of warehouse
 * You need to add the reference of “libc++.tbd” warehouse to link options in the project when using the iOS version of SDK .
 * Please refer to the "Guidelines for rapid development of iOS applications ".
 */


/**
 * @mainpage Export interface
 * @subpage mount-page
 */

#import <UIKit/UIKit.h>

//! Project version number for PVSDK.
FOUNDATION_EXPORT double PVSDKVersionNumber;

//! Project version string for PVSDK.
FOUNDATION_EXPORT const unsigned char PVSDKVersionString[];

#define PVSDKLog(__str__) NSLog(@"%@", [NSString stringWithFormat:@"[PVSDK]>>>>>%@",__str__]);

#import <PVSDK/PVEyeCamera.h>

#import "PVSDKManager.h"

#import "PVProductHelper.h"
#import "PVFlightHelper.h"
#import "PVFlightRemote.h"

#import "PVCameraState.h"
//#import "PVEyeCamera.h"
#import "PVEyeCameraSettingsDef.h"

#import "PVCameraSDCardState.h"

#import "PVWayPointModel.h"

#import "PVGimabal.h"
#import "PVMount.h"
#import "PVBattery.h"
#import "PVLocation.h"
#import "PVNavigation.h"

