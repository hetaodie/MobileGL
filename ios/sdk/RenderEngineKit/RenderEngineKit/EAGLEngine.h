//
//  GLESEngine.h
//  AvatarKit
//
//  Created by weixu on 2018/1/4.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/CAEAGLLayer.h>

@interface EAGLEngine : NSObject
@property (nonatomic, assign) BOOL isOffscreenRender;
- (BOOL)resetGLContext;
- (void)createFramebuffer:(CAEAGLLayer *)layer;
- (BOOL)setFramebuffer;
- (void)deleteFramebuffer;
- (BOOL)presentFramebuffer;
- (int)getDefaultFramebuffer;
@end
