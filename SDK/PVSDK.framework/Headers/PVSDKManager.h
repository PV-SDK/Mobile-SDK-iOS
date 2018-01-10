//
//  PVSDKManager.h
//  PVSDK
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PVSDKManager;
@class PVProductHelper;
@class PVFlightHelper;

@protocol PVSDKManagerDelegate <NSObject>

@required

/**
 [PVSDKManagerDelegate] Update Connect State
 
 @param manager PVSDKManager
 @param helper PVProductHelper
 */
- (void)pv_sdkManager:(PVSDKManager *)manager didUpdateConnectStateWithHelper:(PVProductHelper *)helper;

@optional

/**
 [PVSDKManagerDelegate] Update Flight Mode delegate
 
 @param manager PVSDKManager
 @param helper PVFlightHelper
 */
- (void)pv_sdkManager:(PVSDKManager *)manager didUpdateFlightModeWithHelper:(PVFlightHelper *)helper;

@end

@interface PVSDKManager : NSObject

@property (nonatomic, weak) id <PVSDKManagerDelegate>delegate;

/**
 Instantiation PVSDKManager
 
 @return PVSDKManager
 */
+ (instancetype)manager;

/**
 Start connect to product.
 */
- (void)startConnectToProduct;

/**
 Stop connect to product.
 */
- (void)stopConnectToProduct;

/**
 Reconnect TCP & SDK
 */
- (void)reConnectTCPAndSDK;


@end

