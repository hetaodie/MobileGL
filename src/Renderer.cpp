//
//  Renderer.cpp
//  RenderEngineKit
//
//  Created by weixu on 2019/5/16.
//  Copyright © 2019 weixu. All rights reserved.
//
#include "Shader.h"
#include "Renderer.hpp"
#include "Shader.h"
#include <sys/time.h>
#include <cmath>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#endif


GLfloat triangleVertices1[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

using namespace renderer;

Renderer::Renderer():mShaderProgram(nullptr), mVbo(0), mEbo(0),mTexture(0){
    if (mVbo == 0) {
        glGenBuffers(1, &mVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        
        glGenBuffers(1, &mEbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    }
}

Renderer::~Renderer(){
    glDeleteBuffers(1, &mVbo);
}

void Renderer::setupGL(){
    
}
void Renderer::setupViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}



void Renderer::render(){
    static float addX = 0;
    static float addy = 0;
    static int isHidden;
    glClearColor(0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);

    if (mShaderProgram == nullptr) {
        printf("weixu\n");
        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
    }

//    if (mRedShaderProgram == nullptr) {
//        mRedShaderProgram = new ShaderProgram(vertexShader.c_str(), redfragmentShader.c_str());
//    }
//
    GLint positionAttribLocation = glGetAttribLocation(mShaderProgram->mProgram, "position");
    glEnableVertexAttribArray(positionAttribLocation);
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)0);

    GLint vertexColorLocation = glGetAttribLocation(mShaderProgram->mProgram, "vertexColor");
    glEnableVertexAttribArray(vertexColorLocation);
    glVertexAttribPointer(vertexColorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)(3 * sizeof(float)));
    
    GLint textureLocation = glGetAttribLocation(mShaderProgram->mProgram, "coord");
    glEnableVertexAttribArray(textureLocation);
    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)(6 * sizeof(float)));
    
    GLuint moveU = glGetUniformLocation(mShaderProgram->mProgram, "move1");
    glUniform1f(moveU, addX);
    
    
    GLuint hiddenL = glGetUniformLocation(mShaderProgram->mProgram, "isHidden");
    glUniform1i(hiddenL, isHidden);
    //    glVertexAttrib1f(moveLocation, 0.1);
    
    
    std::vector<GLuint>::iterator iVector = mTextureVector.begin();
    int num = 0;
    while(iVector != mTextureVector.end())
        
    {
        std::string sample = "ourTexture" + std::to_string(num);;
        GLint texture = *iVector;
        glActiveTexture(GL_TEXTURE0 + num);
        glBindTexture(GL_TEXTURE_2D, texture);
        GLuint uvLocation = glGetUniformLocation(mShaderProgram->mProgram, sample.c_str());
        glUniform1i(uvLocation, num);
        ++iVector;
        num++;
    }


    glm::mat4 trans;
//    trans = glm::translate(trans, glm::vec3(addX, addy, 0.0f));
//    long time = getCurrentTime();
//    float angle = (time % 360) / 10;
//    printf("weixu = %f \n", angle);
//    trans = glm::rotate(trans,addX, glm::vec3(1.0f, 1.0f, 0.0f));
//
//    GLuint transformLoc = glGetUniformLocation(mShaderProgram->mProgram, "transform");
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    mShaderProgram->useProgram();
    if (mRenderData.index.size() > 0) {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    } else {
        GLsizei num = (GLsizei)mRenderData.mVertices.size()/mRenderData.vertexNum;
        glDrawArrays(GL_TRIANGLES, 0, num);
    }
    addX += 0.05;
    if (addX > 1) {
        addX = 0;
    }
    
    addy++;
    if(addy > 10) {
        addy = 0;
        isHidden = 0;
    } else if(addy > 5){
        isHidden = 1;
    }
}


void Renderer::updataRenderData(RenderData renderData) {
    mRenderData = renderData;
    glBufferData(GL_ARRAY_BUFFER, sizeof(mRenderData.mVertices[0]) * mRenderData.mVertices.size() , mRenderData.mVertices.data(), GL_STATIC_DRAW);
    
    if (mRenderData.index.size() > 0) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mRenderData.index[0]) * mRenderData.index.size(), mRenderData.index.data(), GL_STATIC_DRAW);
    } else {
        
    }
    
}

GLuint createTexture2D(GLenum format, int width, int height, void *data)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void Renderer::setupImageData(unsigned char *data, int width, int height) {
//    if (mTexture == 0) {
//        GLuint texture;
//        glGenTextures(1 , &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        GLuint texture = createTexture2D(GL_RGBA, width, height, data);
        mTextureVector.push_back(texture);
//        mTexture = texture;
//    }
}

