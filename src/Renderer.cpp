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

#include "glm/glm.hpp"
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

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000)/1000;
}

using namespace renderer;

Renderer::Renderer():mShaderProgram(nullptr), mVbo(0), mEbo(0),mTexture(0){
    if (mVbo == 0) {
        glGenBuffers(1, &mVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        
        glGenBuffers(1, &mEbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    }
    mCamera = new Camera(glm::vec3(0.0, 0.0, 10.0));
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
}



void Renderer::render(){
    static float addX = 0;
    static float addy = 0;
    static int rotation = 0;
    static int isHidden=1;
    glClearColor(0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);

    if (mShaderProgram == nullptr) {
        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
    }

    if (mLightShaderProgram == nullptr) {
        mLightShaderProgram = new ShaderProgram(lightVertexShader.c_str(), lightFragmentShader.c_str());
    }
    mShaderProgram->useProgram();
    
    GLint positionAttribLocation = glGetAttribLocation(mShaderProgram->mProgram, "position");
    glEnableVertexAttribArray(positionAttribLocation);
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)0);

    GLint normalLocation = glGetAttribLocation(mShaderProgram->mProgram, "normal");
    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)(3 * sizeof(float)));

    GLint textureLocation = glGetAttribLocation(mShaderProgram->mProgram, "texCoords");
    glEnableVertexAttribArray(textureLocation);
    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)(6 * sizeof(float)));

    
    GLint texture = mTextureMap.at("diffuseImage");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(mShaderProgram->mProgram, "material.diffuse"), 0);
    
    GLint texture2 = mTextureMap.at("specularMap");
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(mShaderProgram->mProgram, "material.specular"), 1);
    
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
//    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "dirLight.direction"), 0, 0, 20.0f);

    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "dirLight.ambient"), 1.05f, 1.05f, 1.05f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
    // Point light 1
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[0].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[0].linear"), 0.09);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[0].quadratic"), 0.032);
    // Point light 2
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[1].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[1].linear"), 0.09);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[1].quadratic"), 0.032);
    // Point light 3
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[2].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[2].linear"), 0.09);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[2].quadratic"), 0.032);
    // Point light 4
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[3].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[3].linear"), 0.09);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "pointLights[3].quadratic"), 0.032);
//    GLint viewPosLoc = glGetUniformLocation(mShaderProgram->mProgram, "viewPos");
    glUniform3f(glGetUniformLocation(mShaderProgram->mProgram, "viewPos"),  mCamera->Position.x, mCamera->Position.y, mCamera->Position.z);
    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "material.shininess"),  32.0); // 依旧把光源设置为白色

    glm::mat4 view;
    view = mCamera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(mCamera->Zoom, (GLfloat)mWidth / (GLfloat)mHeight, 0.1f, 100.0f);
    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(mShaderProgram->mProgram, "model");
    GLint viewLoc  = glGetUniformLocation(mShaderProgram->mProgram, "view");
    GLint projLoc  = glGetUniformLocation(mShaderProgram->mProgram, "projection");
    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    GLint normalM = glGetUniformLocation(mShaderProgram->mProgram, "normalMatrix");

    glm::mat4 model;
    for (GLuint i = 0; i < 10; i++)
    {
        model = glm::mat4();
        model = glm::translate(model, cubePositions[i]);
        GLfloat angle = 20.0f * i;
        model = glm::rotate(model, angle + rotation, glm::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
        glUniformMatrix3fv(normalM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    
    mLightShaderProgram->useProgram();
    
    positionAttribLocation = glGetAttribLocation(mLightShaderProgram->mProgram, "aPos");
    glEnableVertexAttribArray(positionAttribLocation);
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)0);

    // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
    modelLoc = glGetUniformLocation(mLightShaderProgram->mProgram, "model");
    viewLoc  = glGetUniformLocation(mLightShaderProgram->mProgram, "view");
    projLoc  = glGetUniformLocation(mLightShaderProgram->mProgram, "projection");
    
    // Set matrices
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    // We now draw as many light bulbs as we have point lights.
    for (GLuint i = 0; i < 4; i++)
    {
        model = glm::mat4();
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
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

void Renderer::setupImageData(unsigned char *data, int width, int height,std::string name) {
    GLuint texture = createTexture2D(GL_RGBA, width, height, data);
    mTextureVector.push_back(texture);
    mTextureMap.insert(std::pair<std::string, GLint>(name, texture));

}

