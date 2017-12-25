//
//  PVFlightRemote.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import <PVSDK/PVSDK.h>
#import "PVBaseComponent.h"

typedef NS_ENUM(NSUInteger,PVFlightRemoteConnectState){
    /**
     *  connecting
     */
    PVFlightRemoteConnectStateConnecting,
    /**
     * already connected
     */
    PVFlightRemoteConnectStateConnected,
    /**
     *  Gesture-based remote controller is connected
     */
    PVFlightRemoteConnectStateTGConnected,
    /**
     *   connection break off
     */
    PVFlightRemoteConnectStateDisConnected,
    /**
     *  connection time-out
     */
    PVFlightRemoteConnectStateTimeout,
    /**
     *  heartbeat timeout
     */
    PVFlightRemoteConnectStateHeartTimeout,
    /**
     *  Failed to connect
     */
    PVFlightRemoteConnectStateFailed,
};

/**
 *  Remote control mode
 */
typedef NS_ENUM(NSInteger,PVFlightRemoteMode) {
    /**
     *  Mode 1
     */
    PVFlightRemoteModeJapan=1,
    /**
     *  Mode 2
     */
    PVFlightRemoteModeUSA,
    /**
     *  Mode 3
     */
    PVFlightRemoteModeChinese,
    /**
     * Mode 4
     */
    PVFlightRemoteModeCustomer,
};

@interface PVFlightRemote : PVBaseComponent

@property (nonatomic, assign) PVFlightRemoteConnectState remoteConnectState;

/**
 *
 *
 *  @return callback successfully or failure
 */

/**
 Start to connect the remote control

 @param successBlock Success CallBack
 @param failureBlock Failure CallBack
 */
- (void)startConnectRemoteBlockWithSuccessCallBack:(PVCompletionBlock)successBlock FailureCallBack:(PVCompletionBlock)failureBlock;

/**
 *  set remote control mode
 *
 *  @param remoteMode remote control mode
 *  @param block setting results
 */
- (void)setRemoteMode:(PVFlightRemoteMode)remoteMode withCompletion:(PVCompletionBlock)block;

/**
 *  obtain remote control mode
 *
 *  @param block results
 */
- (void)getRemoteModeWithComplection:(void (^_Nonnull)(PVFlightRemoteMode remoteMode,NSError *_Nullable error))block;


@end
