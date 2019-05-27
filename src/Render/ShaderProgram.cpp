//
//  ShaderProgram.cpp
//  RenderEngineKit
//
//  Created by weixu on 2019/5/16.
//  Copyright © 2019 weixu. All rights reserved.
//

#include "ShaderProgram.hpp"
#include <iostream>
using namespace renderer;
ShaderProgram::ShaderProgram(const char* vtxSrc, const char* fragSrc) {
    createProgram(vtxSrc, fragSrc);
}

ShaderProgram::~ShaderProgram() {
    
}

void ShaderProgram::useProgram() {
    glUseProgram(mProgram);
}

GLuint ShaderProgram::createShader(GLenum shaderType, const char *src) {
    GLuint shader;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
//#ifdef DEBUG
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout <<"weixu " << shaderType<< " shader comple error ,the info is :"<<infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
//#endif
    
    return shader;
}

void ShaderProgram::createProgram(const char *vtxSrc, const char *fragSrc) {
    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
    GLuint program;
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vtxSrc);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragSrc);
    
    if (vertexShader == 0 || fragmentShader == 0) {
        return;
    }
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
//#ifdef DEBUG
    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                printf("weixu program%s\n", infoLog);
                free(infoLog);
                infoLog = nullptr;
            }
        }
        glDeleteProgram(program);
        program = 0;
    }
//#endif
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    mProgram = program;
}
