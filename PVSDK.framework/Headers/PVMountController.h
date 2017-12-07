/**
 * @file PVMountController.h
 * @author Layne
 *
 * @brief Mount interface file
 *
 */

/**
 * @defgroup PVSDK_CORE_API_MOUNTCONTROL Core interface of SDK mount.
 * @{
 */

/**
 * @page mount-page Mount interface
 */


#import <Foundation/Foundation.h>

////////////////////////////////////////
/// @brief The type of mount interface.
///
/// Define the type of mount interface.
////////////////////////////////////////
typedef enum _PVMountPortType{
    PVMountPortTypeUART, //!< Uart
    PVMountPortTypeCAN, //!< Can
    PVMountPortTypeI2C, //!< I2c
    PVMountPortTypeSPI, //!< Spi
    PVMountPortTypeGPIO, //!< Gpio
}PVMountPortType;

//////////////////////////////////////////////////
/// @brief Parameters about the status of mount device.
///
/// Define interface parameters about the status of mount device.
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_MOUNTSTATE_DEVICE {
    int uart; ///< gorge
    int can; ///< internet access
    int i2c; ///< I2C
    int spi; ///< SPI
    int gpio1; ///< GPIO1
    int gpio2; ///< GPIO2
    int gpio3; ///< GPIO3
} PVSDK_MOUNTAPI_MOUNTSTATE_DEVICE;

//////////////////////////////////////////////////
/// @brief Parameters about gorge settings.
///
///  Define interface parameters about gorge settings.
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_UART_PARAM {
    int bps; ///< Gorge baudrate  0:9600 1:14400 2:19200 3:38400 4:57600 5:115200
    int dataBits; ///<  Data bits 0:8bits 1:9bits
    int stopBits; ///< Stop bits0:1bits 1:2bits
    int parity; ///< verify 0:no verification1:odd parity check 2:even parity check
    int flowCtrl; ///< fluid control  0:no fluid control 1:RTS is effective2:CTS is effective3:RTS and CTS are effective at the same time.
} PVSDK_MOUNTAPI_UART_PARAM;

//////////////////////////////////////////////////
/// @brief Parameters about Can settings.
///
/// Define interface parameters about Can settings.
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_CAN_PARAM {
    int mode; ///< Mode 0:Normal mode1:Silent mode2:Loopback mode 3:Silent loopback mode
    int bps; ///< Baud rate0:5k 1:10k 2:20k 3:50k 4:100k 5:125k 6:250k 7:500k 8:800k 9:1000k
} PVSDK_MOUNTAPI_CAN_PARAM;

//////////////////////////////////////////////////
/// @briefParameters about I2c settings.
///
/// Define interface parameters about I2c settings.
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_I2C_PARAM {
    int mode; ///<  Mode  0:Master mode  1:Slave mode
    int bps; ///< Rate setting  0:100kbps 1:400kbps
    int deviceAddr; ///<Device address(0~127)Device address
} PVSDK_MOUNTAPI_I2C_PARAM;

//////////////////////////////////////////////////
/// @brief Interface parameters about Spi settings.
///
/// Define interface parameters about Spi settings.
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SPI_PARAM {
    int mode; ///<  Mode 0:Master mode 1:Slave mode
    int bps; ///< Rate setting 0:1Mbps 1:2Mbps 2:4Mbps 3:8Mbps 4:16Mbps
    int firstBit; ///< Significance first  0:MSB first 1:LSB first
    int dataSize; ///< Data size 0:8bit 1:16bit
    int crcEnable; ///< Crc enable0:not enablecrc 1:enablecrc
} PVSDK_MOUNTAPI_SPI_PARAM;

//////////////////////////////////////////////////
/// @brief Interface parameters about Can filtering settings.
///
///Define interface parameters about Can filtering settings.
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_CAN_FILTER_PARAM {
    int number; ///<  The span of filter number is 0~13.
    int mode; ///< Filter mode 0:mask Mode 1:id list Mode
    int matchId; ///<  ID matching value
    int maskId; ///< ID mask value
    int type; ///< ID type0:StandardID 1:ExtendID
    int format; ///< Frame format 0:data frame 1:remote frame
    int Enable; ///< Filter enable 0:Not enable 1:Enable
} PVSDK_MOUNTAPI_CAN_FILTER_PARAM;

//////////////////////////////////////////////////
/// @brief Interface parameters about Can filtering settings.
///
/// Define interface parameters about Can filtering settings.
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_GPIO_PARAM {
    int deviceNumber; ///< gpio device number 0:gpio1 1:gpio2 2:gpio3
    int periodRatio; ///< The span of cycle value resolution is (0~0xffff).The unit is 1/64us.
    int periodLow; ///< The span of low level duration in a circle is (0~0xffff).
    int periodHigh; ///< (0~0xffff)The span of high level duration in a circle is (0~0xffff).
} PVSDK_MOUNTAPI_GPIO_PARAM;

