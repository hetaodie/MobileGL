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

//GLfloat quadVertices[] = {
//    //  ---位置---   ------颜色-------
//    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//    0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
//
//    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//    0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//    0.05f,  0.05f,  0.0f, 1.0f, 1.0f
//};

// Options
GLboolean hdr = true; // Change with 'Space'
GLfloat exposure = 1.0f; // Change with Q and E

// RenderCube() Renders a 1x1 3D cube in NDC.
GLuint cubeVAO = 0;
GLuint cubeVBO = 0;
void RenderCube()
{
    // Initialize (if necessary)
    if (cubeVAO == 0)
    {
        GLfloat vertices[] = {
            // Back face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
            // Front face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
            // Left face
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            // Right face
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            // Top face
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left
        };
        glGenBuffers(1, &cubeVBO);
        // Fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // Link vertex attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    }
    // Render Cube
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDeleteBuffers(1, &cubeVBO);
}

GLuint quadVAO = 0;
GLuint quadVBO;
void RenderQuad()
{
    if (quadVAO == 0)
    {
        GLfloat quadVertices[] = {
            // Positions        // Texture Coords
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // Setup plane VAO
        glGenBuffers(1, &quadVBO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    }
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDeleteBuffers(1, &quadVBO);
}


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
    
    mCamera = new Camera(glm::vec3(0.0, 0.0, 10.0));
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
}


void Renderer::render(){
    static float rotate = 0.0;
    glClearColor(0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
    GLuint colorBuffer;
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (mLightShaderProgram == nullptr) {
        mLightShaderProgram = new ShaderProgram(lightVertexShader.c_str(), lightFragShader.c_str());
    }
    
    if (mShaderProgram == nullptr) {
        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragShader.c_str());
    }
    
    
    mLightShaderProgram->useProgram();
    
    std::vector<glm::vec3> lightPositions;
    lightPositions.push_back(glm::vec3(0.0f, 0.0f, 49.5f)); // back light
    lightPositions.push_back(glm::vec3(-1.4f, -1.9f, 9.0f));
    lightPositions.push_back(glm::vec3(0.0f, -1.8f, 4.0f));
    lightPositions.push_back(glm::vec3(0.8f, -1.7f, 6.0f));
    // - Colors
    std::vector<glm::vec3> lightColors;
    lightColors.push_back(glm::vec3(200.0f, 200.0f, 200.0f));
    lightColors.push_back(glm::vec3(0.1f, 0.0f, 0.0f));
    lightColors.push_back(glm::vec3(0.0f, 0.0f, 0.2f));
    lightColors.push_back(glm::vec3(0.0f, 0.1f, 0.0f));
//    lightColors.push_back(glm::vec3(1.f, 0.0f, 0.0f));
//    lightColors.push_back(glm::vec3(0.0f, 1.f, 0.0f));
//    lightColors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    glm::vec3 lightPos(0.5f, 1.0f, 0.3f);

    
    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 view;
    glm::mat4 projection;
    
    GLuint woodTexture = mTextureMap.at("wood");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    glUniform1i(glGetUniformLocation(mLightShaderProgram->mProgram, "diffuseTexture"), 0);
    
    view = mCamera->GetViewMatrix();
    projection = glm::perspective(mCamera->Zoom, (float)mWidth / (float)mHeight, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(mLightShaderProgram->mProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(mLightShaderProgram->mProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    for (GLuint i = 0; i < lightPositions.size(); i++)
    {
        glUniform3fv(glGetUniformLocation(mLightShaderProgram->mProgram, ("lights[" + std::to_string(i) + "].Position").c_str()), 1, &lightPositions[i][0]);
        glUniform3fv(glGetUniformLocation(mLightShaderProgram->mProgram, ("lights[" + std::to_string(i) + "].Color").c_str()), 1, &lightColors[i][0]);
    }
    glUniform3fv(glGetUniformLocation(mLightShaderProgram->mProgram, "viewPos"), 1, &mCamera->Position[0]);
    // - render tunnel
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 30));
//    model = glm::rotate(model, -rotate, glm::vec3(1.0, 1.0, 0.0));

    model = glm::scale(model, glm::vec3(5.0f, 5.0f, 60.0f));
    glUniformMatrix4fv(glGetUniformLocation(mLightShaderProgram->mProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(glGetUniformLocation(mLightShaderProgram->mProgram, "inverse_normals"), GL_FALSE);
    RenderCube();
//
//    mShaderProgram->useProgram();
//    glActiveTexture(GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, colorBuffer);
////    glUniform1i(glGetUniformLocation(mLightShaderProgram->mProgram, "hdrBuffer"), 0);
//    glUniform1i(glGetUniformLocation(mShaderProgram->mProgram, "hdr"), hdr);
//    glUniform1f(glGetUniformLocation(mShaderProgram->mProgram, "exposure"), exposure);
//    RenderQuad();
    
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glDeleteBuffers(1, &colorBuffer);
//    model = glm::mat4();
//    model = glm::translate(model, lightPos);
//    model = glm::scale(model, glm::vec3(0.1f));
//    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram->mProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    RenderQuad();
    rotate += 1.0;
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
    GLuint texture = createTexture2D(GL_RGBA, width, height, data);
    mTextureVector.push_back(texture);
    mTextureMap.insert(std::pair<std::string, GLint>(name, texture));

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


