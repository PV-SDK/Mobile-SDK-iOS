//
//  PVFlightController.h
//  PVSDK
//
//  Created by Layne on 16/4/22.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PVBaseComponent.h"
#import "PVFlightControllerState.h"

//typedef void(^PVCompletionBlock)();
typedef void (^_Nullable PVSelfCheckingBlock)(PVSelfCheckingState, NSError * _Nullable);

typedef NS_ENUM(NSInteger,PVStateUpdate){
    //连接状态
    PVFlightConnectStateUpdate,
    //飞行器姿态
    PVAttitudeStateUpdate,
    //飞行器位置
    PVAircraftPositionStateUpdate,
    //飞行器home点
    PVHomePositionStateUpdate,
    //飞行器GPS卫星颗数
    PVGPSCountStateUpdate,
    //飞行器电池电量
    PVBatteryStateUpdate,
    //飞行器模式
    PVModeStateUpdate,
    //飞行器参数
    PVFlighParamSetStateUpdate,
    //飞行器返航点
    PVFlightLandPositionStateUpdate,
    //报警信息
    PVAlarmMessageUpdate,
    //任务状态
    PVAutoMissionStateUpdate,
    //定位方式
    PVFlightLocatingTypeUpdate,
};

//typedef enum : NSUInteger {
//    SendFail,
//    SendSuccess
//} WayPointSendState;
//
//typedef enum: NSUInteger{
//    PVProductTypePowerEgg=1,
//    PVProductTypePowerEye,
//    PVProductTypePowerRay,
//    Unknow,
//}PVProductType;
//
//typedef enum : NSUInteger{
//    PVSafeModeTypeClose,
//    PVSafeModeTypeOpen,
//}PVSafeModeType;
//
////返航点参数
//typedef enum _PVSDK_TAKEOFFLAND_STATUS {
//    PVSDK_TAKEOFFLAND_STATUS_RC_POSITION = (uint64_t)1<<2, ///返航点为用户位置
//    PVSDK_TAKEOFFLAND_STATUS_TAKEOFF = (uint64_t)1<<3, ///设置返航点为起飞位置
//    PVSDK_TAKEOFFLAND_STATUS_APP_SET_POSITION = (uint64_t)1<<4, ///< 设置返航点为地图选点
//    PVSDK_TAKEOFFLAND_STATUS_RTL_YES = (uint64_t)1<<5, ///提示用户是否返航，用户选择“是”
//    PVSDK_TAKEOFFLAND_STATUS_RTL_NO = (uint64_t)1<<6, ///弹出对话框提示用户是否返航，用户选择“否”
//} PVSDK_TAKEOFFLAND_STATUS;
//
///**
// *  飞机敏感度设置方向
// */
//typedef NS_ENUM(NSInteger,PVOperationSensitivityOrientation) {
//    /**
//     *  pitch
//     */
//    PVOperationSensitivityOrientationPitch,
//    /**
//     *  roll
//     */
//    PVOperationSensitivityOrientationRoll,
//};
//
///**
// *  脚架收放模式
// */
//typedef NS_ENUM(NSInteger,PVHlemMode) {
//    /**
//     *  手动
//     */
//    PVHlemModeManual,
//    /**
//     *  自动
//     */
//    PVHlemModeAuto,
//};
//
///**
// *  脚架当前状态
// */
//typedef NS_ENUM(NSInteger,PVHlemCurrentStatus) {
//    /**
//     *  开启
//     */
//    PVHlemCurrentStatusOpen,
//    /**
//     *  关闭
//     */
//    PVHlemCurrentStatusClose,
//    /**
//     *  操作中
//     */
//    PVHlemCurrentStatusOperating,
//};
//
///**
// *  失控行为操作
// */
//typedef NS_ENUM(NSInteger,PVOutOfControlsafeOperation) {
//    /**
//     *  返航
//     */
//    PVOutOfControlsafeOperationGoHome,
//    /**
//     *  悬停
//     */
//    PVOutOfControlsafeOperationLoiter,
//};
//
///**
// *  飞控固件升级状态
// */
//typedef NS_ENUM(NSInteger,PVFlightFirmwareUpgradeState) {
//    /**
//     *  升级失败
//     */
//    PVFlightFirmwareUpgradeStateFailed,
//    /**
//     *  升级成功
//     */
//    PVFlightFirmwareUpgradeStateSuccess,
//    /**
//     *  升级中
//     */
//    PVFlightFirmwareUpgradeStateUpgrading,
//};
//
//typedef struct {
//    float land_lat;
//    float land_lon;
//    float land_alt;
//    PVSDK_TAKEOFFLAND_STATUS status;//1代表遥控器位置，2代表飞机起点，3代表地图选点，仅3需要设置经纬度
//} PVSDK_RETURNPOINT_PARAM;
//
//typedef struct {
//    float x;
//    float y;
//    float z;
//    float radius;
//    int speed;
//    BOOL isClockwise;
//    BOOL isPause;
//} PVSDK_AUTOCIRCLE_PARAM;
//
//typedef struct {
//    float p1x; /*< x position 1 / Longitude 1*/
//    float p1y; /*< y position 1 / Longitude 1*/
//    float p1z; /*< z position 1 / Altitude 1*/
//    float p2x; /*< x position 2 / Latitude 2*/
//    float p2y; /*< y position 2 / Longitude 2*/
//    float p2z; /*< z position 2 / Altitude 2*/
//    int frame; /*< Coordinate frame, as defined by MAV_FRAME enum in mavlink_types.h. Can be either global, GPS, right-handed with Z axis up or local, right handed, Z axis down.*/
//} PVSDK_SAFEAREA_PARAM;
//
//typedef struct{
//    PVHlemMode hlemMode;
//    PVHlemCurrentStatus currentStatus;
//}PVHlemState;
//
///**
// *  飞行日志头
// */
//typedef struct {
//    int type; ///< 飞行记录类型
//    char *fileNameWithPath; ///< 全路径文件名，SDK会在后面插入当前时间作为文件唯一标识
//} PVFLIGHT_RECORD_START_INFO;
//
///**
// *  飞行日志尾
// */
//typedef struct {
//    union {
//        struct {
//            char *flightDate;
//            char *cityName;
//            char *flightPosition;
//            int userId;
//            char *aircraftId;
//            long longVideo;
//            long flightTime;
//            bool isCollection;
//            float maxAltitude;
//            float flightDistance;
//            int cameraCounts;
//            float maxSpeed;
//            char *psn;
//        };
//    };
//} PVFLIGHT_RECORD_STOP_INFO;


