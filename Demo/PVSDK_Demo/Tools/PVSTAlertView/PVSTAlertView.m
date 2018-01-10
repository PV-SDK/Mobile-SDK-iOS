//
//  PVSTAlertView.m
//  PVSDK
//
//  Copyright © 2017 PowerVision. All rights reserved.
//
/**
 *  A helper function to pop-up a simple alert view. 
 */
#import "PVSTAlertView.h"

#define NavControllerObject(navController) UINavigationController* navController = (UINavigationController*)[[UIApplication sharedApplication] keyWindow].rootViewController;


void ShowResult(NSString *format, ...)
{
    va_list argumentList;
    va_start(argumentList, format);

    NSString* message = [[NSString alloc] initWithFormat:format arguments:argumentList];
    va_end(argumentList);
    NSString * newMessage = [message hasSuffix:@":(null)"] ? [message stringByReplacingOccurrencesOfString:@":(null)" withString:@" successful!"] : message;
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertController* alertViewController = [UIAlertController alertControllerWithTitle:nil message:newMessage preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction* okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil];
        [alertViewController addAction:okAction];
        UINavigationController* navController = (UINavigationController*)[[UIApplication sharedApplication] keyWindow].rootViewController;
        [navController dismissViewControllerAnimated:NO completion:nil];
        [navController presentViewController:alertViewController animated:YES completion:nil];
    });
}

@interface PVSTAlertView()

@property(nonatomic, strong) UIAlertController* alertController;

@end

@implementation PVSTAlertView

+(instancetype _Nullable)showAlertViewWithMessage:(NSString* _Nullable)message titles:(NSArray<NSString*> * _Nullable)titles action:(PVSTAlertViewActionBlock _Nullable)actionBlock presentedViewController:(UIViewController *)viewController
{
    PVSTAlertView* alertView = [[PVSTAlertView alloc] init];
    
    alertView.alertController = [UIAlertController alertControllerWithTitle:@"" message:message preferredStyle:UIAlertControllerStyleAlert];
    for (NSUInteger index = 0; index < titles.count; ++index) {
        UIAlertActionStyle actionStyle = (index == 0) ? UIAlertActionStyleCancel : UIAlertActionStyleDefault;
        UIAlertAction* alertAction = [UIAlertAction actionWithTitle:titles[index] style:actionStyle handler:^(UIAlertAction * _Nonnull action) {
            if (actionBlock) {
                actionBlock(index);
            }
        }];
        [alertView.alertController addAction:alertAction];
    }
    
    [viewController presentViewController:alertView.alertController animated:YES completion:nil];
    return alertView;
}

+(instancetype _Nullable)showAlertViewWithMessage:(NSString* _Nullable)message titles:(NSArray<NSString*> * _Nullable)titles action:(PVSTAlertViewActionBlock _Nullable)actionBlock
{
    PVSTAlertView* alertView = [[PVSTAlertView alloc] init];

    alertView.alertController = [UIAlertController alertControllerWithTitle:@"" message:message preferredStyle:UIAlertControllerStyleAlert];
    for (NSUInteger index = 0; index < titles.count; ++index) {
        UIAlertActionStyle actionStyle = (index == 0) ? UIAlertActionStyleCancel : UIAlertActionStyleDefault;
        UIAlertAction* alertAction = [UIAlertAction actionWithTitle:titles[index] style:actionStyle handler:^(UIAlertAction * _Nonnull action) {
            if (actionBlock) {
                actionBlock(index);
            }
        }];
        [alertView.alertController addAction:alertAction];
    }

    NavControllerObject(navController);
    [navController presentViewController:alertView.alertController animated:YES completion:nil];
    return alertView;
}

+(instancetype _Nullable)showAlertViewWithMessage:(NSString* _Nullable)message titles:(NSArray<NSString*> * _Nullable)titles textFields:(NSArray<NSString*>* _Nullable)textFields action:(PVSTAlertInputViewActionBlock _Nullable)actionBlock
{
    PVSTAlertView* alertView = [[PVSTAlertView alloc] init];

    alertView.alertController = [UIAlertController alertControllerWithTitle:@"" message:message preferredStyle:UIAlertControllerStyleAlert];
    for (NSUInteger index = 0; index < textFields.count; ++index) {
        [alertView.alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = textFields[index];
        }];
    }

    NSArray* fieldViews = alertView.alertController.textFields;
    for (NSUInteger index = 0; index < titles.count; ++index) {
        UIAlertActionStyle actionStyle = (index == 0) ? UIAlertActionStyleCancel : UIAlertActionStyleDefault;
        UIAlertAction* alertAction = [UIAlertAction actionWithTitle:titles[index] style:actionStyle handler:^(UIAlertAction * _Nonnull action) {
            if (actionBlock) {
                actionBlock(fieldViews, index);
            }
        }];

        [alertView.alertController addAction:alertAction];
    }

    NavControllerObject(navController);
    [navController presentViewController:alertView.alertController animated:YES completion:nil];
    return alertView;
}

-(void)updateMessage:(nullable NSString *)message
{
    self.alertController.message = message;
}

-(void)dismissAlertView
{
    [self.alertController dismissViewControllerAnimated:YES completion:nil];
}

@end

