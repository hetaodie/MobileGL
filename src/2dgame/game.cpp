//
//  game.cpp
//  RenderEngineKit
//
//  Created by weixu on 2019/6/5.
//  Copyright © 2019 weixu. All rights reserved.
//

#include "game.hpp"

#include "Resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "Texture2D.hpp"

// Game-related State data
SpriteRenderer  *Renderer;


Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
    
}

Game::~Game()
{
    delete Renderer;
}

void Game::Init(std::string vertexCode, std::string fragmentCode)
{
    // Load shaders
    ResourceManager::LoadShader(vertexCode, fragmentCode, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures

    // Set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
}

void Game::loadImage(unsigned char *image ,int width, int height, bool alpba) {
    ResourceManager::LoadTexture(image, width, height, alpba, "face");
}

void Game::Update(GLfloat dt)
{
    
}


void Game::ProcessInput(GLfloat dt)
{
    
}

void Game::Render(int width, int height)
{
    Texture2D texture2D =  ResourceManager::GetTexture("face");
    Renderer->DrawSprite(texture2D, glm::vec2(width/4, height/4), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
