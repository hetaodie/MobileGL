//
//  Tool.m
//  RenderEngineKit
//
//  Created by weixu on 2019/5/17.
//  Copyright © 2019 weixu. All rights reserved.
//

#import "Tool.h"

@implementation Tool
+(unsigned char *)getImagePixel:(NSString *)path {
    UIImage *image = [[UIImage alloc] initWithContentsOfFile:path];
    CFDataRef pixelData = CGDataProviderCopyData(CGImageGetDataProvider(image.CGImage));
    const uint8_t* data = CFDataGetBytePtr(pixelData);
    
    int width = (int)image.size.width;
    int height = (int)image.size.height;
    uint8_t *imgData = (uint8_t *)malloc(width*height*4);
    memcpy(imgData, data, width*height*4);
    return imgData;
}

+(unsigned char *)getImage:(UIImage *)image {
    CFDataRef pixelData = CGDataProviderCopyData(CGImageGetDataProvider(image.CGImage));
    uint8_t* data = (uint8_t*)CFDataGetBytePtr(pixelData);
    
    int width = (int)image.size.width;
    int height = (int)image.size.height;
    uint8_t *imgData = (uint8_t *)malloc(width*height*4);
    memcpy(imgData, data, width*height*4);
    return imgData;
}


@end
