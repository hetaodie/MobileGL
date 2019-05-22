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
"attribute vec2 coord;\n"
"uniform mat4 model; \n"
"uniform mat4 view; \n"
"uniform mat4 projection; \n"
"uniform float move1;\n"
"varying vec4 color;\n"
"varying vec2 texCoord;\n"
"varying vec2 texCoord2;\n"
"void main()\n"
"{\n"
"   color = vec4(vertexColor,1.0);\n"
"   float y = coord.y - move1;\n"
//"   if(y > 1.0){ \n"
//"       y = y - 2.0 * move1;"
//"   }\n"
"   vec2 testCoord= vec2(coord.x, y); \n"
"   texCoord2 = testCoord;\n"
"   texCoord = coord;"
"   mat4 transform = projection * view * model; \n"
"   gl_Position = transform * vec4(position, 1.0);\n"
"}\n";

static std::string fragmentShader =
"precision mediump float; \n"
"precision mediump int; \n"
"varying vec4 color;\n"
"varying vec2 texCoord;\n"
"varying vec2 texCoord2;\n"
"uniform sampler2D ourTexture0;\n"
"uniform sampler2D ourTexture1;\n"
"uniform int isHidden;\n"
"uniform float changeAlpha;\n"
"void main() \n"
"{ \n"
"   vec2 TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n"
"   vec2 TexCoord2 = vec2(texCoord2.x, 1.0 - texCoord2.y); \n"
"   vec4 texture0= texture2D(ourTexture0, TexCoord); \n"
"   vec4 texture1= texture2D(ourTexture1, TexCoord2); \n"
"   vec4 fragColor = mix(texture0, texture1, texture1.w);\n"
"   gl_FragColor = fragColor; \n"
"}\n";

static std::string redfragmentShader =
"precision mediump float; \n"
"uniform vec4 unColor;"
"void main() \n"
"{ \n"
"   gl_FragColor = unColor;"
"}\n";

#endif /* Shader_h */