@class PVFlightController;
@protocol PVFlightControllerDelegate <NSObject>

@optional
/**
 *  飞机连接时回调
 *
 *  @param fc    flightController
 *  @param state 飞机连接状态
 */
- (void)flightController:(PVFlightController *)fc didUpdateFlightConnectState:(PVFlightConnectState)state;

/**
 *  飞机信息改变时回调
 *
 *  @param fc    flightController
 *  @param state 飞机信息
 */
- (void)flightController:(PVFlightController *)fc didUpdateFlightState:(PVFlightControllerState *)state stateType:(PVStateUpdate)stateUpdate;

/**
 *  航点发送后回调
 *
 *  @param fc       flightController
 *  @param sendSate 发送状态
 */
//- (void)flightController:(PVFlightController *)fc wayPointSendState:(WayPointSendState)sendSate;

/**
 *  报警信息更新回调
 *
 *  @param fc           flightController
 *  @param alarmMessage 报警信息
 */
//- (void)flightController:(PVFlightController *)fc didUpdateAlarmMessage:(PVAlarmMessage)alarmMessage;

@end

@interface PVFlightController : PVBaseComponent
@property (nonatomic,strong) PVFlightControllerState *flightControllerState;
//设备当前连接状态
@property (nonatomic,assign)PVFlightConnectState flightConnectState;
@property (nonatomic,weak)id <PVFlightControllerDelegate>delegate;

///**
// *  获取飞机型号
// *
// *  @param block 获取结果
// */
//- (void)getProductTypeWithComplection:(void (^_Nonnull)(PVProductType type,NSError *_Nullable error))block;
//
///**
// *  获取飞控固件版本
// *
// *  @param block 获取结果
// */
//- (void)getFCVersionWithComplection:(void (^_Nonnull)(int version,NSError *_Nullable error))block;
//
///**
// *  获取飞机UDID
// *
// *  @param block 获取结果
// */
//- (void)getProductUDIDWithComplection:(void (^_Nonnull)(NSInteger productUDID,NSError *_Nullable error))block;

/**
 *  开始连接飞机
 *
 *  @return 成功与失败是指连接方法的调用，不是飞机连接成功与否，飞机连接需要检测飞机连接状态属性值flightConnectState（PVFlightControllerState中）
 */
- (void)startConnectFlightBlockWithSuccess:(void (^)(PVFlightController *fc))success failure:(void (^)(PVFlightController *fc))failure;

/**
 *  断开飞机连接
 *
 *  @return 成功返回YES，否则返回NO
 */
- (BOOL)stopConnectFlight;

/**
 *  重连飞机
 *
*/
- (void)reConnectTCPAndAircraft;

