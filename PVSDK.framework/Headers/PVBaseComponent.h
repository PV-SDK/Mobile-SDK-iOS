/**
 * @file PVBaseComponent.h
 * @author Layne
 *
 * @brief base class file
 * Created by Layne on 17/8/22.
 * Copyright © 2017 Layne. All rights reserved.
 */

#import <Foundation/Foundation.h>

////////////////////////////////////////
/// @brief state of activation
///
/// define the state of activation
////////////////////////////////////////
typedef enum _PVProductValidateState{
    PVProductValidateStateInactive,     ///< unactivated
    PVProductValidateStateActivated,    ///< activated
}PVProductValidateState;


typedef void (^_Nullable PVCompletionBlock)(NSError *_Nullable error);

@interface PVBaseComponent : NSObject

/**
 set int parameters
 
 @param key key
 @param value value
 */
+ (void)setParameterForKey:(NSString *_Nonnull)key valueForInt:(int)value;


/**
 set float parameters
 
 @param key key
 @param value value
 */
+ (void)setParameterForKey:(NSString *_Nonnull)key valueForFloat:(float)value;

@end
