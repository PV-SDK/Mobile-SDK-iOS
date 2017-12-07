
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

#import "PVFlightController.h"
#import "PVCamera.h"
#import "PVGimabal.h"
#import "PVMountController.h"
#import "PVCameraCallback.h"
#import "PVBattery.h"
#import "PVRemoteController.h"

