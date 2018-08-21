//
//  AVADisplayLinkTimer.h
//  AvatarKit
//
//  Created by weixu on 2018/2/10.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AVADisplayLinkTimer : NSObject
@property(nonatomic) BOOL isPaused;

- (instancetype)initWithMaxfps:(int)maxfps WithTimerHandler:(void (^)(void))timerHandler;
- (void)invalidate;
@end
