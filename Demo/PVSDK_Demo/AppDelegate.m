//
//  AppDelegate.m
//  PVSDK_Demo
//
//  Created by Layne on 2017/10/12.
//  Copyright © 2017 PowerVision. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {

    //  此处 post notification 是为了在App Resign(放弃) Active 时 通知图传 Pause
    [[NSNotificationCenter defaultCenter] postNotificationName:@"ApplicationWillResignActive" object:nil];
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    //  此处 post notification 是为了在App Become Active 时 通知图传 Play
    [[NSNotificationCenter defaultCenter] postNotificationName:@"ApplicationDidBecomeActive" object:nil];
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
