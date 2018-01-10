//
//  PVSTGPSLocationPicker.h
//  PVSDK
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    /** Progress is shown using a horizontal progress bar This is the default */
    GPSLocationPickerModeDeterminateHorizontalBar,
    /** Progress is shown using a round, pie-chart like, progress view. */
    GPSLocationPickerModeDeterminate,
    /** Progress is shown using an UIActivityIndicatorView.*/
    GPSLocationPickerModeIndeterminate,
    /** Progress is shown using a ring-shaped progress view. */
    GPSLocationPickerModeAnnularDeterminate,
} GPSLocationPickerMode;

typedef void (^LocationResult)(CLLocation *location, NSError *error);

@interface PVSTGPSLocationPicker : NSObject

//定位超时时间（单位:s）， 默认为-100
@property (nonatomic, assign) int timeoutPeriod;
//定位期望精度（单位:m），默认为-100
@property (nonatomic, assign) CLLocationAccuracy precision;
//当前坐标
@property (nonatomic, assign) CLLocationCoordinate2D nowCoordinate;
//定位期望的有效距离（单位:m），默认为-100，设置该属性时，必须把用户当前坐标传进来，即nowCoordinate
@property (nonatomic, assign) CLLocationDistance validDistance;

/**是否显示等待框 默认为YES*/
@property (nonatomic, assign) BOOL showWaitView;
/**等待框样式*/
@property (nonatomic, assign) GPSLocationPickerMode mode;

/**等待框中是否显示剩余时间 默认为YES*/
@property (nonatomic, assign) BOOL showLocTime;
/**等待框中是否显示详细信息 默认为YES*/
@property (nonatomic, assign) BOOL showDetailInfo;

+ (instancetype)shareGPSLocationPicker;
/**
 * @brief 启动定位，如果需要对超时时长、采集到的坐标精度和有效距离做要求， 则需要在调用该方法之前对 timeoutPeriod, precision, nowCoordinate, valiDistance 做一个对应的赋值
 */
- (void)startLocationAndCompletion:(LocationResult)completion;

/**
 * @brief 重置变量为默认值
 */
- (void)resetDefaultVariable;

@end
