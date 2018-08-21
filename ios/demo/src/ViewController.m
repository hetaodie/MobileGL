//
//  ViewController.m
//  GLESStudy
//
//  Created by weixu on 2018/1/25.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import "ViewController.h"
#import <RenderEngineKit/RenderEngineKit.h>

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIView *parentView;
@property (nonatomic, strong) RenderEngine *mRenderEngine;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    RenderEngine *renderEngine = [[RenderEngine alloc] initWithView:self.parentView];
    self.mRenderEngine = renderEngine;
    [renderEngine startRender];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
//    RenderEngine *renderEngine = [[RenderEngine alloc] initWithView:self.parentView];
//    self.mRenderEngine = renderEngine;
//    [renderEngine startRender];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


@end
