//
//  Resource_manager.cpp
//  RenderEngineKit
//
//  Created by weixu on 2019/6/5.
//  Copyright © 2019 weixu. All rights reserved.
//

#include "Resource_manager.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;


Shader ResourceManager::LoadShader(std::string vertexCode, std::string fragmentCode, std::string name)
{
    Shaders[name] = loadShaderFromFile(vertexCode, fragmentCode);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(unsigned char* image,int width, int height, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(image,width, height, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(std::string vertexCode, std::string fragmentCode)
{
    Shader shader;
    shader.Compile(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(unsigned char* image,int width, int height, GLboolean alpha)
{
    Texture2D texture;
    texture.Internal_Format = GL_RGBA;
    texture.Image_Format = GL_RGBA;
    // Now generate texture
    texture.Generate(width, height, image);
    // And finally free image data
    return texture;
}