//////////////////////////////////////////////////
/// @brief Interface parameters of Uart data
///
///  Define interface parameters about Uart data
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_UART_DATA {
    char data[245]; ///<Data content
    int len; ///< Data length
    int encryption; ///<Encryption 0:no encryption    1:xxTea encrypt 2:RSA encrypt
} PVSDK_MOUNTAPI_UART_DATA;

//////////////////////////////////////////////////
/// @brief Interface parameters of Can data.
///
/// Define interface parameters about Can data
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_CAN_DATA {
    int type; ///< id:type0:standard 1:expanded id
    int format; ///< Frame format  0: data frame  1:remote frame
    int id; ///<  Frame id bit0~bit28bit is effective。 bit0~bit10 is  standard frame.bit11~bit28 is expanded format.
    char data[239]; ///<  Data content
    int len; ///< Data length
    int encryption; ///<  Encryption 0:no encryption    1:xxTea encrypt 2:RSA encrypt
} PVSDK_MOUNTAPI_CAN_DATA;

//////////////////////////////////////////////////
/// @brief Interface parameters of I2c data
///
///  Define interface parameters about I2c data
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_I2C_DATA {
    int ramAddr; ///< Memory address
    int addrType; ///< Address type   0:Single-byte address 1: double byte address
    char data[242]; ///<  Sending data
    int len; ///< The length of sending data
    int encryption; ///< 0:no encryption    1:xxTea encrypt 2:RSA encrypt
} PVSDK_MOUNTAPI_I2C_DATA;

//////////////////////////////////////////////////
/// @brief  The parameters about Spi data interface
///
/// Define interface parameters about Spi data
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SPI_DATA {
    char data[245]; ///<  Data content
    int len; ///< Data length
    int encryption; ///< Encryption 0:no encryption    1:xxTea encrypt 2:RSA encrypt
} PVSDK_MOUNTAPI_SPI_DATA;

//////////////////////////////////////////////////
/// @brief  Interface parameters about Can filter number
///
/// Define interface parameters about Can filter number
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_DEL_CAN_FILTER {
    int number; ///< Filter number0~13
} PVSDK_MOUNTAPI_DEL_CAN_FILTER;

//////////////////////////////////////////////////
/// @brief The filter setting,remove,query interface parameters of Can
///
/// Define parameters of Can about its filter setting,remove,query interface
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM {
    int totalNumber; ///< The number of enabling filter
    PVSDK_MOUNTAPI_CAN_FILTER_PARAM filter[14]; ///< The parameters of enabling filter
} PVSDK_MOUNTAPI_RETURN_CAN_FILTER_PARAM;

//////////////////////////////////////////////////
/// @brief Parameters about data delivery status
///
/// Define interface parameters about data delivery status
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SEND_DATA_RETURN {
    int state; ///<  Send state  0:success -1:failure
    int error; ///< error code
} PVSDK_MOUNTAPI_SEND_DATA_RETURN;

//////////////////////////////////////////////////
/// @brief Parameters about the parameters Settings

/// Define interface parameters about the parameters Settings
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SET_PARAM {
    int state; ///< Send state  0:success -1:failure
    int error; ///<error code
} PVSDK_MOUNTAPI_SET_PARAM;

//////////////////////////////////////////////////
/// @brief  I2c read the data of request parameters
///
///  Define I2c read the data of request interface parameters
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_I2C_RETURN_DATA {
    char data[245]; ///<Data content
    int len; ///< Data length
    int encryption; ///<  Encryption 0:no encryption    1:xxTea encrypt 2:RSA encrypt
} PVSDK_MOUNTAPI_I2C_RETURN_DATA;

//////////////////////////////////////////////////
/// @brief Spi read the data of request parameters
///
/// Define Spi read the data of request interface parameters
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_SPI_RETURN_DATA {
    char data[245]; ///<Data content
    int len; ///< Data length
    int encryption; ///<Encryption 0:no encryption    1:xxTea encrypt 2:RSA encrypt
} PVSDK_MOUNTAPI_SPI_RETURN_DATA;

//////////////////////////////////////////////////
/// @brief  I2c read the data of request parameters
///
/// Define I2c read the data of request interface parameters
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_READI2C_DATA {
    int ramAddr; ///<Memory address
    int addrType; ///< Address type   0:Single-byte address 1: double byte address
    int dataNumber; ///< Read the number of bytes in the data.1~245
} PVSDK_MOUNTAPI_READI2C_DATA;

//////////////////////////////////////////////////
/// @brief  Spi read the data of request parameters
///
///  Define Spi read the data of request interface parameters
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_READSPI_DATA {
    int ramAddr; ///< Memory address
    int dataNumber; ///< Read the number of bytes in the data.1~245
} PVSDK_MOUNTAPI_READSPI_DATA;

