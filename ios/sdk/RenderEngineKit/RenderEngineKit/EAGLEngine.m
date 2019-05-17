//
//  GLESEngine.m
//  AvatarKit
//
//  Created by weixu on 2018/1/4.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import "EAGLEngine.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>

#import <OpenGLES/EAGL.h>

@interface EAGLEngine ()
{
    GLint framebufferWidth;
    GLint framebufferHeight;
    
    GLuint defaultFramebuffer, colorRenderbuffer, depthRenderbuffer;
}

@property (nonatomic, strong) EAGLContext *mContext;

@end

@implementation EAGLEngine

#pragma mark -
#pragma mark lifecycle

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self setUpContext];
    }
    return self;
}

- (void)dealloc
{
    [self deleteFramebuffer];
}

#pragma mark -
#pragma mark public

- (BOOL)setFramebuffer
{
    if (self.mContext)
    {
        if ([EAGLContext currentContext] != self.mContext) {
            BOOL isSuccess = [EAGLContext setCurrentContext:self.mContext];
            if (!isSuccess) {
                NSLog(@"weixu setFramebuffer1");
                return NO;
            }
        }
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        return YES;
    }
    NSLog(@"weixu setFramebuffer2");
    return NO;
}

- (BOOL)presentFramebuffer
{
    BOOL success = FALSE;
    
    if (self.mContext)
    {
        if ([EAGLContext currentContext] != self.mContext) {
            [EAGLContext setCurrentContext:self.mContext];
        }
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        success = [self.mContext presentRenderbuffer:GL_RENDERBUFFER];
    }
    return success;
}

- (int) getDefaultFramebuffer
{
    return defaultFramebuffer;
}


#pragma mark -
#pragma mark notification

#pragma mark -
#pragma mark delegate


#pragma mark -
#pragma mark private

/**
 优先支持opengles3.0,在不支持3.0的设备上切换为2.0
 ** warning: 暂时不支持3.0
 */
- (void)setUpContext {
    if (!self.mContext) {
        self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        if (!self.mContext) {
            self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        }
    }
    [self resetGLContext];
}

- (BOOL)resetGLContext
{
    if (self.mContext)
    {
        if ([EAGLContext currentContext] != self.mContext) {
            BOOL isSuccess = [EAGLContext setCurrentContext:self.mContext];
            if (!isSuccess) {
                NSLog(@"weixu resetGLContext1");
                return NO;
            }
        }
        return YES;
    }
    NSLog(@"weixu resetGLContext2");

    return NO;
}

- (void)createFramebuffer1:(CAEAGLLayer *)layer{
     [self deleteFramebuffer];
    //先要renderbuffer，然后framebuffer，顺序不能互换。
    
    // OpenGlES共有三种：colorBuffer，depthBuffer，stencilBuffer。
    // 生成一个renderBuffer，id是_colorRenderBuffer
    glGenRenderbuffers(1, &colorRenderbuffer);
    // 设置为当前renderBuffer
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    //为color renderbuffer 分配存储空间
    [self.mContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
    
    // FBO用于管理colorRenderBuffer，离屏渲染
    glGenFramebuffers(1, &defaultFramebuffer);
    //设置为当前framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
    // 将 _colorRenderBuffer 装配到 GL_COLOR_ATTACHMENT0 这个装配点上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
}

- (void)createFramebuffer:(CAEAGLLayer *)layer
{
    [self deleteFramebuffer];
    if (self.mContext && !defaultFramebuffer )
    {
        [EAGLContext setCurrentContext:self.mContext];
        
        glGenFramebuffers(1, &defaultFramebuffer);
        glGenRenderbuffers(1, &colorRenderbuffer);
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        
        if (layer && !self.isOffscreenRender) {
            [self.mContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);

        }
//        else {
//            framebufferHeight = 1280;
//            framebufferWidth = 720;
//        }
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8_OES, framebufferWidth, framebufferHeight);

        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, framebufferWidth, framebufferHeight);

    }
}

- (void)deleteFramebuffer
{
    if (self.mContext)
    {
        [EAGLContext setCurrentContext:self.mContext];
        
        if (defaultFramebuffer)
        {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer)
        {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
        
        if( depthRenderbuffer )
        {
            glDeleteRenderbuffers(1, &depthRenderbuffer);
            depthRenderbuffer = 0;
        }
    }
}


@end
