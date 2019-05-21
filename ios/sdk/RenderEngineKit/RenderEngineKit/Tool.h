//
//  Tool.h
//  RenderEngineKit
//
//  Created by weixu on 2019/5/17.
//  Copyright © 2019 weixu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface Tool : NSObject
+(unsigned char *)getImagePixel:(NSString *)path;
+(unsigned char *)getImage:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
