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
#import <OpenGLES/EAGL.h>

@interface EAGLEngine ()
{
    GLint framebufferWidth;
    GLint framebufferHeight;
    
    GLuint defaultFramebuffer, colorRenderbuffer, depthRenderbuffer;
    
    GLuint _msaaFramebuffer, _msaaRenderBuffer, _msaaDepthBuffer;
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

- (void)setFramebuffer
{
    if (self.mContext)
    {
        if ([EAGLContext currentContext] != self.mContext) {
            [EAGLContext setCurrentContext:self.mContext];
        }

        if(_msaaFramebuffer)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _msaaFramebuffer);

            glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, _msaaFramebuffer);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, defaultFramebuffer);

            glResolveMultisampleFramebufferAPPLE();

            GLenum attachments[] = {GL_DEPTH_ATTACHMENT, GL_COLOR_ATTACHMENT0};
            glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, attachments);
        }
        
        glResolveMultisampleFramebufferAPPLE();
        glBindFramebuffer(GL_FRAMEBUFFER, _msaaFramebuffer);
        
    }
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


#pragma mark -
#pragma mark notification

#pragma mark -
#pragma mark delegate


#pragma mark -
#pragma mark private

/**
 优先支持opengles3.0,在不支持3.0的设备上切换为2.0
 */
- (void)setUpContext {
    if (!self.mContext) {
        self.mContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
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
            [EAGLContext setCurrentContext:self.mContext];
        }
        return YES;
    }
    return NO;
}

- (void)createFramebuffer:(CAEAGLLayer *)layer
{
    [self deleteFramebuffer];
    //add by xhx
//    _msaaFramebuffer = _msaaRenderBuffer = 0;//add over
    
    if (self.mContext && !defaultFramebuffer )
    {
        [EAGLContext setCurrentContext:self.mContext];
        
        // Create default framebuffer object. modified by xhx
        glGenFramebuffers(1, &defaultFramebuffer);
        glGenRenderbuffers(1, &colorRenderbuffer);
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        
        if (layer && !self.isOffscreenRender) {
            [self.mContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
        }
        
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, framebufferWidth, framebufferHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
        
        
        //normal depth buffer
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, framebufferWidth, framebufferHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
        
        
        glGenFramebuffers(1, &_msaaFramebuffer);
        glGenRenderbuffers(1, &_msaaRenderBuffer);

        glBindFramebuffer(GL_FRAMEBUFFER, _msaaFramebuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _msaaRenderBuffer);

        // Samples is the amount of pixels the MSAA buffer uses to make one pixel on the render // buffer. Use a small number like 2 for the 3G and below and 4 or more for newer models
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, 4, GL_RGBA8_OES, framebufferWidth, framebufferHeight);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _msaaRenderBuffer);
        glGenRenderbuffers(1, &_msaaDepthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _msaaDepthBuffer);

        GLuint attachmentType = GL_DEPTH_COMPONENT16;//;
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, 4, attachmentType, framebufferWidth , framebufferHeight);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _msaaDepthBuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
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
        
        if(_msaaRenderBuffer) {
            glDeleteRenderbuffers(1, &_msaaRenderBuffer);
            _msaaRenderBuffer = 0;
        }
        
        if(_msaaDepthBuffer) {
            glDeleteRenderbuffers(1, &_msaaDepthBuffer);
            _msaaDepthBuffer = 0;
        }
        
        if(_msaaFramebuffer) {
            glDeleteFramebuffers(1, &_msaaFramebuffer);
            _msaaFramebuffer = 0;
        }
    }
}


@end
