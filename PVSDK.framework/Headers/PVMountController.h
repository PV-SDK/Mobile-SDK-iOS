/**
 * @file PVMountController.h
 * @author Layne
 *
 * @brief 挂载接口文件
 *
 */

/**
 * @defgroup PVSDK_CORE_API_MOUNTCONTROL 核心SDK挂载接口
 * @{
 */

/**
 * @page mount-page 挂载接口
 */


#import <Foundation/Foundation.h>

////////////////////////////////////////
/// @brief 挂载设备类型
///
/// 定义了挂载设备的类型
////////////////////////////////////////
typedef enum _PVMountPortType{
    PVMountPortTypeUART, //!< Uart
    PVMountPortTypeCAN, //!< Can
    PVMountPortTypeI2C, //!< I2c
    PVMountPortTypeSPI, //!< Spi
    PVMountPortTypeGPIO, //!< Gpio
}PVMountPortType;

//////////////////////////////////////////////////
/// @brief 挂载设备状态接口参数
///
/// 定义关于挂载设备状态接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_MOUNTSTATE_DEVICE {
    int uart; ///< 串口
    int can; ///< 网口
    int i2c; ///< I2C
    int spi; ///< SPI
    int gpio1; ///< GPIO1
    int gpio2; ///< GPIO2
    int gpio3; ///< GPIO3
} PVSDK_MOUNTAPI_MOUNTSTATE_DEVICE;

//////////////////////////////////////////////////
/// @brief 串口设置接口参数
///
/// 定义关于串口设置接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_UART_PARAM {
    int bps; ///< 串口波特率 0:9600 1:14400 2:19200 3:38400 4:57600 5:115200
    int dataBits; ///< 数据位数 0:8位 1:9位
    int stopBits; ///< 停止位数 0:1位 1:2位
    int parity; ///< 校验 0:无校验 1:奇校验 2:偶校验
    int flowCtrl; ///< 流控 0:无流控 1:RTS有效 2:CTS有效 3:RTS和CTS同时有效
} PVSDK_MOUNTAPI_UART_PARAM;

//////////////////////////////////////////////////
/// @brief Can设置接口参数
///
/// 定义关于Can设置接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_CAN_PARAM {
    int mode; ///< 模式 0:正常模式 1:静默模式 2:回环模式 3:静默回环模式
    int bps; ///< 波特率设置 0:5k 1:10k 2:20k 3:50k 4:100k 5:125k 6:250k 7:500k 8:800k 9:1000k
} PVSDK_MOUNTAPI_CAN_PARAM;

//////////////////////////////////////////////////
/// @brief I2c设置接口参数
///
/// 定义关于I2c设置接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_I2C_PARAM {
    int mode; ///< 模式 0:主模式 1:从模式
    int bps; ///< 速率设置 0:100kbps 1:400kbps
    int deviceAddr; ///< 设备地址 (0~127)
} PVSDK_MOUNTAPI_I2C_PARAM;

//////////////////////////////////////////////////
/// @brief Spi设置接口参数
///
/// 定义关于Spi设置接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SPI_PARAM {
    int mode; ///< 模式 0:主模式 1:从模式
    int bps; ///< 速率设置 0:1Mbps 1:2Mbps 2:4Mbps 3:8Mbps 4:16Mbps
    int firstBit; ///< 有效位先发 0:MSB first 1:LSB first
    int dataSize; ///< 数据大小 0:8位 1:16位
    int crcEnable; ///< Crc使能 0:不使能crc 1:使能crc
} PVSDK_MOUNTAPI_SPI_PARAM;

//////////////////////////////////////////////////
/// @brief Can滤波设置接口参数
///
/// 定义关于Can滤波设置接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_CAN_FILTER_PARAM {
    int number; ///< 滤波器编号 取值范围0~13
    int mode; ///< 滤波器模式 0:mask模式 1:id list模式
    int matchId; ///< ID匹配值
    int maskId; ///< ID掩码值
    int type; ///< ID类型 0:标准ID 1:扩展ID
    int format; ///< 帧格式 0:数据帧 1:远程帧
    int Enable; ///< 滤波器使能 0:不使能 1:使能
} PVSDK_MOUNTAPI_CAN_FILTER_PARAM;

