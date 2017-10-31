/**
 * @file PVBaseComponent.h
 * @author Layne
 *
 * @brief 基类文件
 * Created by Layne on 17/8/22.
 * Copyright © 2017年 Layne. All rights reserved.
 */

#import <Foundation/Foundation.h>

////////////////////////////////////////
/// @brief 激活状态类型
///
/// 定义了激活状态类型
////////////////////////////////////////
typedef enum _PVProductValidateState{
    PVProductValidateStateInactive, ///< 未激活
    PVProductValidateStateActivated, ///< 已激活
}PVProductValidateState;


typedef void (^_Nullable PVCompletionBlock)(NSError *_Nullable error);

@interface PVBaseComponent : NSObject

/**
 设置int型参数

 @param key key
 @param value value
 */
+ (void)setParameterForKey:(NSString *_Nonnull)key valueForInt:(int)value;


/**
 设置float型参数

 @param key key
 @param value value
 */
+ (void)setParameterForKey:(NSString *_Nonnull)key valueForFloat:(float)value;

@end
