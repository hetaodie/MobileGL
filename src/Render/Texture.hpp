//
//  Texture.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/5/21.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#endif

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>

namespace renderer {
    
    class Texture {
    public:
        Texture(const char * imageData);
        ~Texture();
    private:
        
    public:
        GLint textureId;
        
    };
};
#endif /* Texture_hpp */
