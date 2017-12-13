//
//  PrefixHeaderMacro.h
//  PVSDK_Demo
//
//  Copyright © 2017年 PowerVision. All rights reserved.
//

#ifndef PrefixHeaderMacro_h
#define PrefixHeaderMacro_h

#define ScreenWidth [UIScreen mainScreen].bounds.size.width
#define ScreenHeight [UIScreen mainScreen].bounds.size.height

#define WEAKSELF __weak __typeof(self) weakSelf = self
#define STRONGSELF __strong __typeof(self) strongSelf = weakSelf;

#define WEAKReturn(__obj) if(__obj ==nil)return;

#endif /* PrefixHeaderMacro_h */