///**
// *  启动航点飞行
// *
// *  @param success 成功执行block
// *  @param failure 失败block
// */
//- (void)startWayPointBlockWithSuccess:(void (^)(PVFlightController *fc))success failure:(void (^)(PVFlightController *fc))failure;
//
///**
// *  飞机悬停
// *
// *  @param success 成功执行block
// *  @param failure 失败执行block
// */
//- (void)autoLoiterBlockWithSuccess:(void (^)(PVFlightController *fc))success failure:(void (^)(PVFlightController *fc))failure;
//
///**
// *  执行任务
// *
// *  @param success 成功执行block
// *  @param failure 失败执行block
// */
//- (void)autoMissionBlockWithSuccess:(void (^)(PVFlightController *fc))success failure:(void (^)(PVFlightController *fc))failure;
//
///**
// *  跟随模式
// *
// *  @param success 成功block
// *  @param failure 失败block
// */
//- (void)followMeBlockWithSuccess:(void (^)(PVFlightController *fc))success failure:(void (^)(PVFlightController *fc))failure;
//
///**
// *  返航点设置
// *
// *  @param success success
// *  @param failure failure 
// */
//- (void)setReturnPoint:(PVSDK_RETURNPOINT_PARAM)returnPoint andWithSuccess:(void (^)(PVFlightController *))success failure:(void (^)(PVFlightController *))failure;
//
///**
// *  环绕模式
// *
// *  @param circleData 环绕参数
// *  @param success    successBlock
// *  @param failure    failureBlock
// */
//- (void)autoCircleWithData:(PVSDK_AUTOCIRCLE_PARAM)circleData andWithSuccess:(void (^)(PVFlightController *))success failure:(void (^)(PVFlightController *))failure;
//
///**
// *  切回上一次模式
// */
//- (void)setLastMode;
//
///**
// *  飞机当前是否解锁
// *
// *  @return YES为解锁，NO为加锁
// */
//- (BOOL)isArmed;
//
///**
// *  开始飞机自检
// *
// *  @param block 
// */
//- (void)startSelfCheckWithCompletion:(PVSelfCheckingBlock)block;
//
///**
// *  设置飞机敏感度
// *
// *  @param orientation 方向
// *  @param value       数值
// *  @param block       回调结果
// */
//- (void)setOperationalSensitivityWithOrientation:(PVOperationSensitivityOrientation)orientation Value:(float)value withCompletion:(PVCompletionBlock)block;
//
///**
// *  设置视觉定位开启和关闭
// *
// *  @param enable  YES为开启  NO为关闭
// *  @param block   设置结果
// */
//- (void)setVisualLocating:(BOOL)enable withCompletion:(PVCompletionBlock)block;
//
///**
// *  启动自拍
// *
// *  @param block 结果回调
// */
//- (void)startAutodyneWithCompletion:(PVSelfCheckingBlock)block;
//
///**
// *  设置安全区域
// *
// *  @param safeArea 安全区域参数
// *  @param block    设置结果回调
// */
//- (void)setSafeArea:(PVSDK_SAFEAREA_PARAM)safeArea  withCompletion:(PVCompletionBlock)block;
//
///**
// *  获取脚架当前状态
// *
// *  @param block 回调结果
// */
//- (void)getHlemStateWithCompletion:(void (^_Nonnull)(PVHlemState hlemState,NSError *_Nonnull error))block;
//
///**
// *  设置脚架收放模式
// *
// *  @param hlemMode 模式
// */
//- (void)setHlemMode:(PVHlemMode)hlemMode;
//
///**
// *  设置失控行为安全操作
// *
// *  @param operation  安全操作
// *  @param completion 设置结果回调
// */
//- (void)setOutOfControlsafeOperation:(PVOutOfControlsafeOperation)operation withCompletion:(PVCompletionBlock)block;
//
///**
// *  获取失控行为安全操作
// *
// *  @param block 获取结果
// */
//- (void)getOutOfControlsafeOperationWithCompletion:(void (^_Nonnull)(PVOutOfControlsafeOperation operation, NSError *_Nullable error))block;
//
///**
// *  开启脚架
// */
//- (void)openHlem;
//
///**
// *  关闭脚架
// */
//- (void)closeHlem;
//
///**
// *  获取产品激活码
// *
// *  @param block 获取结果
// */
//- (void)getProductValidateKeyWithComplection:(void (^_Nonnull)(NSString *_Nullable validateKey,NSError *_Nullable error))block;
//
//
///**
// 获取PSN码
//
// @param block 获取结果
// */
//- (void)getProductPSNWithComplection:(void (^)(NSString * _Nullable, NSError * _Nullable))block;
//
///**
// *  激活产品
// *
// *  @param block 激活结果
// */
//- (void)validateProductWithComplection:(PVCompletionBlock)block;
//
//- (void)unValidateProductWithComplection:(PVCompletionBlock)block;
//
///**
// *  获取飞机激活状态
// *
// *  @param block 获取结果
// */
//- (void)getProductValidateStateWithComplection:(void (^_Nonnull)(PVProductValidateState validateState,NSError *_Nullable error))block;
//
///**
// *  开启飞行日志
// *
// *  @param startDiary 飞行日志
// */
//- (void)startRecordDiary:(PVFLIGHT_RECORD_START_INFO)startDiary;
//
///**
// *  停止飞行日志
// *
// *  @param stopDiary 飞行日志
// */
//- (void)stopRecordDiary:(PVFLIGHT_RECORD_STOP_INFO)stopDiary;
//
///**
// *  设置安全模式开启或关闭
// *
// *  @param block 开启结果(成功/失败）
// */
//- (void)setSafeMode:(PVSafeModeType)safeModeType WithComplection:(PVCompletionBlock)block;
//
///**
// 获取安全模式开启或关闭
//
// @param block 获取结果
// */
//- (void)getSafeModeWithComplection:(void (^_Nonnull)(PVSafeModeType type,NSError *_Nullable error))block;
//
///**
// *  获取飞行时长
// *
// *  @param block 获取结果
// */
//- (void)getFlyTimeWithComplection:(void (^_Nonnull)(NSInteger flightTime,NSError *_Nullable error))block;
//
///**
// *  设置低电量降落阈值
// *
// *  @param value 降落阈值
// *  @param block 设置结果
// */
//- (void)setLandOfLowBatteryValue:(NSInteger)value WithComplection:(PVCompletionBlock)block;
//
///**
// *  获取低电量降落阈值
// *
// *  @param block 返回结果
// */
//- (void)getLandOfLowBatteryValueWithComplection:(void (^_Nonnull)(NSInteger lowBatteryValue,NSError *_Nullable error))block;
//
///**
// *  更新当前距离传感器距离
// *
// *  @param block 返回结果
// */
//- (void)updateSensorDistanceWithComplection:(void (^_Nonnull)(NSInteger distance,NSError *_Nullable error))block;
//
///**
// 切换固定天线
// 
// @param no 天线序号
// @param block 返回结果
// */
//- (void)changeAntenna:(NSInteger)no WithComplection:(PVCompletionBlock)block;
//
//
///**
// 复位飞机参数（用于心跳超时时的参数复位，以便在心跳恢复的时候重新接受参数）
//
// @param block 复位结果（暂不可用）
// */
//- (void)resetFlightParamsWithComplection:(PVCompletionBlock)block;
//
//
///**
// 设置飞机禁飞区功能开启和关闭
//
// @param isOpen 开启/关闭
// @param block 设置结果
// */
//- (void)setNoFlyZoneOpen:(BOOL)isOpen withComplection:(PVCompletionBlock)block;
//
///**
// 获取禁飞区功能开关状态
//
// @param block 返回结果
// */
//- (void)getNoFlyZoneOpenWithComplection:(void (^_Nonnull)(BOOL isOpen,NSError *_Nullable error))block;
//
//
///**
// 设置最大飞行高度
//
// @param altitude 高度
// @param block 设置结果
// */
//- (void)setMaxAltitude:(NSInteger)altitude withComplection:(PVCompletionBlock)block;
//
///**
// 获取最大飞行高度
// 
// @param block 返回结果
// */
//- (void)getMaxAltitudeWithComplection:(void (^_Nonnull)(NSInteger altitude,NSError *_Nullable error))block;
//
///**
// *飞机起飞
// */
//- (void)takeOff;
//
///**
// *  飞机加锁
// */
//- (void)armFlight;
//
///**
// *  飞机解锁
// */
//- (void)disArmFlight;
//
///**
// *  降落
// */
//- (void)autoLand;
//
///**
// *  自动返航
// */
//- (void)returnToLand;
//
///**
// *  升级飞控固件
// */
//- (void)startFlightFirmwareUpdate:(NSString *_Nullable)filePath WithComplection:(void (^_Nonnull)(PVFlightFirmwareUpgradeState upgradeState,NSInteger upgradeProcess,NSError *_Nullable NSError))block;
//
///**
// 超声版本
// 
// @param block
// */
//- (void)getSonarVersionWithComplection:(void(^_Nonnull)(float version,NSError *_Nullable error))block;
//
///**
// 超声bootloader版本
// 
// @param block
// */
//- (void)getSonarBootloaderVersionWithComplection:(void(^_Nonnull)(float version,NSError *_Nullable error))block;
//
//
///**
// 光流版本
//
// @param block
// */
//- (void)getOpticalFlowVersionComplection:(void(^_Nonnull)(int version,NSError *_Nullable error))block;
//
///**
// 光流Bootloader版本
// 
// @param block
// */
//- (void)getOpticalFlowBootloaderVersionComplection:(void(^_Nonnull)(float version,NSError *_Nullable error))block;
//
//
///**
// 解锁时间
// 
// @param block
// */
//- (void)getFlightArmTimeWithComplection:(void (^_Nonnull)(int armTime, NSError * _Nullable))block;

@end
