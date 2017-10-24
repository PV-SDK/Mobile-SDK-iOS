//
//  PVRayCameraManager.h
//  PVRayCameraDemo
//
//  Created by Gavin.Guo on 2017/4/11.
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PVBaseComponent.h"

//////////////////////////////////////////////////
/// @brief 设置相机客户端信息的回调结果
///
/// 定义关于设置相机客户端信息的回调结果
//////////////////////////////////////////////////
typedef enum POWERRAY_CAMERA_SET_CLIENT_INFO_CALLBACK_INFO {
    POWERRAY_CAMERA_SET_CLIENT_INFO_CALLBACK_INFO_SUCCESS = 0,
    POWERRAY_CAMERA_SET_CLIENT_INFO_CALLBACK_INFO_FAILED
} POWERRAY_CAMERA_SET_CLIENT_INFO_CALLBACK_INFO;
//////////////////////////////////////////////////
/// @brief PowerRay相机启动会话回调结果
///
/// PowerRay相机启动会话回调时的结果参数
//////////////////////////////////////////////////
typedef enum POWERRAY_CAMERA_STARTSESSION_CALLBACK_INFO {
    POWERRAY_CAMERA_STARTSESSION_CALLBACK_INFO_SUCCESS = 0,
    POWERRAY_CAMERA_STARTSESSION_CALLBACK_INFO_TIMEOUT = 1,
    POWERRAY_CAMERA_STARTSESSION_CALLBACK_INFO_FAILED = 2
} POWERRAY_CAMERA_STARTSESSION_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief PowerRay相机停止会话回调结果
///
/// PowerRay相机停止会话回调时的结果参数
//////////////////////////////////////////////////
typedef enum POWERRAY_CAMERA_STOPSESSION_CALLBACK_INFO {
    POWERRAY_CAMERA_STOPSESSION_CALLBACK_INFO_SUCCESS = 0,
    POWERRAY_CAMERA_STOPSESSION_CALLBACK_INFO_TIMEOUT = 1,
    POWERRAY_CAMERA_STOPSESSION_CALLBACK_INFO_FAILED = 2
} POWERRAY_CAMERA_STOPSESSION_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 相机拍照的回调参数
///
/// 定义关于相机拍照的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_TAKE_PHOTO_CALLBACK_INFO {
    int rval;
    char *captureMode; ///< 拍照模式
    char *param; ///< 若captureMode为“precise quality”，则param为照片路径，否则为空
} POWERRAY_CAMERA_TAKE_PHOTO_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief PowerRay相机停止会话回调结果
///
/// PowerRay相机停止会话回调时的结果参数
//////////////////////////////////////////////////
typedef enum POWERRAY_CAMERA_RECORDSTART_CALLBACK_INFO {
    POWERRAY_CAMERA_RECORDSTART_CALLBACK_INFO_SUCCESS = 0,
    POWERRAY_CAMERA_RECORDSTART_CALLBACK_INFO_TIMEOUT = 1,
    POWERRAY_CAMERA_RECORDSTART_CALLBACK_INFO_FAILED = 2
} POWERRAY_CAMERA_RECORDSTART_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 设置相机参数的参数类型
///
/// 定义关于设置相机参数的参数类型信息
//////////////////////////////////////////////////
typedef enum POWERRAY_CAMERA_SET_SETTING_PARAM_TYPE {
    POWERRAY_CAMERA_SET_SETTING_PARAM_TYPE_INT = 0,
    POWERRAY_CAMERA_SET_SETTING_PARAM_TYPE_FLOAT = 1,
    POWERRAY_CAMERA_SET_SETTING_PARAM_TYPE_DOUBLE = 2,
    POWERRAY_CAMERA_SET_SETTING_PARAM_TYPE_STRING = 3
} POWERRAY_CAMERA_SET_SETTING_PARAM_TYPE;

//////////////////////////////////////////////////
/// @brief 相机录像的回调参数
///
/// 定义关于相机录像的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_RECORD_STOP_CALLBACK_INFO {
    int rval;
    char *param; ///< 照片路径
} POWERRAY_CAMERA_RECORD_STOP_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 设置相机参数的回调参数
///
/// 定义关于设置相机参数的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_SET_SETTING_CALLBACK_INFO {
    int rval;
    char *type; ///< 设置完成的相机参数
} POWERRAY_CAMERA_SET_SETTING_CALLBACK_INFO;

