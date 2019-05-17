//
//  ShaderProgram.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/5/16.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <string>

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#endif

namespace renderer {
    
    class ShaderProgram {
    public:
        ShaderProgram(const char* vtxSrc, const char* fragSrc);
        ~ShaderProgram();
        void useProgram();
        
        GLuint getUniformLocation(const GLchar* name);
        GLuint getUniformLocation(std::string name);
        GLuint getAttribLocation(const GLchar* name);
        
//    private:
        GLuint mProgram;
    private:
        GLuint createShader(GLenum shaderType, const char *src);
        void createProgram(const char *vtxSrc, const char *fragSrc);
    };
};
#endif /* ShaderProgram_hpp */
