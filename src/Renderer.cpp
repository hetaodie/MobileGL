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
#include <sstream>

#include "2dgame/game.hpp"

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



long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000)/1000;
}

using namespace renderer;

Renderer::Renderer():mShaderProgram(nullptr),mLightShaderProgram(nullptr), mVbo(0), mEbo(0),mTexture(0){
//    createVBO(mCubeVBO, quadVertices, 30);
//    createVBO(mSkybox, skyboxVertices,108);
    mCamera = new Camera(glm::vec3(0.0, 0.0, 5.0));
    lastFrame = 0;
}

void Renderer::createVBO(GLuint &vbo, float *data, int size) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * size, data,  GL_STATIC_DRAW);
}


Renderer::~Renderer(){
    glDeleteBuffers(1, &mVbo);
}

void Renderer::setupGL(){
    
}
void Renderer::setupViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
    mWidth = width;
    mHeight = height;
    mBreakout = Game(mWidth, mHeight);
    mBreakout.Init(vertexShader, fragShader);
    mBreakout.State = GAME_ACTIVE;

}


void Renderer::render(){
    
    long currentFrame = getCurrentTime();
    long deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // Manage user input
    mBreakout.ProcessInput(deltaTime);
//
    // Update Game state
    mBreakout.Update(deltaTime);
//
    // Render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    mBreakout.Render(mWidth, mHeight);
    
//    static float rotate = 0.0;
//    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//
////    glClearColor(0, 0.0, 1.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    GLint oldFBO;
//    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);
//
//    GLuint hdrFBO;
//    glGenFramebuffers(1, &hdrFBO);
//    // - Create floating point color buffer
//    GLuint colorBuffer;
//    glGenTextures(1, &colorBuffer);
//    glBindTexture(GL_TEXTURE_2D, colorBuffer);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // - Create depth buffer (renderbuffer)
//    GLuint rboDepth;
//    glGenRenderbuffers(1, &rboDepth);
//    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, mWidth, mHeight);
//    // - Attach buffers
//    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//        GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//        printf("Framebuffer not complete! = %u",result);
//    }
//
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
//
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//        GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//        printf("Framebuffer not complete! = %u",result);
//    }
//
//    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
//
//
//    if (mLightShaderProgram == nullptr) {
//        mLightShaderProgram = new ShaderProgram(lightVertexShader.c_str(), lightFragShader.c_str());
//    }
//
//    if (mShaderProgram == nullptr) {
//        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragShader.c_str());
//    }
//
//    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    mLightShaderProgram->useProgram();
//
//    std::vector<glm::vec3> lightPositions;
//    lightPositions.push_back(glm::vec3(0.0f, 0.0f, 49.5f)); // back light
//    lightPositions.push_back(glm::vec3(-1.4f, -1.9f, 9.0f));
//    lightPositions.push_back(glm::vec3(0.0f, -1.8f, 4.0f));
//    lightPositions.push_back(glm::vec3(0.8f, -1.7f, 6.0f));
//    // - Colors
//    std::vector<glm::vec3> lightColors;
//    lightColors.push_back(glm::vec3(200.0f, 200.0f, 200.0f));
//    lightColors.push_back(glm::vec3(0.1f, 0.0f, 0.0f));
//    lightColors.push_back(glm::vec3(0.0f, 0.0f, 0.2f));
//    lightColors.push_back(glm::vec3(0.0f, 0.1f, 0.0f));
////    lightColors.push_back(glm::vec3(1.f, 0.0f, 0.0f));
////    lightColors.push_back(glm::vec3(0.0f, 1.f, 0.0f));
////    lightColors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
//
//
//    glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
//
//
//    glm::mat4 model = glm::mat4(1.0);
//    glm::mat4 view;
//    glm::mat4 projection;
//
//    GLuint woodTexture = mTextureMap.at("wood");
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, woodTexture);
//    glUniform1i(glGetUniformLocation(mLightShaderProgram->mProgram, "diffuseTexture"), 0);
//
//    view = mCamera->GetViewMatrix();
//    projection = glm::perspective(mCamera->Zoom, (float)mWidth / (float)mHeight, 0.1f, 100.0f);
//    glUniformMatrix4fv(glGetUniformLocation(mLightShaderProgram->mProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//    glUniformMatrix4fv(glGetUniformLocation(mLightShaderProgram->mProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//    for (GLuint i = 0; i < lightPositions.size(); i++)
//    {
//        glUniform3fv(glGetUniformLocation(mLightShaderProgram->mProgram, ("lights[" + std::to_string(i) + "].Position").c_str()), 1, &lightPositions[i][0]);
//        glUniform3fv(glGetUniformLocation(mLightShaderProgram->mProgram, ("lights[" + std::to_string(i) + "].Color").c_str()), 1, &lightColors[i][0]);
//    }
//    glUniform3fv(glGetUniformLocation(mLightShaderProgram->mProgram, "viewPos"), 1, &mCamera->Position[0]);
//    // - render tunnel
//    model = glm::mat4();
//    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
////    model = glm::rotate(model, -rotate, glm::vec3(1.0, 1.0, 0.0));
//
//    model = glm::scale(model, glm::vec3(2.5f, 2.5f,60.0f));
//    glUniformMatrix4fv(glGetUniformLocation(mLightShaderProgram->mProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    glUniform1i(glGetUniformLocation(mLightShaderProgram->mProgram, "inverse_normals"), true);
//    RenderCube();
//
//    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
////    RenderCube();
//
////
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    mShaderProgram->useProgram();
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, colorBuffer);
//    glUniform1i(glGetUniformLocation(mLightShaderProgram->mProgram, "hdrBuffer"), 0);
//    glUniform1i(glGetUniformLocation(mShaderProgram->mProgram, "hdr"), true);
//    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "exposure"), exposure + rotate);
//    RenderQuad();
//
////    glBindTexture(GL_TEXTURE_2D, 0);
////    glDeleteBuffers(1, &colorBuffer);
////    model = glm::mat4();
////    model = glm::translate(model, lightPos);
////    model = glm::scale(model, glm::vec3(0.1f));
////    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram->mProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
////    RenderQuad();
//    glDeleteTextures(1, &colorBuffer);
//    glDeleteFramebuffers(1, &hdrFBO);
//    glDeleteRenderbuffers(1, &rboDepth);
//    rotate += 0.001;
//    if (rotate > 1) {
//        rotate = 0;
//    }
}


void Renderer::updataRenderData(RenderData renderData) {
//    mRenderData = renderData;
//    glBufferData(GL_ARRAY_BUFFER, sizeof(mRenderData.mVertices[0]) * mRenderData.mVertices.size() , mRenderData.mVertices.data(), GL_STATIC_DRAW);
//
//    if (mRenderData.index.size() > 0) {
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mRenderData.index[0]) * mRenderData.index.size(), mRenderData.index.data(), GL_STATIC_DRAW);
//    } else {
//
//    }
    
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

void Renderer::setupImageData(unsigned char *data, int width, int height,std::string name) {
    mBreakout.loadImage(data, width, height, false);
//    GLuint texture = createTexture2D(GL_RGBA, width, height, data);
//    mTextureVector.push_back(texture);
//    mTextureMap.insert(std::pair<std::string, GLint>(name, texture));

}

GLuint loadCubemap(std::vector<ImageData> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        ImageData data = faces[i];
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data.mWidth, data.mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.mData);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return textureID;
}

void Renderer::loadCubeImageData(std::vector<ImageData> cubeData) {
    mSkyboxTexture = loadCubemap(cubeData);
}


