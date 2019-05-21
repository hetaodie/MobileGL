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
"uniform mat4 transform; \n"
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
"   gl_Position = vec4(position, 1.0);\n"
"}\n";

static std::string fragmentShader =
"precision mediump float; \n"
"varying vec4 color;\n"
"varying vec2 texCoord;\n"
"varying vec2 texCoord2;\n"
"uniform sampler2D ourTexture0;\n"
"uniform sampler2D ourTexture1;\n"
"void main() \n"
"{ \n"
"   vec2 TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n"
"   vec2 TexCoord2 = vec2(texCoord2.x, 1.0 - texCoord2.y); \n"
"   vec4 texture0= texture2D(ourTexture0, TexCoord); \n"
"   vec4 texture1= texture2D(ourTexture1, TexCoord2); \n"
"   vec4 texture = texture1; \n"
"   if (texture1.w == 0.0) { \n"
"       texture = texture0;\n"
"   } \n"
"   gl_FragColor = texture; \n"
//"   gl_FragColor = color; \n"
"}\n";

static std::string redfragmentShader =
"precision mediump float; \n"
"uniform vec4 unColor;"
"void main() \n"
"{ \n"
"   gl_FragColor = unColor;"
"}\n";

#endif /* Shader_h */
