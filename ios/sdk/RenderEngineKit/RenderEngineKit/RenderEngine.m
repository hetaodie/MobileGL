//
//  RenderEngine.m
//  RenderEngineKit
//
//  Created by weixu on 2018/8/21.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import "RenderEngine.h"
#import "EAGLView.h"
#import "EAGLEngine.h"
#import "AVADisplayLinkTimer.h"
static int MAXFPS = 30;
static dispatch_queue_t kInvokingQueue = nil;
@interface RenderEngine()<EAGLViewDelegate>
@property (nonatomic, strong) EAGLEngine *glEngine;
@property (nonatomic, strong) EAGLView *eaglView;
@property (nonatomic, assign) CGSize mGLSize;
@property (nonatomic, assign) BOOL mIsRender;
@property (nonatomic, assign) BOOL isResignActive;

@end


@implementation RenderEngine{
    AVADisplayLinkTimer *_timer;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (id)initWithView:(UIView *)parentView {
    self = [super init];
    if (self) {
        [self setupRenderEngine];
        [self setupGLRender:parentView];
    }
    return self;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self setupRenderEngine];
        [self setupGLRender:nil];
    }
    return self;
}

- (void)setupView:(UIView *)parentView {
    if(parentView != nil) {
        [self setupRenderView:parentView];
    }
}

- (void)removeView:(UIView *)parentView {
    
}

- (void)startRender {
    if (!self.mIsRender)
    {
        __weak RenderEngine *weakSelf = self;
        _timer = [[AVADisplayLinkTimer alloc] initWithMaxfps:MAXFPS WithTimerHandler:^{
            RenderEngine *strongSelf = weakSelf;
            [strongSelf render];
        }];
        _timer.isPaused = NO;
        self.mIsRender = YES;
    }
}

- (void)stopRender {
    if (self.mIsRender)
    {
        [_timer invalidate];
        self.mIsRender = NO;
    }
}

- (void)glView:(EAGLView *)view changeFrame:(CGRect)frame {
    dispatch_async(kInvokingQueue, ^{
        dispatch_sync(dispatch_get_main_queue(), ^{
            [self setUpContext];
            [self resize:frame.size];
            self.mGLSize = frame.size;
            [self.glEngine createFramebuffer:(CAEAGLLayer *)view.layer];
        });
    });
}

- (void)addNotifation {
    NSNotificationCenter *notificationCenter =
    [NSNotificationCenter defaultCenter];
    [notificationCenter addObserver:self
                           selector:@selector(willResignActive)
                               name:UIApplicationWillResignActiveNotification
                             object:nil];
    [notificationCenter addObserver:self
                           selector:@selector(didBecomeActive)
                               name:UIApplicationDidBecomeActiveNotification
                             object:nil];
}

#pragma mark -
#pragma mark private

- (void)setupRenderEngine {
    [self addNotifation];
    [self setupData];
}

- (void)setupData {
    kInvokingQueue = dispatch_queue_create("render_Invoking", DISPATCH_QUEUE_SERIAL);
}

- (void)setupGLRender:(UIView *)view {
    EAGLEngine * eaglEngine = [[EAGLEngine alloc] init];
    self.glEngine = eaglEngine;
    
    [self setupRenderView:view];
    [self setUpContext];
}

- (void)setupRenderView:(UIView *)view {
    if (view == nil) {
        [self.glEngine createFramebuffer:nil];
    } else {
        EAGLView *eaglView = [[EAGLView alloc] init];
        [eaglView setBackgroundColor:[UIColor greenColor]];
        eaglView.translatesAutoresizingMaskIntoConstraints = NO;
        [view addSubview:eaglView];
        NSArray<NSLayoutConstraint *> *horizontalConstraint = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[eaglView]-0-|" options:(NSLayoutFormatAlignAllTop | NSLayoutFormatAlignAllBottom) metrics:nil views:NSDictionaryOfVariableBindings(view, eaglView)];
        [view addConstraints:horizontalConstraint];
        
        NSArray<NSLayoutConstraint *> *verticalConstraint = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[eaglView]-0-|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(view, eaglView)];
        [view addConstraints:verticalConstraint];
        self.eaglView = eaglView;
        self.eaglView.delegate = self;
        [self.glEngine createFramebuffer:(CAEAGLLayer *)self.eaglView.layer];
    }
}

- (void)setUpContext {
    [self.glEngine resetGLContext];
}

- (void)resize:(CGSize)size {
    [self setUpContext];
//    [self.mAvatarHelper resizeAvatar:size.width height:size.height];
}

- (void)render {
    if (self.isResignActive) {
        return;
    }
    dispatch_async(kInvokingQueue, ^{
        //添加用来渲染的代码
        [self setUpContext];
        [self.glEngine setFramebuffer];
        glEnable(GL_DEPTH_TEST); //auto:
        //添加用来渲染的代码
        glClearColor(1.0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        [self.glEngine presentFramebuffer];
        glDisable(GL_DEPTH_TEST); //auto:
    });
}

- (void)didBecomeActive {
    self.isResignActive = NO;
}

- (void)willResignActive {
    self.isResignActive = YES;
}

@end