////////////////////////////////////////
/// @brief 连接相机回调的状态
///
/// 定义了连接相机状态回调时的状态值
////////////////////////////////////////
typedef enum POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO {
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_CONTROL_CONNECTED = 0,
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_CONTROL_DISCONNECTED,
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_CONTROL_TIMEOUT,
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_CONTROL_FAILED,
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_DATA_CONNECTED,
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_DATA_DISCONNECTED,
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_DATA_TIMEOUT,
    POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO_DATA_FAILED
} POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 获取相机参数的回调参数
///
/// 定义关于获取相机参数的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_GET_SETTING_CALLBACK_INFO {
    int rval;
    char *type; ///< 获取完成的相机参数
    char *param; ///< 获取完成的相机参数
} POWERRAY_CAMERA_GET_SETTING_CALLBACK_INFO;

////////////////////////////////////////////////////
///// @brief 获取当前所有的相机参数的回调参数
/////
///// 定义关于获取相机参数的回调参数
////////////////////////////////////////////////////
//typedef struct POWERRAY_CAMERA_GET_ALL_CURRENT_SETTINGS_CALLBACK_INFO {
//    int rval;
//    char *param; ///< 获取完成的相机参数
//} POWERRAY_CAMERA_GET_ALL_CURRENT_SETTINGS_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 获取当前所有的相机参数的回调参数
///
/// 定义关于获取相机参数的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_GET_ALL_CURRENT_SETTINGS_CALLBACK_INFO {
    int rval;
    char *param; ///< 获取完成的相机参数
    char *camera_clock;
    char *video_resolution;
    char *video_quality;
    char *video_split;
    char *video_stamp;
    char *slow_motion;
    char *streaming;
    char *capture_mode;
    char *photo_size;
    char *burst_num;
    char *photo_stamp;
    char *digital_effect;
    char *ev_bias;
    char *ISO;
    char *sharpness;
    char *scene;
    char *wb;
    char *system_type;
    char *default_setting;
    char *ver;
} POWERRAY_CAMERA_GET_ALL_CURRENT_SETTINGS_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 上传文件到相机的参数
///
/// 定义关于上传文件到相机的参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_PUT_FILE_INFO {
    char *fileName; ///< 要上传到当前路径下的文件名或全路径文件名
    unsigned long long size;
    int offset;
    char *md5sum;
} POWERRAY_CAMERA_PUT_FILE_INFO;


//////////////////////////////////////////////////
/// @brief 向相机上传文件完成的回调参数
///
/// 定义关于向相机上传文件完成的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_PUT_FILE_COMPLETE_CALLBACK_INFO {
    char *type;
    unsigned long long param;
    char *md5sum;
} POWERRAY_CAMERA_PUT_FILE_COMPLETE_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 上传文件到相机的回调参数
///
/// 定义关于上传文件到相机的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_PUT_FILE_CALLBACK_INFO {
    int rval;
} POWERRAY_CAMERA_PUT_FILE_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 相机固件升级完成的回调参数
///
/// 定义关于相机固件升级完成的回调参数
//////////////////////////////////////////////////
typedef struct POWERRAY_CAMERA_FW_UPGRADE_COMPLETE_CALLBACK_INFO {
    char *type;
} POWERRAY_CAMERA_FW_UPGRADE_COMPLETE_CALLBACK_INFO;


typedef enum : NSUInteger {
    PVRay_ControlConnectedStateConnected      = 0,
    PVRay_ControlConnectedStateDisConnected   = 1,
    PVRay_ControlConnectedStateTimeout        = 2,
    PVRay_ControlConnectedStateFailed         = 3
} PVRay_ControlConnectedState;

typedef enum : NSUInteger {
    PVRay_DataConnectedStateConnected     = 0,
    PVRay_DataConnectedStateDisConnected  = 1,
    PVRay_DataConnectedStateTimeout       = 2,
    PVRay_DataConnectedStateFailed        = 3
} PVRay_DataConnectedState;

typedef enum : NSUInteger {
    PVRay_SocketConnectedStateConnected     = 0,
    PVRay_SocketConnectedStateDisConnected  = 1
} PVRay_SocketConnectedState;

typedef enum : NSUInteger {
    PVRay_ConnectedCameraStateConnected     = 0,
    PVRay_ConnectedCameraStateDisConnected  = 1
} PVRay_ConnectedCameraState;

typedef enum : NSUInteger {
    PVRay_HoldSessionStateOFF    = 0,
    PVRay_HoldSessionStateON  = 1
} PVRay_HoldSessionState;

@protocol PVRayCameraManagerDelegate <NSObject>

/**
 上传文件头代理回调
 
 @param info 上传回调 .rval=0代表成功
 */
- (void)PVRayCameraManagerPutFileCallBack:(POWERRAY_CAMERA_PUT_FILE_CALLBACK_INFO)info;

/**
 文件传送结束回调
 
 @param uploadInfo 结束状态
 */
- (void)PVRayCameraUploadFileCallBack:(POWERRAY_CAMERA_PUT_FILE_COMPLETE_CALLBACK_INFO)uploadInfo;

