//
//  sprite_renderer.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/6/5.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef sprite_renderer_hpp
#define sprite_renderer_hpp

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#elif __ANDROID__
#include <GLES3/gl2.h>
#include <GLES3/gl2ext.h>
#include <GLES3/gl2platform.h>
#include <EGL/egl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.hpp"
#include "Shader.hpp"


class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    Shader shader;
    GLuint quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};
#endif /* sprite_renderer_hpp */
