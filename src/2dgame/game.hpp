//
//  game.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/6/5.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <string>
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

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    // Game state
    GameState              State;
    GLboolean              Keys[1024];
    GLuint                 Width, Height;
    Game(){};
    // Constructor/Destructor
    Game(GLuint width, GLuint height);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void Init(std::string vertexCode, std::string fragmentCode);
    void loadImage(unsigned char *image ,int width, int height, bool alpba);
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render(int width, int height);
};


#endif /* game_hpp */
