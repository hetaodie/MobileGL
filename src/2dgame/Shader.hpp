//
//  Shader.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/6/5.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#elif __ANDROID__
#include <GLES3/gl2.h>
#include <GLES3/gl2ext.h>
#include <GLES3/gl2platform.h>
#include <EGL/egl.h>
#endif

class Shader
{
public:
    // State
    GLuint ID;
    // Constructor
    Shader() { }
    // Sets the current shader as active
    Shader  &Use();
    // Compiles the shader from given source code
    void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource); // Note: geometry source code is optional
    // Utility functions
    void    SetFloat    (const GLchar *name, GLfloat value, GLboolean useShader = false);
    void    SetInteger  (const GLchar *name, GLint value, GLboolean useShader = false);
    void    SetVector2f (const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void    SetVector2f (const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void    SetVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void    SetVector3f (const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void    SetVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void    SetVector4f (const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void    SetMatrix4  (const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    // Checks if compilation or linking failed and if so, print the error logs
    void    checkCompileErrors(GLuint object, std::string type);
};
#endif /* Shader_hpp */
