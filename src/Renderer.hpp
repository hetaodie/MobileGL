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
#include <map>
#include <stdio.h>
#include "ShaderProgram.hpp"
#include "Camera.hpp"


namespace renderer {
    struct RenderData{
        std::vector<float> mVertices;
        int vertexNum;
        std::vector<unsigned short> index;
    };
    
    struct ImageData{
        unsigned char *mData;
        int mWidth;
        int mHeight;
        
//        ImageData() {
//            mData= nullptr;
//            mWidth = 0;
//            mHeight = 0;
//        }
//        
//        ImageData& operator = (const ImageData& copy)
//        {
//            mData = copy.mData;
//            mWidth = copy.mWidth;
//            mHeight = copy.mHeight;
//            return *this;
//        }
//        
//        void copy(ImageData item) {
//            mData = item.mData;
//            mWidth = item.mWidth;
//            mHeight = item.mHeight;
//        }
    };
    
    class Renderer {
    public:

        Renderer();
        ~Renderer();
        void setupViewport(int x, int y, int width, int height);
        void updataRenderData(RenderData renderData);
        void render();
        void setupImageData(unsigned char *data, int width, int height,std::string name);\
        void loadCubeImageData(std::vector<ImageData> cubeData);
    private:
        void createVBO(GLuint &vbo, float *data, int size);
    private:
        void setupGL();
        RenderData mRenderData;
        ShaderProgram *mShaderProgram;
        ShaderProgram *mLightShaderProgram;

        GLuint mVbo;
        GLuint mEbo;
        GLuint mTexture;
        std::vector<GLuint> mTextureVector;
        std::map<std::string,GLuint> mTextureMap;
        int mWidth, mHeight;
        Camera *mCamera;
        
        GLuint mCubeVBO, mPlaneVBO, mQuadVBO;
        GLuint mSkybox, mSkyboxTexture;
    };
};

#endif /* Renderer_hpp */
