/**
 * @file PVFlightControllerState.h
 * @author Layne
 *
 * @brief 飞行状态文件
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef enum _PVFlightConnectState{
    PVFlightConnectStateTCPConnecting=0, ///< 链路连接中
    PVFlightConnectStateTCPSuccess=1, ///< 链路连接成功
    PVFlightConnectStateTCPDisConnect=2, ///< 链路连接断开
    PVFlightConnectStateTCPTimeOut=3, ///< 链路连接超时
    PVFlightConnectStateTCPFailed=4, ///< 链路连接失败
    PVFlightConnectStateHeartTimeout=5, ///< 心跳超时
    PVFlightConnectRemoteConnected =6, ///< 标准遥控器已连接
    PVFlightConnectStateTGConnected=7, ///< 体感遥控器已连接
    PVFlightConnectStateConnecting=8, ///< 飞行器连接中
    PVFlightConnectStateConnected=9, ///< 飞行器已连接
    PVFlightConnectStateDisConnected=10, ///< 飞行器连接断开
    PVFlightConnectStateTimeout = 11, ///< 飞行器连接超时
    PVFlightConnectStateFailed=12, ///< 飞行器连接失败
    PVFlightConnectStateHeartTimeoutReply=14, ///< 心跳恢复
}PVFlightConnectState;


@interface PVFlightControllerState : NSObject

/**
 *  飞行器连接状态
 */
@property (nonatomic,assign) PVFlightConnectState flightConnectState;

@end
