//
//  Camera.hpp
//  RenderEngineKit
//
//  Created by weixu on 2019/5/22.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

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
#include <stdio.h>

namespace renderer {
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    
    // Default camera values
    const GLfloat YAW        = -90.0f;
    const GLfloat PITCH      =  0.0f;
    const GLfloat SPEED      =  3.0f;
    const GLfloat SENSITIVTY =  0.25f;
    const GLfloat ZOOM       =  45.0f;

    
    class Camera {
    public:
        // Camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // Eular Angles
        GLfloat Yaw;
        GLfloat Pitch;
        // Camera options
        GLfloat MovementSpeed;
        GLfloat MouseSensitivity;
        GLfloat Zoom;
        
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
       
        // Constructor with scalar values
        Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
        glm::mat4 GetViewMatrix();
        void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
        void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
        void ProcessMouseScroll(GLfloat yoffset);
    private:
        void updateCameraVectors();
        
    public:
        GLint textureId;
        
    };
};
#endif /* Camera_hpp */