//////////////////////////////////////////////////
/// @brief Can滤波设置接口参数
///
/// 定义关于Can滤波设置接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_GPIO_PARAM {
    int deviceNumber; ///< gpio设备编号 0:gpio1 1:gpio2 2:gpio3
    int periodRatio; ///< 周期值分辨率,取值范围(0~0xffff),单位 1/64us
    int periodLow; ///< 一个周期内低电平持续时间, 取值范围(0~0xffff)
    int periodHigh; ///< 一个周期内高电平持续时间,取值范围(0~0xffff)
} PVSDK_MOUNTAPI_GPIO_PARAM;

//////////////////////////////////////////////////
/// @brief Uart数据接口参数
///
/// 定义关于Uart数据接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_UART_DATA {
    char data[245]; ///< 数据内容
    int len; ///< 数据长度
    int encryption; ///<加密方式 0:不加密 1:xxTea加密 2:RSA加密
} PVSDK_MOUNTAPI_UART_DATA;

//////////////////////////////////////////////////
/// @brief Can数据接口参数
///
/// 定义关于Can数据接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_CAN_DATA {
    int type; ///< id:类型 0:标准 1:扩展id
    int format; ///< 帧格式 0:数据帧 1:远程帧
    int id; ///< 帧id bit0~bit28位有效 bit0~bit10是标准帧 bit11~bit28是扩展帧
    char data[239]; ///< 数据内容
    int len; ///< 数据长度
    int encryption; ///< 加密方式 0:不加密 1:xxTea加密 2:RSA加密
} PVSDK_MOUNTAPI_CAN_DATA;

//////////////////////////////////////////////////
/// @brief I2c数据接口参数
///
/// 定义关于I2c数据接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_I2C_DATA {
    int ramAddr; ///< 内存地址
    int addrType; ///< 地址类型 0:单字节地址 1:双字节地址
    char data[242]; ///< 发送的数据
    int len; ///< 发送数据的长度
    int encryption; ///< 0:不加密 1:xxTea加密 2:RSA加密
} PVSDK_MOUNTAPI_I2C_DATA;

//////////////////////////////////////////////////
/// @brief Spi数据接口参数
///
/// 定义关于Spi数据接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SPI_DATA {
    char data[245]; ///< 数据内容
    int len; ///< 数据长度
    int encryption; ///< 加密方式 0:不加密 1:xxTea加密 2:RSA加密
} PVSDK_MOUNTAPI_SPI_DATA;

//////////////////////////////////////////////////
/// @brief Can滤波编号参数
///
/// 定义关于Can滤波编号接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_DEL_CAN_FILTER {
    int number; ///< 滤波器编号 0~13
} PVSDK_MOUNTAPI_DEL_CAN_FILTER;

//////////////////////////////////////////////////
/// @brief Can滤波设置、删除、查询参数
///
/// 定义关于Can滤波设置、删除、查询接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM {
    int totalNumber; ///< 使能的滤波器个数
    PVSDK_MOUNTAPI_CAN_FILTER_PARAM filter[14]; ///< 使能的滤波器参数
} PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM;

//////////////////////////////////////////////////
/// @brief 数据发送状态参数
///
/// 定义关于数据发送状态接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SEND_DATA_RETURN {
    int state; ///< 发送状态 0:成功 -1:失败
    int error; ///< 错误码
} PVSDK_MOUNTAPI_SEND_DATA_RETURN;

//////////////////////////////////////////////////
/// @brief 参数设置状态参数
///
/// 定义关于参数设置状态接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SET_PARAM {
    int state; ///< 发送状态 0:成功 -1:失败
    int error; ///< 错误码
} PVSDK_MOUNTAPI_SET_PARAM;

//////////////////////////////////////////////////
/// @brief I2c读取数据参数
///
/// 定义I2c读取数据接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_I2C_RETURN_DATA {
    char data[245]; ///< 数据内容
    int len; ///< 数据长度
    int encryption; ///< 加密方式 0:不加密 1:xxTea加密 2:RSA加密
} PVSDK_MOUNTAPI_I2C_RETURN_DATA;

