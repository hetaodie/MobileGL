//
//  AVADisplayLinkTimer.m
//  AvatarKit
//
//  Created by weixu on 2018/2/10.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import "AVADisplayLinkTimer.h"
#import <QuartzCore/QuartzCore.h>

@implementation AVADisplayLinkTimer{
    CADisplayLink *_displayLink;
    void (^_timerHandler)(void);
}


- (instancetype)initWithMaxfps:(int)maxfps WithTimerHandler:(void (^)(void))timerHandler{
    NSParameterAssert(timerHandler);
    if (self = [super init]) {
        _timerHandler = timerHandler;
        _displayLink =
        [CADisplayLink displayLinkWithTarget:self
                                    selector:@selector(displayLinkDidFire:)];
        _displayLink.paused = YES;
        // Set to half of screen refresh, which should be 30fps.
        if (@available(iOS 10.0, *)) {
            [_displayLink setPreferredFramesPerSecond:maxfps];
        } else {
            int interval = 60/maxfps;
            [_displayLink setFrameInterval:interval];
        }
       
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                           forMode:NSRunLoopCommonModes];
    }
    return self;
}

- (void)dealloc {
    [self invalidate];
}

- (BOOL)isPaused {
    return _displayLink.paused;
}

- (void)setIsPaused:(BOOL)isPaused {
    _displayLink.paused = isPaused;
}

- (void)invalidate {
    [_displayLink invalidate];
}

- (void)displayLinkDidFire:(CADisplayLink *)displayLink {
    _timerHandler();
}
@end
