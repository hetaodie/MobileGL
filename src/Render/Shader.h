//
//  Shader.h
//  RenderEngineKit
//
//  Created by weixu on 2019/5/16.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef Shader_h
#define Shader_h
#include <string>
static std::string vertexShader =
"attribute vec3 position;\n"
"attribute vec3 vertexColor;\n"
"varying vec4 color;\n"
"void main()\n"
"{\n"
"   color = vec4(vertexColor,1.0);\n"
"   gl_Position = vec4(position, 1.0);\n"
"}\n";

static std::string fragmentShader =
"precision mediump float; \n"
"varying vec4 color;\n"
"void main() \n"
"{ \n"
"   gl_FragColor = color;"
"}\n";

#endif /* Shader_h */
