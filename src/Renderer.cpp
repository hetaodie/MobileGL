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
    mCamera = new Camera(glm::vec3(0.0, 0.0, 3.0));
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
        printf("weixu\n");
//        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
        mShaderProgram = new ShaderProgram(lightVertexShader.c_str(), fragmentShader.c_str());

    }

    if (mLightShaderProgram == nullptr) {
        mLightShaderProgram = new ShaderProgram(lightVertexShader.c_str(), lightFragmentShader.c_str());
    }
    mShaderProgram->useProgram();
    GLint positionAttribLocation = glGetAttribLocation(mShaderProgram->mProgram, "position");
    glEnableVertexAttribArray(positionAttribLocation);
    glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)0);

    GLint normalLocation = glGetAttribLocation(mShaderProgram->mProgram, "normal");
    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char *)(3 * sizeof(float)));
//    GLint vertexColorLocation = glGetAttribLocation(mShaderProgram->mProgram, "vertexColor");
//    glEnableVertexAttribArray(vertexColorLocation);
//    glVertexAttribPointer(vertexColorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)(3 * sizeof(float)));
//
//    GLint textureLocation = glGetAttribLocation(mShaderProgram->mProgram, "coord");
//    glEnableVertexAttribArray(textureLocation);
//    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (char *)(3 * sizeof(float)));
//
//    GLuint moveU = glGetUniformLocation(mShaderProgram->mProgram, "move1");
//    glUniform1f(moveU, addX);
//    
//
//    GLuint hiddenL = glGetUniformLocation(mShaderProgram->mProgram, "isHidden");
//    glUniform1i(hiddenL, isHidden);
//
//    GLuint alphaL = glGetUniformLocation(mShaderProgram->mProgram, "changeAlpha");
//    glUniform1f(alphaL, addy);
    //    glVertexAttrib1f(moveLocation, 0.1);
    
    
//    std::vector<GLuint>::iterator iVector = mTextureVector.begin();
//    int num = 0;
//    while(iVector != mTextureVector.end())
//
//    {
//        std::string sample = "ourTexture" + std::to_string(num);;
//        GLint texture = *iVector;
//        glActiveTexture(GL_TEXTURE0 + num);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        GLuint uvLocation = glGetUniformLocation(mShaderProgram->mProgram, sample.c_str());
//        glUniform1i(uvLocation, num);
//        ++iVector;
//        num++;
//    }

//    GLint objectColorLoc = glGetUniformLocation(mShaderProgram->mProgram, "objectColor");
    GLint lightColorLoc  = glGetUniformLocation(mShaderProgram->mProgram, "lightColor");
