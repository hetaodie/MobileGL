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

GLuint quadVBO;

void RenderQuad()
{
    // positions
    glm::vec3 pos1(-1.0, 1.0, 0.0);
    glm::vec3 pos2(-1.0, -1.0, 0.0);
    glm::vec3 pos3(1.0, -1.0, 0.0);
    glm::vec3 pos4(1.0, 1.0, 0.0);
    // texture coordinates
    glm::vec2 uv1(0.0, 1.0);
    glm::vec2 uv2(0.0, 0.0);
    glm::vec2 uv3(1.0, 0.0);
    glm::vec2 uv4(1.0, 1.0);
    // normal vector
    glm::vec3 nm(0.0, 0.0, 1.0);
    
    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // - triangle 1
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;
    
    GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    
    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);
    
    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);
    
    // - triangle 2
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;
    
    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    
    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);
    
    
    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);
    
    
    GLfloat quadVertices[] = {
        // Positions            // normal         // TexCoords  // Tangent                          // Bitangent
        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        
        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };
    // Setup plane VAO
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
    
    mCamera = new Camera(glm::vec3(0.0, 0.0, 3.0));
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

    if (mShaderProgram == nullptr) {
        mShaderProgram = new ShaderProgram(vertexShader.c_str(), fragShader.c_str());
    }
    
    
    mShaderProgram->useProgram();
    
    glUniform1i(glGetUniformLocation(mShaderProgram->mProgram, "diffuseMap"), 0);
    glUniform1i(glGetUniformLocation(mShaderProgram->mProgram, "normalMap"), 1);
    glm::vec3 lightPos(0.5f, 1.0f, 0.3f);

    
    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 view;
    glm::mat4 projection;
    GLuint diffuseMap = mTextureMap.at("brickwall");
    GLuint normalMap = mTextureMap.at("brickwall_normal");

    
    view = mCamera->GetViewMatrix();
    projection = glm::perspective(mCamera->Zoom, (float)mWidth / (float)mHeight, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram->mProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram->mProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // Render normal-mapped quad
    model = glm::rotate(model, (GLfloat)rotate, glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // Rotates the quad to show normal mapping works in all directions
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram->mProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(mShaderProgram->mProgram, "lightPos"), 1, &lightPos[0]);
    glUniform3fv(glGetUniformLocation(mShaderProgram->mProgram, "viewPos"), 1, &mCamera->Position[0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap);
    RenderQuad();
    
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


