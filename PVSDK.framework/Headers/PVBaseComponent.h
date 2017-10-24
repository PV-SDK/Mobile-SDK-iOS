//
//  PVBaseComponent.h
//  PVSDK
//
//  Created by Layne on 16/6/17.
//  Copyright © 2016年 Layne. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  激活状态
 */
typedef NS_ENUM(NSInteger,PVProductValidateState) {
    /**
     *  未激活
     */
    PVProductValidateStateInactive,
    /**
     *  已激活
     */
    PVProductValidateStateActivated,
};


typedef void (^_Nullable PVCompletionBlock)(NSError *_Nullable error);

@interface PVBaseComponent : NSObject

+ (void)setParameterForKey:(NSString *_Nonnull)key valueForInt:(int)value;

+ (void)setParameterForKey:(NSString *_Nonnull)key valueForFloat:(float)value;

@end
