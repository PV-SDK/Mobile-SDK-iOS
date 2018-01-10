//
//  PVWayPointModel.h
//  PVSDK
//
//  Copyright © 2016 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface PVWayPointModel : NSObject

@property (nonatomic, assign) CLLocationCoordinate2D touchMapCoordinate;    ///<  Longitude and latitude（ must do ）
@property (nonatomic, assign) float height;                                 ///<  Agl above ground level（ must do ）：The altitude of the waypoint from the ground.[3m-100m]
@property (nonatomic, assign) float stayTime;                               ///<  Residence time（must do ）：How long will it stay from this point to the next point

@end