//////////////////////////////////////////////////
/// @brief Spi读取数据参数
///
/// 定义Spi读取数据接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SPI_RETURN_DATA {
    char data[245]; ///< 数据内容
    int len; ///< 数据长度
    int encryption; ///< 0:不加密 1:xxTea加密 2:RSA加密
} PVSDK_MOUNTAPI_SPI_RETURN_DATA;

//////////////////////////////////////////////////
/// @brief I2c读取数据请求参数
///
/// 定义I2c读取数据请求接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_READI2C_DATA {
    int ramAddr; ///< 内存地址
    int addrType; ///< 地址类型 0:单字节地址 1:双字节地址
    int dataNumber; ///< 读取数据的字节个数 1~245
} PVSDK_MOUNTAPI_READI2C_DATA;

//////////////////////////////////////////////////
/// @brief Spi读取数据请求参数
///
/// 定义Spi读取数据请求接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_READSPI_DATA {
    int ramAddr; ///< 读取地址
    int dataNumber; ///< 读取数据的字节个数 1~245
} PVSDK_MOUNTAPI_READSPI_DATA;

//////////////////////////////////////////////////
/// @brief 设备版本获取参数
///
/// 定义设备版本获取接口参数
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_DEVICE_VERSION {
    int ver; ///< 版本号
    int date; 
} PVSDK_MOUNTAPI_DEVICE_VERSION;



typedef void (^_Nullable PVLoadDeviceResultBlock)(PVSDK_MOUNTAPI_MOUNTSTATE_DEVICE result);

typedef void (^_Nullable PVSendDataResultBlock)(PVSDK_MOUNTAPI_SEND_DATA_RETURN returnInfo);

typedef void (^_Nullable PVSetParamResultBlock)(PVSDK_MOUNTAPI_SET_PARAM param);

typedef void (^_Nullable PVSetCanFilterParamResultBlock)(PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM param);

typedef void (^_Nullable PVQueryUartParamBlock)(PVSDK_MOUNTAPI_UART_PARAM param);

typedef void (^_Nullable PVQueryCanParamBlock)(PVSDK_MOUNTAPI_CAN_PARAM param);

typedef void (^_Nullable PVQueryCanFilterParamBlock)(PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM param);

typedef void (^_Nullable PVQuerySpiParamBlock)(PVSDK_MOUNTAPI_SPI_PARAM param);

typedef void (^_Nullable PVQueryI2cParamBlock)(PVSDK_MOUNTAPI_I2C_PARAM param);

typedef void (^_Nullable PVQueryGpioParamBlock)(PVSDK_MOUNTAPI_GPIO_PARAM param);

typedef void (^_Nullable PVSDKReadI2cDataBlock)(PVSDK_MOUNTAPI_I2C_RETURN_DATA data);

typedef void (^_Nullable PVSDKReadSpiDataBlock)(PVSDK_MOUNTAPI_SPI_RETURN_DATA data);

typedef void (^_Nullable PVSDKQueryDeviceVersionBlock)(PVSDK_MOUNTAPI_DEVICE_VERSION versionInfo);

@class PVMountController;
@protocol PVMountControllerDelegate <NSObject>

/**
 接收Uart数据代理

 @param mc mc
 @param mData 数据内容
 */

- (void)mounthController:(PVMountController * _Nonnull)mc reciveUartData:(PVSDK_MOUNTAPI_UART_DATA)mData;

/**
 * 接收Can数据代理
 *
 * @param mc mc
 * @param mData 数据内容
 */
- (void)mounthController:(PVMountController * _Nonnull)mc reciveCanData:(PVSDK_MOUNTAPI_CAN_DATA)mData;


@end

@interface PVMountController : NSObject

NS_ASSUME_NONNULL_BEGIN //在其区间的属性都会获得nonnull属性

@property (nonatomic,weak)id <PVMountControllerDelegate> delegate;

NS_ASSUME_NONNULL_END

/**
 * 装载挂载设备
 *
 * @param deviceType 设备类型
 */
- (void)loadDevice:(PVMountPortType)deviceType WithComplection:(PVLoadDeviceResultBlock)block;

/**
 发送Uart数据

 @param data 数据内容
 @param block 发送状态
 */