//////////////////////////////////////////////////
/// @brief  Take the parameter of equipment version
///
///   Define equipment version access interface parameters
//////////////////////////////////////////////////
typedef struct PVSDK_MOUNTAPI_DEVICE_VERSION {
    int ver; ///< version number
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
 Receive Uart data agent
 
 @param mc mc
 @param mData content
 */

- (void)mounthController:(PVMountController * _Nonnull)mc reciveUartData:(PVSDK_MOUNTAPI_UART_DATA)mData;

/**
 *  Receive can data agent
 *
 * @param mc mc
 * @param mData  Data content
 */
- (void)mounthController:(PVMountController * _Nonnull)mc reciveCanData:(PVSDK_MOUNTAPI_CAN_DATA)mData;


@end

@interface PVMountController : NSObject

NS_ASSUME_NONNULL_BEGIN //Attribute in its rang will getattr nonnull

@property (nonatomic,weak)id <PVMountControllerDelegate> delegate;

NS_ASSUME_NONNULL_END

/**
 * Loading mounted equipment
 *
 * @param deviceType Device type
 */
- (void)loadDevice:(PVMountPortType)deviceType WithComplection:(PVLoadDeviceResultBlock)block;

/**
 Send Uart data
 
 @param data data content
 @param send state
 */
- (void)sendUartData:(PVSDK_MOUNTAPI_UART_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 Send Can data
 
 @param data Data content
 @param  Send state
 */
- (void)sendCanData:(PVSDK_MOUNTAPI_CAN_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 Send I2c data
 
 @param data Data content
 @param Send state
 */
- (void)sendI2cData:(PVSDK_MOUNTAPI_I2C_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 Send Spi data
 
 @param data Data content
 @param  Send state
 */
- (void)sendSpiData:(PVSDK_MOUNTAPI_SPI_DATA)data withSendResultBlock:(PVSendDataResultBlock)block;

/**
 Set Uart parameter
 
 @param param Parameter content
 @param block   results
 */
- (void)setUartParam:(PVSDK_MOUNTAPI_UART_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;


/**
 set Can parameter
 
 @param param Parameter content
 @param block  results
 */
- (void)setCanParam:(PVSDK_MOUNTAPI_CAN_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;


/**
 Set Can filter
 
 @param param  filter parameter
 @param block  results
 */
- (void)setCanFilterParam:(PVSDK_MOUNTAPI_CAN_FILTER_PARAM)param withSetResultBlock:(PVSetCanFilterParamResultBlock)block;

/**
 Remove Can filter
 
 @param param  filter parameter
 @param block    results
 */
- (void)deleteCanFilterParam:(PVSDK_MOUNTAPI_DEL_CAN_FILTER)param withSetResultBlock:(PVSetCanFilterParamResultBlock)block;


/**
 Set the parameters of I2c
 
 
 @param param parameter content
 @param block   results
 */
- (void)setI2cParam:(PVSDK_MOUNTAPI_I2C_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;

/**
 Set the parameters of Spi
 
 @param param  parameter content
 @param block  results
 */
- (void)setSpiParam:(PVSDK_MOUNTAPI_SPI_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;

/**
 Set the parameters of Gpio
 
 @param param parameter content
 @param block  results
 */
- (void)setGpioParam:(PVSDK_MOUNTAPI_GPIO_PARAM)param withSetResultBlock:(PVSetParamResultBlock)block;

/**
 Query the parameters of Jart
 
 @param block query results
 */
- (void)queryUartParamWithBlock:(PVQueryUartParamBlock)block;

/**
 Query the parameters of Can
 
 @param block  query results
 */
- (void)queryCanParamWithBlock:(PVQueryCanParamBlock)block;

/**
 Query the filter parameters of Can
 
 @param block  query results
 */
- (void)queryCanFilterParamWithBlock:(PVQueryCanFilterParamBlock)block;


/**
 Query the parameters of Spi
 
 @param block query results
 */
- (void)querySpiParamWithBlock:(PVQuerySpiParamBlock)block;


/**
 Query the parameters of I2c
 
 @param block query results
 */
- (void)queryI2cParamWithBlock:(PVQueryI2cParamBlock)block;

//typedef int (*MountApi_inquireGpioParamNotify)(const MOUNTAPI_GPIO_PARAM info); //请求Gpio参数通知
//PVSDK_API int MountApi_inquireGpioParam(int device);


/**
 Query the equipment parameters of Gpio
 
 @param block query results
 */
- (void)queryGpioParamWithGpioNumber:(NSInteger)num WithBlock:(PVQueryGpioParamBlock)block;

/**
 Read the data of I2c
 
 @param readInfo  read parameter settings
 @param block read content
 */
- (void)readI2cData:(PVSDK_MOUNTAPI_READI2C_DATA)readInfo WithReadDataBlock:(PVSDKReadI2cDataBlock)block;

/**
 Read the data of spi
 
 
 @param readInfo read parameter settings
 @param block read content
 */
- (void)readSpiData:(PVSDK_MOUNTAPI_READSPI_DATA)readInfo WithReadDataBlock:(PVSDKReadSpiDataBlock)block;

/**
 The software version of query device
 
 @param block query results
 */
- (void)queryDeviceSoftVersionWithBlock:(PVSDKQueryDeviceVersionBlock)block;

/**
 The hardware version of query device
 
 @param block query results
 */
- (void)queryDeviceHardVersionWithBlock:(PVSDKQueryDeviceVersionBlock)block;

@end

/**  @} */
