/**
 * @file PVFlightControllerState.h
 * @author Layne
 *
 * @brief  Flight state files
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef enum _PVFlightConnectState{
    PVFlightConnectStateTCPConnecting       = 0,    ///< Link connecting
    PVFlightConnectStateTCPSuccess          = 1,    ///< Link connected successfully.
    PVFlightConnectStateTCPDisConnect       = 2,    ///< The connection of link  was interrupted.
    PVFlightConnectStateTCPTimeOut          = 3,    ///< The connection of link was timed out.
    PVFlightConnectStateTCPFailed           = 4,    ///< Failed to connect the link .
    PVFlightConnectStateHeartTimeout        = 5,    ///< Heartbeat timeout.
    PVFlightConnectRemoteConnected          = 6,    ///< Standard remote controller has been connected.
    PVFlightConnectStateTGConnected         = 7,    ///< Gesture-based remote controller has been connected.
    PVFlightConnectStateConnecting          = 8,    ///< Aircraft connecting
    PVFlightConnectStateConnected           = 9,    ///< The aircraft has been connected.
    PVFlightConnectStateDisConnected        = 10,   ///< The connection of aircraft was interrupted.
    PVFlightConnectStateTimeout             = 11,   ///< The connection of aircraft was timed out.
    PVFlightConnectStateFailed              = 12,   ///< Failed to connect the aircraft.
    PVFlightConnectStateHeartTimeoutReply   = 14,   ///< Heartbeat has recovered.
}PVFlightConnectState;


@interface PVFlightControllerState : NSObject

/**
 Connection status of aircraft
 */
@property (nonatomic,assign) PVFlightConnectState flightConnectState;

@end