//    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);// 我们所熟悉的珊瑚红
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f); // 依旧把光源设置为白色
    
    GLint matAmbientLoc = glGetUniformLocation(mShaderProgram->mProgram, "material.ambient");
    GLint matDiffuseLoc = glGetUniformLocation(mShaderProgram->mProgram, "material.diffuse");
    GLint matSpecularLoc = glGetUniformLocation(mShaderProgram->mProgram, "material.specular");
    GLint matShineLoc = glGetUniformLocation(mShaderProgram->mProgram, "material.shininess");
    
    glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
    glUniform1f(matShineLoc, 32.0f);
    
    GLint lightAmbientLoc = glGetUniformLocation(mShaderProgram->mProgram, "light.ambient");
    GLint lightDiffuseLoc = glGetUniformLocation(mShaderProgram->mProgram, "light.diffuse");
    GLint lightSpecularLoc = glGetUniformLocation(mShaderProgram->mProgram, "light.specular");
    
    glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
    glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);// 让我们把这个光调暗一点，这样会看起来更自然
    glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
    
    glm::vec3 lightColor;
    lightColor.x = sin(addX * 2.0f);
    lightColor.y = sin(addX * 0.7f);
    lightColor.z = sin(addX * 1.3f);
    
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    
    glUniform3f(lightAmbientLoc, ambientColor.x, ambientColor.y, ambientColor.z);
    glUniform3f(lightDiffuseLoc, diffuseColor.x, diffuseColor.y, diffuseColor.z);
    
    glm::mat4 view;
    view = mCamera->GetViewMatrix();
    glm::mat4 projection;
    projection = glm::perspective(mCamera->Zoom, (float)mWidth/(float)mHeight, 0.1f, 1000.0f);


    GLuint viewL = glGetUniformLocation(mShaderProgram->mProgram, "view");
    glUniformMatrix4fv(viewL, 1, GL_FALSE, glm::value_ptr(view));
    
    
    GLuint projectionL = glGetUniformLocation(mShaderProgram->mProgram, "projection");
    glUniformMatrix4fv(projectionL, 1, GL_FALSE, glm::value_ptr(projection));
    
    glm::vec3 lightPos(0.f, 1.0, 0.0f);
    GLint lightPosLoc = glGetUniformLocation(mShaderProgram->mProgram, "lightPos");
    glUniform3f(lightPosLoc, mCamera->Position.x, mCamera->Position.y, mCamera->Position.z);


    
    GLint viewPosLoc = glGetUniformLocation(mShaderProgram->mProgram, "viewPos");
    glUniform3f(viewPosLoc, mCamera->Position.x, mCamera->Position.y, mCamera->Position.z);
//    mShaderProgram->useProgram();
    if (mRenderData.index.size() > 0) {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    } else {
        
        glm::mat4 model;
//        model = glm::translate(model, glm::vec3( 0.0f,  0.0f, -10.0f));
        model = glm::rotate(model, (float)rotation, glm::vec3(1.0f, 1.0f, 1.0f));
        GLuint modelL = glGetUniformLocation(mShaderProgram->mProgram, "model");
        glUniformMatrix4fv(modelL, 1, GL_FALSE, glm::value_ptr(model));
        
        GLint normalM = glGetUniformLocation(mShaderProgram->mProgram, "normalMatrix");
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
        glUniformMatrix3fv(normalM, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        
        glDrawArrays(GL_TRIANGLES, 0, mRenderData.vertexNum);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        mLightShaderProgram->useProgram();

        GLfloat radius = 10.0f;
        long time = getCurrentTime();
        GLfloat camX = sin(rotation/100.0) * radius;
        GLfloat camZ = cos(rotation/100.0) * radius;
        glm::mat4 view;
        view = mCamera->GetViewMatrix();
        glm::mat4 projection;
        projection = glm::perspective(mCamera->Zoom, (float)mWidth/(float)mHeight, 0.1f, 1000.0f);
        
        GLuint viewL = glGetUniformLocation(mLightShaderProgram->mProgram, "view");
        glUniformMatrix4fv(viewL, 1, GL_FALSE, glm::value_ptr(view));
        
        
        GLuint projectionL = glGetUniformLocation(mLightShaderProgram->mProgram, "projection");
        glUniformMatrix4fv(projectionL, 1, GL_FALSE, glm::value_ptr(projection));

        GLuint lightColorLoc2  = glGetUniformLocation(mLightShaderProgram->mProgram, "lightColor");
        glUniform3f(lightColorLoc2,  1.0f, 1.0f, 1.0f); // 依旧把光源设置为白色
        model = glm::mat4();
        
        model = glm::translate(model, lightPos);
//        model = glm::rotate(model, (float)-10.0, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.2f));

        GLuint modelLL = glGetUniformLocation(mLightShaderProgram->mProgram, "model");
        glUniformMatrix4fv(modelLL, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, mRenderData.vertexNum);

    }
    addX += 0.01;
//    if (addX > 1) {
//        addX = 0;
//    }
    
    addy += 0.1;
    if (addy > 1) {
        addy = 0;
    }
    
    rotation +=2;
    rotation = rotation % 360;
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

