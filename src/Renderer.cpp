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

Renderer::Renderer(){
    mShaderProgram = nullptr;
}

Renderer::~Renderer(){
    
}

void Renderer::setupGL(){
    
}
void Renderer::setupViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void Renderer::render(){
    glClearColor(0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLuint vba;
    glGenBuffers(1, &vba);
    glBindBuffer(GL_ARRAY_BUFFER, vba);

    glBufferData(GL_ARRAY_BUFFER, sizeof(mRenderData.mVertices[0]) * mRenderData.mVertices.size() , mRenderData.mVertices.data(), GL_STATIC_DRAW);
    if (mShaderProgram == nullptr) {
        printf("weixu\n");
        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
    }

    mShaderProgram->useProgram();
    
    GLint positionAttribLocation = glGetAttribLocation(mShaderProgram->mProgram, "position");
    glEnableVertexAttribArray(positionAttribLocation);
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (char *)0);
    

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteBuffers(1, &vba);
    
}

void Renderer::updataRenderData(RenderData renderData) {
    mRenderData = renderData;
}
