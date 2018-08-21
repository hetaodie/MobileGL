//
//  RenderEngine.h
//  RenderEngineKit
//
//  Created by weixu on 2018/8/21.
//  Copyright © 2018年 weixu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface RenderEngine : NSObject

//测试

/**
 此传递的view是将要渲染的view的父类

 @param parentView 渲染view 的父view
 @return 返回实例
 */
- (id)initWithView:(UIView *)parentView;

/**
 当通过其他方式init方式初始化的时候，后面可以动态设置view

 @param parentView 渲染view的父view
 */
- (void)setupView:(UIView *)parentView;

/**
 使渲染view从父view中移除掉，当调用此函数时，渲染还在进行，变成了离屏渲染

 @param parentView 渲染view的父view
 */
- (void)removeView:(UIView *)parentView;

/**
 当调用此接口开始渲染
 */
- (void)startRender;

/**
 当调用此接口，停止渲染
 */
- (void)stopRender;
@end
