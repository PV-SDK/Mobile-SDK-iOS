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
- (void)pv_sdkManager:(PVSDKManager *)manager didUpdateConnectStateWithHelper:(PVProductHelper *)helper;

@optional
- (void)pv_sdkManager:(PVSDKManager *)manager didUpdateFlightModeWithHelper:(PVFlightHelper *)helper;

@end

@interface PVSDKManager : NSObject

@property (nonatomic, weak) id <PVSDKManagerDelegate>delegate;

+ (PVSDKManager *)manager;

- (void)startConnectToProduct;

- (void)stopConnectToProduct;

- (void)reConnectTCPAndSDK;


@end
