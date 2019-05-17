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
using namespace renderer;

Renderer::Renderer():mShaderProgram(nullptr), mVbo(0), mEbo(0){
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

    glClearColor(0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);

    if (mShaderProgram == nullptr) {
        printf("weixu\n");
        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
    }

    if (mRedShaderProgram == nullptr) {
        mRedShaderProgram = new ShaderProgram(vertexShader.c_str(), redfragmentShader.c_str());
    }
    
    GLint positionAttribLocation = glGetAttribLocation(mShaderProgram->mProgram, "position");
    glEnableVertexAttribArray(positionAttribLocation);
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)0);
    
    GLint vertexColorLocation = glGetAttribLocation(mShaderProgram->mProgram, "vertexColor");
    glEnableVertexAttribArray(vertexColorLocation);
    glVertexAttribPointer(vertexColorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)(3 * sizeof(float)));
    
    mShaderProgram->useProgram();
    if (mRenderData.index.size() > 0) {
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
    } else {
        GLsizei num = (GLsizei)mRenderData.mVertices.size()/mRenderData.vertexNum;
        glDrawArrays(GL_TRIANGLES, 0, num);
    }
    
    mRedShaderProgram->useProgram();
    GLint redLocation = glGetAttribLocation(mRedShaderProgram->mProgram, "position");
    glEnableVertexAttribArray(redLocation);
    glVertexAttribPointer(redLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);


}

void Renderer::updataRenderData(RenderData renderData) {
    mRenderData = renderData;
    glBufferData(GL_ARRAY_BUFFER, sizeof(mRenderData.mVertices[0]) * mRenderData.mVertices.size() , mRenderData.mVertices.data(), GL_STATIC_DRAW);
    
    if (mRenderData.index.size() > 0) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mRenderData.index[0]) * mRenderData.index.size(), mRenderData.index.data(), GL_STATIC_DRAW);
    } else {
        
    }
}
