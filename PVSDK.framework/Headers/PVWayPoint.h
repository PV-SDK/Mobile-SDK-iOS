//
//  PVWayPoint.h
//  PVSDK
//
//  Created by Layne on 16/4/26.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface PVWayPoint : NSObject

@property (nonatomic,assign)float param2;
@property (nonatomic,assign)float param4;
@property (nonatomic,assign)CLLocationCoordinate2D touchMapCoordinate;
@property (nonatomic,assign)float speed;
@property (nonatomic,assign)float height;
@property (nonatomic,assign)float stayTime;
@property (nonatomic,assign)float arriveRadius;
@property (nonatomic,assign)uint16_t seq;

@end
