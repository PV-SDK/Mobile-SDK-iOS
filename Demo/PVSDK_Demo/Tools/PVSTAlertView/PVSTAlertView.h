//
//  PVSTAlertView.h
//  PVSDK_Demo
//
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern void ShowResult(NSString * format, ...);

typedef void (^PVSTAlertViewActionBlock)(NSUInteger buttonIndex);
typedef void (^PVSTAlertInputViewActionBlock)(NSArray<UITextField*>* _Nullable textFields, NSUInteger buttonIndex);

@interface PVSTAlertView : NSObject

+(instancetype _Nullable) showAlertViewWithMessage:(NSString* _Nullable)message titles:(NSArray<NSString*> * _Nullable)titles action:(PVSTAlertViewActionBlock _Nullable)actionBlock;

+(instancetype _Nullable) showAlertViewWithMessage:(NSString* _Nullable)message titles:(NSArray<NSString*> * _Nullable)titles textFields:(NSArray<NSString*>* _Nullable)textFields action:(PVSTAlertInputViewActionBlock _Nullable)actionBlock;

+(instancetype _Nullable) showAlertViewWithMessage:(NSString* _Nullable)message titles:(NSArray<NSString*> * _Nullable)titles action:(PVSTAlertViewActionBlock _Nullable)actionBlock presentedViewController:(UIViewController *)viewController;

-(void) dismissAlertView;

-(void) unpdateMessage:(nullable NSString *)message;

@end

NS_ASSUME_NONNULL_END
