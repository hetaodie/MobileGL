//
//  testData.h
//  RenderEngineKit
//
//  Created by weixu on 2019/5/16.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef testData_h
#define testData_h

GLfloat triangleVertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
};


GLfloat squareVertices[] = {
    // 第一个三角形
    0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // 右上角
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右下角
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 左上角
    // 第二个三角形
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右下角
    -0.5f, -0.5f, 0.0f,1.0f, 0.0f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f // 左上角
};

GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,// 右上角
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,1.0f, 0.0f,// 右下角
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f, 0.0f,// 左下角
    -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f,  0.0f, 1.0f  // 左上角
};

GLushort indices[] = { // 注意索引从0开始!
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};


#endif /* testData_h */
