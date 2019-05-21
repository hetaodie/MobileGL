//
//  Renderer.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/5/16.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp
#include <string>
#include <vector>
#include <stdio.h>
#include "ShaderProgram.hpp"

namespace renderer {
    struct RenderData{
        std::vector<float> mVertices;
        int vertexNum;
        std::vector<unsigned short> index;
    };
    
    class Renderer {
    public:

        Renderer();
        ~Renderer();
        void setupViewport(int x, int y, int width, int height);
        void updataRenderData(RenderData renderData);
        void render();
        void setupImageData(unsigned char *data, int width, int height);
    private:
        void setupGL();
        RenderData mRenderData;
        ShaderProgram *mShaderProgram;
        ShaderProgram *mRedShaderProgram;

        GLuint mVbo;
        GLuint mEbo;
        GLuint mTexture;
    };
};

#endif /* Renderer_hpp */
