//
//  EAGLView.h
//  Avatar-demo
//
//  Created by weixu on 2017/11/15.
//  Copyright © 2017年 Buddy. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
@class EAGLView;

@protocol EAGLViewDelegate <NSObject>

- (void)glView:(EAGLView *)view changeFrame:(CGRect)frame;
@end

@interface EAGLView : UIView
@property (nonatomic, weak) id<EAGLViewDelegate>delegate;
- (void)setupViewContentScaleFactor:(float)value;

@end

