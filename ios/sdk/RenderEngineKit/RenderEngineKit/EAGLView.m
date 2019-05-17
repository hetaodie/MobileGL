//
//  EAGLView.m
//  Avatar-demo
//
//  Created by weixu on 2017/11/15.
//  Copyright © 2017年 Buddy. All rights reserved.
//


#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"

@implementation EAGLView

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithCoder:(NSCoder*)coder
{
    self = [super initWithCoder:coder];
    if (self)
    {
        [self setupLayer];
    }
    
    return self;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self setupLayer];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
    }
    return self;
}

- (void)setupLayer {
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
    
    eaglLayer.opaque = TRUE;
    eaglLayer.drawableProperties = [ NSDictionary dictionaryWithObjectsAndKeys:
                                    [ NSNumber numberWithBool:NO],
                                    kEAGLDrawablePropertyRetainedBacking,
                                    kEAGLColorFormatRGBA8,
                                    kEAGLDrawablePropertyColorFormat,
                                    nil ];
//    eaglLayer.contentsScale = 2.0;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    if (self.delegate && [self.delegate respondsToSelector:@selector(glView:changeFrame:)]) {
        [self.delegate glView:self changeFrame:self.frame];
    }
}

- (void)setupViewContentScaleFactor:(float)value {
     CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
    if ([NSThread currentThread].isMainThread) {
        eaglLayer.contentsScale = value;
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
            eaglLayer.contentsScale = value;
        });
    }
}


@end