- (void)sendUartData:(PVSDK_MOUNTAPI_UART_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 发送Can数据
 
 @param data 数据内容
 @param block 发送状态
 */
- (void)sendCanData:(PVSDK_MOUNTAPI_CAN_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 发送I2c数据
 
 @param data 数据内容
 @param block 发送状态
 */
- (void)sendI2cData:(PVSDK_MOUNTAPI_I2C_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 发送Spi数据
 
 @param data 数据内容
 @param block 发送状态
 */
- (void)sendSpiData:(PVSDK_MOUNTAPI_SPI_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 设置Uart参数

 @param param 参数内容
 @param block 设置结果
 */
- (void)setUartParam:(PVSDK_MOUNTAPI_UART_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;


/**
 设置Can参数
 
 @param param 参数内容
 @param block 设置结果
 */
- (void)setCanParam:(PVSDK_MOUNTAPI_CAN_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;


/**
 设置Can滤波器

 @param param 滤波器参数
 @param block 设置结果
 */
- (void)setCanFilterParam:(PVSDK_MOUNTAPI_CAN_FILTER_PARAM)param withSetResultBlock:(PVSetCanFilterParamResultBlock)block;

/**
 删除Can滤波器

 @param param 滤波器参数
 @param block 设置结果
 */
- (void)deleteCanFilterParam:(PVSDK_MOUNTAPI_DEL_CAN_FILTER)param withSetResultBlock:(PVSetCanFilterParamResultBlock)block;


/**
 设置I2c参数
 
 @param param 参数内容
 @param block 设置结果
 */
- (void)setI2cParam:(PVSDK_MOUNTAPI_I2C_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;

/**
 设置Spi参数
 
 @param param 参数内容
 @param block 设置结果
 */
- (void)setSpiParam:(PVSDK_MOUNTAPI_SPI_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;

/**
 设置Gpio参数

 @param param 参数内容
 @param block 设置结果
 */
- (void)setGpioParam:(PVSDK_MOUNTAPI_GPIO_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;

/**
 查询Uart参数
 
 @param block 查询结果
 */
- (void)queryUartParamWithBlock:(PVQueryUartParamBlock)block;

/**
 查询Can参数

 @param block 查询结果
 */
- (void)queryCanParamWithBlock:(PVQueryCanParamBlock)block;

/**
 查询Can滤波器参数
 
 @param block 查询结果
 */
- (void)queryCanFilterParamWithBlock:(PVQueryCanFilterParamBlock)block;


/**
 查询Spi参数

 @param block 查询结果
 */
- (void)querySpiParamWithBlock:(PVQuerySpiParamBlock)block;


/**
 查询I2c参数

 @param block 查询结果
 */
- (void)queryI2cParamWithBlock:(PVQueryI2cParamBlock)block;

//typedef int (*MountApi_inquireGpioParamNotify)(const MOUNTAPI_GPIO_PARAM info); //请求Gpio参数通知
//PVSDK_API int MountApi_inquireGpioParam(int device);


/**
 查询Gpio设备参数

 @param block 查询结果
 */
- (void)queryGpioParamWithGpioNumber:(NSInteger)num WithBlock:(PVQueryGpioParamBlock)block;

/**
 读取I2c数据

 @param readInfo 读取参数设置
 @param block 读取内容
 */
- (void)readI2cData:(PVSDK_MOUNTAPI_READI2C_DATA)readInfo WithReadDataBlock:(PVSDKReadI2cDataBlock)block;

/**
 读取Spi数据

 @param readInfo 读取参数设置
 @param block 读取内容
 */
- (void)readSpiData:(PVSDK_MOUNTAPI_READSPI_DATA)readInfo WithReadDataBlock:(PVSDKReadSpiDataBlock)block;

/**
 查询设备软件版本

 @param block 查询结果
 */
- (void)queryDeviceSoftVersionWithBlock:(PVSDKQueryDeviceVersionBlock)block;

/**
 查询设备硬件版本

 @param block 查询结果
 */
- (void)queryDeviceHardVersionWithBlock:(PVSDKQueryDeviceVersionBlock)block;

@end

/**  @} */
