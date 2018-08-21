//
//  EAGLView.m
//  GLESStudy
//
//  Created by weixu on 2018/1/25.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import "EAGLView.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface EAGLView () {
    GLuint colorBuffers;  // 定义颜色缓冲
    GLuint frameBuffers;  // 定义FBO
}

@property (nonatomic, strong) CAEAGLLayer *eaglLayer;
@property (nonatomic, strong) EAGLContext *context;
@end

@implementation EAGLView

#pragma mark -
#pragma mark lifecycle

/**
 当需要显示出openGLES绘制出来的内容是，需要把View的Layer设置为CAEAGLLayer
 
 @return 返回CAEAGLLayer
 */
+(Class)layerClass {
    return [CAEAGLLayer class];
}

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
        [self setupLayer];
        [self setupGL];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupGL];
    }
    return self;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self setupLayer];
        [self setupGL];
    }
    return self;
}

- (void)layoutSubviews {
    [EAGLContext setCurrentContext:self.context];
    [self destoryGL];
    [self setupGL];
    [self render];
}

#pragma mark -
#pragma mark public

/**
 <#Description#>
 */
- (void)render {
    glClearColor(0.0f, 1.f, 0.f, 1.0f);  //设置清屏颜色
   //用来指定要用清屏颜色来清除由mask指定的buffer，mask 可以是 GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT的自由组合
    glClear(GL_COLOR_BUFFER_BIT);
    //把FBO渲染出来的内容，渲染到view上
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}


#pragma mark -
#pragma mark notification

#pragma mark -
#pragma mark delegate


#pragma mark -
#pragma mark private

/**
 设置Layer相关属性，
 */
- (void)setupLayer {
    self.eaglLayer  = (CAEAGLLayer *)self.layer;
    self.eaglLayer.opaque = YES; // 默认情况下，layer 是不透明的，需要强制设置为透明，否则无法显示渲染出来的内容
    NSDictionary *drawablePropertyDic = @{kEAGLDrawablePropertyRetainedBacking:[NSNumber numberWithBool:NO],kEAGLDrawablePropertyColorFormat:kEAGLColorFormatRGBA8};
    self.eaglLayer.drawableProperties = drawablePropertyDic;
}

/**
 初始化设置GL相关参数
 */
- (void)setupGL {
    [self setupContext];
    [self setupRenderBuffer];
    [self setupFrameBuffer];
}

// 初始化EAGLContext 为opengles2 并设置为当前context。
- (void)setupContext {
    // 指定 OpenGL 渲染 API 的版本，在这里我们使用 OpenGL ES 2.0
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    self.context = [[EAGLContext alloc] initWithAPI:api];
    if (!self.context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    // 设置为当前上下文
    if (![EAGLContext setCurrentContext:self.context]) {
        self.context = nil;
        
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

/**
 设置渲染缓存，步骤为：1、生成缓存（缓存共有三种，color、depth、stencil）；2、把生成的buffer绑定到RenderBuffer中；3、分配存储空间
 */
- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &colorBuffers);
    glBindRenderbuffer(GL_RENDERBUFFER, colorBuffers);
    [self.context renderbufferStorage:GL_RENDERBUFFER fromDrawable:self.eaglLayer];
}

/**
 初始化framebuffer，framebuffer object 通常也被称之为 FBO，它相当于 buffer(color, depth, stencil)的管理者，三大buffer 可以附加到一个 FBO 上。我们是用 FBO 来在 off-screen buffer上进行渲染。
 */
- (void)setupFrameBuffer {
    glGenFramebuffers(1, &frameBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffers);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffers);
}

- (void)destoryGL {
    if (colorBuffers != 0) {
        glDeleteRenderbuffers(1, &colorBuffers);
        colorBuffers = 0;
    }
    
    if (frameBuffers != 0) {
        glDeleteFramebuffers(1, &frameBuffers);
        frameBuffers = 0;
    }
}

@end
