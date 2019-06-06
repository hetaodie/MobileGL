//
//  Texture2D.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/6/5.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp
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

class Texture2D
{
public:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint ID;
    // Texture image dimensions
    GLuint Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    GLuint Internal_Format; // Format of texture object
    GLuint Image_Format; // Format of loaded image
    // Texture configuration
    GLuint Wrap_S; // Wrapping mode on S axis
    GLuint Wrap_T; // Wrapping mode on T axis
    GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
    // Constructor (sets default texture modes)
    Texture2D();
    // Generates texture from image data
    void Generate(GLuint width, GLuint height, unsigned char* data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};
#endif /* Texture2D_hpp */