/**
 固件升级回调
 
 @param upgradenfo 升级结果
 */
- (void)PVRayCameraManagerUpgradeCallBack:(POWERRAY_CAMERA_FW_UPGRADE_COMPLETE_CALLBACK_INFO)upgradenfo;

/**
 文件上传进度

 @param progress 上传进度
 */
- (void)PVRayCameraUploadProgress:(Float32)progress;

@end

@interface PVRayCameraManager : PVBaseComponent


@property (nonatomic,assign) id<PVRayCameraManagerDelegate> delegate;

+ (PVRayCameraManager *)shareManager;


/**
 连接-控制链路-的状态
 */
@property (nonatomic, assign) PVRay_ControlConnectedState controlConnectedState;

/**
 连接-数据层-的状态
 */
@property (nonatomic, assign) PVRay_DataConnectedState dataConnectedState;

/**
 连接-Socket-的状态
 */
@property (nonatomic, assign) PVRay_SocketConnectedState socketConnectedState;

/**
 连接-相机-的状态
 */
@property (nonatomic, assign) PVRay_ConnectedCameraState connectedCameraState;

/**
 初始化 SDK Manager
 */
- (void)initManagerWithCallBack:(void (^)(const POWERRAY_CAMERA_CONNECTION_CALLBACK_INFO infor))block;

/**
 设置链接相机的信息
 
 @param host IP Address
 @param isTCP 是否是 TCP 连接方式
 @param block CallBackBlock
 */
- (void)setClientInfoWithHost:(NSString *)host IsTCP:(BOOL)isTCP CallBack:(void (^)(const POWERRAY_CAMERA_SET_CLIENT_INFO_CALLBACK_INFO infor))block;
/**
 Start Session Method
 
 @param block CallBackBlock
 */
- (void)startSessionMethodCallBack:(void (^)(const POWERRAY_CAMERA_STARTSESSION_CALLBACK_INFO infor))block;

/**
 Stop Session Method
 
 @param block CallBackBlock
 */
- (void)stopSessionMethodCallBack:(void (^)(const POWERRAY_CAMERA_STOPSESSION_CALLBACK_INFO infor))block;

/**
 Take Photo Method
 
 @param block CallBackBlock
 */
- (void)takePhotoMethodCallBack:(void (^)(const POWERRAY_CAMERA_TAKE_PHOTO_CALLBACK_INFO infor))block;

/**
 Record Start Method
 
 @param block CallBackBlock
 */
- (void)recordStartMethodCallBack:(void (^)(const POWERRAY_CAMERA_RECORDSTART_CALLBACK_INFO infor))block;

/**
 Record Stop Method
 
 @param block CallBackBlock
 */
- (void)recordStopMethodCallBack:(void (^)(const POWERRAY_CAMERA_RECORD_STOP_CALLBACK_INFO infor))block;

/**
 Get Camera Current Setting Method
 
 @param name Setting Name
 @param block CallBackBlock
 */
- (void)getCameraCurrentSettingMethodWithSettingName:(NSString *)name CallBack:(void (^)(const POWERRAY_CAMERA_GET_SETTING_CALLBACK_INFO infor))block;

/**
 Set Camera Setting Method
 
 @param type Parameter Type
 @param param Parameter
 @param paramType Set Parameter Type
 @param block CallBackBlock
 */
- (void)setCameraSettingMethodWithType:(NSString *)type Param:(NSString *)param ParamType:(POWERRAY_CAMERA_SET_SETTING_PARAM_TYPE)paramType CallBack:(void (^)(const POWERRAY_CAMERA_SET_SETTING_CALLBACK_INFO infor))block;

/**
 Get All Current Camera Setting

 @param block CallBackBlock
 */
-(void)getAllCurrentCameraSettingWithCompletion:(void (^)(const POWERRAY_CAMERA_GET_ALL_CURRENT_SETTINGS_CALLBACK_INFO infor))block;

/**
 固件升级上传
 
 @param info 上传信息
 */
- (void)rayCameraPutFileWith:(POWERRAY_CAMERA_PUT_FILE_INFO)info;

/**
 发送文件流到相机
 
 @param 文件地址
 */
- (void)rayCameraUploadData:(NSString * )filePath;

/**
 固件升级
 
 @param filePath 升级结果
 */
- (void)rayCameraBurninFwWithFilePath:(NSString *)filePath withCompletion:(void (^_Nonnull)(int rval, NSError *_Nullable error))block;
;

/**
 设置token强制占有

 @param state PVRay_HoldSessionStateYES 强占有(其他设备不能再连接)
              PVRay_HoldSessionStateNO  非占有(其他设备允许连接)
 */
- (void)setHoldSessionState:(PVRay_HoldSessionState)state;

@end
