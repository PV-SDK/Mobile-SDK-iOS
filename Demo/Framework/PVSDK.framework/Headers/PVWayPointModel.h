//
//  PVWayPointModel.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface PVWayPointModel : NSObject

@property (nonatomic, assign) CLLocationCoordinate2D touchMapCoordinate;    //  经纬度（必传）
@property (nonatomic, assign) float height;                                 //  对地高度
@property (nonatomic, assign) float stayTime;                               //  停留时间：从这一个点停留多长时间后向下一个点飞行

@end
