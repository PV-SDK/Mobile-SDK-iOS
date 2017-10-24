//
//  PVRayCameraSDCardManager.h
//  PVRayCameraDemo
//
//  Created by Gavin.Guo on 2017/4/12.
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>

//////////////////////////////////////////////////
/// @brief 进入相机目录的回调参数
///
/// 定义关于进入相机目录的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_CD_DIRECTORY_CALLBACK_INFO {
    int rval;
    char *pwd;
} POWERRAY_CAMERA_CD_DIRECTORY_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief PowerRay相机列出文件参数
///
/// PowerRay相机列出文件的参数
//////////////////////////////////////////////////
typedef enum _POWERRAY_CAMERA_LS_INFO {
    POWERRAY_CAMERA_LS_INFO_ADD_NONE = 0,
    POWERRAY_CAMERA_LS_INFO_ADD_CREATE_DATE = 1,
    POWERRAY_CAMERA_LS_INFO_ADD_FILE_SIZE = 2,
    POWERRAY_CAMERA_LS_INFO_ADD_BOTH = 3
} POWERRAY_CAMERA_LS_INFO;

//////////////////////////////////////////////////
/// @brief 列出相机目录文件的回调参数
///
/// 定义关于列出相机目录文件的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_LS_FILE_CALLBACK_INFO {
    int rval;
    char **fileNames;
    int fileCount;
} POWERRAY_CAMERA_LS_FILE_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 格式化相机SD卡的回调参数
///
/// 定义关于格式化相机SD卡的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_FORMAT_CALLBACK_INFO {
    int rval;
} POWERRAY_CAMERA_FORMAT_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 获取相机文件的回调参数
///
/// 定义关于获取相机文件的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_GET_FILE_CALLBACK_INFO {
    int rval;
    unsigned long long size;
    unsigned long long remSize;
} POWERRAY_CAMERA_GET_FILE_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 列出相机目录文件的回调参数
///
/// 定义关于列出相机目录文件的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_RECEIVE_DATA_CALLBACK_INFO {
    char *buf;
    int len;
} POWERRAY_CAMERA_RECEIVE_DATA_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 获取相机文件完成的回调参数
///
/// 定义关于获取相机文件完成的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_GET_FILE_COMPLETE_CALLBACK_INFO {
    char *type;
    int bytesSent;
    char *md5sum;
} POWERRAY_CAMERA_GET_FILE_COMPLETE_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief 查询相机容量的回调参数
///
/// 定义关于查询相机容量的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_GET_SPACE_CALLBACK_INFO {
    int rval;
    int param;
} POWERRAY_CAMERA_GET_SPACE_CALLBACK_INFO;

//////////////////////////////////////////////////
/// @brief PowerRa查询相机容量参数
///
/// PowerRay查询相机容量参数
//////////////////////////////////////////////////
typedef enum _POWERRAY_CAMERA_GET_SPACE_INFO {
    POWERRAY_CAMERA_GET_SPACE_INFO_TOTAL = 0,
    POWERRAY_CAMERA_GET_SPACE_INFO_FREE = 1
} POWERRAY_CAMERA_GET_SPACE_INFO;

//////////////////////////////////////////////////
/// @brief 相机获取预览文件的回调参数
///
/// 定义关于相机获取预览文件的回调参数
//////////////////////////////////////////////////
typedef struct _POWERRAY_CAMERA_GETTHUMB_CALLBACK_INFO {
    int rval;
    int size;
    char *type;
    char *md5sum;
} POWERRAY_CAMERA_GETTHUMB_CALLBACK_INFO;


@interface PVRayCameraSDCardManager : NSObject

/**
 CD SD Card Camera File List Path
 
 @param path File List Path
 @param block CallBackBlock
 */
- (void)cdSDCardCameraFileListPath:(NSString *)path CallBackBlock:(void (^)(const POWERRAY_CAMERA_CD_DIRECTORY_CALLBACK_INFO infor))block;
/**
 List SD Card File
 
 @param info POWERRAY_CAMERA_LS_INFO
 @param dirName File Dir Name
 @param block CallBackBlock
 */
- (void)listSDCardFileWithInfo:(const POWERRAY_CAMERA_LS_INFO)info DirName:(NSString *)dirName CallBackBlock:(void (^)(const POWERRAY_CAMERA_LS_FILE_CALLBACK_INFO infor))block;

/**
 Formate SD Card
 
 @param path SD Card Root Path
 @param block CallBackBlock
 */
- (void)formatSDCardPath:(NSString *)path CallBackBlock:(void (^)(const POWERRAY_CAMERA_FORMAT_CALLBACK_INFO infor))block;

/**
 Get SD Card Capacity
 
 @param info POWERRAY_CAMERA_GET_SPACE_INFO
 @param block CallBackBlock
 */
- (void)getSDCardCapacity:(const POWERRAY_CAMERA_GET_SPACE_INFO)info CallBackBlock:(void (^)(const POWERRAY_CAMERA_GET_SPACE_CALLBACK_INFO infor))block;
/**
 Get File
 
 @param filePath File Path
 @param offset Offset
 @param fetchSize Fetch
 @param block Get Back Block
 */
- (void)getFileWithFilePath:(NSString *)filePath Offset:(int)offset FetchSize:(int)fetchSize CallBackBlock:(void (^)(const POWERRAY_CAMERA_GET_FILE_CALLBACK_INFO info))block;

/**
 Get File Receive Data
 
 @param block CallBackBlock
 */
- (void)getFileReceiveDataWithCallBackBlock:(void (^)(const POWERRAY_CAMERA_RECEIVE_DATA_CALLBACK_INFO info))block;

/**
 Get File Complete
 
 @param block CallBackBlock
 */
- (void)getFileCompleteWithCallBackBlock:(void (^)(const POWERRAY_CAMERA_GET_FILE_COMPLETE_CALLBACK_INFO info))block;

/**
 Get Thumb Image
 
 @param fileName File Name
 @param block CallBackBlock
 */
- (void)getThumbImageWithFileName:(NSString *)fileName CallBackBlock:(void (^)(const POWERRAY_CAMERA_GETTHUMB_CALLBACK_INFO info))block;

@end
