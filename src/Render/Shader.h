//
//  Shader.h
//  RenderEngineKit
//
//  Created by weixu on 2019/5/16.
//  Copyright © 2019 weixu. All rights reserved.
//

#ifndef Shader_h
#define Shader_h
#include <string>

static std::string vertexShader =
"#version 300 es \n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 normal;\n"
"layout (location = 2) in vec2 texCoords;\n"
"layout (location = 3) in vec3 tangent;\n"
"layout (location = 4) in vec3 bitangent;\n"

"out VS_OUT {\n"
"    vec3 FragPos;\n"
"    vec2 TexCoords;\n"
"    vec3 TangentLightPos;\n"
"    vec3 TangentViewPos;\n"
"    vec3 TangentFragPos;\n"
"} vs_out;\n"

"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"

"uniform vec3 lightPos;\n"
"uniform vec3 viewPos;\n"

"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(position, 1.0f);\n"
"    vs_out.FragPos = vec3(model * vec4(position, 1.0));\n"
"    vs_out.TexCoords = texCoords;\n"
    
"    mat3 normalMatrix = transpose(inverse(mat3(model)));\n"
"    vec3 T = normalize(normalMatrix * tangent);\n"
"    vec3 B = normalize(normalMatrix * bitangent);\n"
"    vec3 N = normalize(normalMatrix * normal);\n"
    
"    mat3 TBN = transpose(mat3(T, B, N));\n"
"    vs_out.TangentLightPos = TBN * lightPos;\n"
"    vs_out.TangentViewPos  = TBN * viewPos;\n"
"    vs_out.TangentFragPos  = TBN * vs_out.FragPos;\n"
"}\n";

static std::string fragShader =
"#version 300 es\n"
"precision mediump float; \n"
"out vec4 FragColor;\n"

"in VS_OUT {\n"
"    vec3 FragPos;\n"
"   vec2 TexCoords;\n"
"    vec3 TangentLightPos;\n"
"    vec3 TangentViewPos;\n"
"    vec3 TangentFragPos;\n"
"} fs_in;\n"

"uniform sampler2D diffuseMap;\n"
"uniform sampler2D normalMap;\n"

"uniform bool normalMapping;\n"

"void main()\n"
"{\n"
    // Obtain normal from normal map in range [0,1]
"    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;\n"
    // Transform normal vector to range [-1,1]
"    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space\n"
    
    // Get diffuse color
"    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;\n"
    // Ambient
"    vec3 ambient = 0.1 * color;\n"
    // Diffuse
"    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);\n"
"    float diff = max(dot(lightDir, normal), 0.0);\n"
"    vec3 diffuse = diff * color;\n"
    // Specular
"    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);\n"
"    vec3 reflectDir = reflect(-lightDir, normal);\n"
"    vec3 halfwayDir = normalize(lightDir + viewDir);\n"
"    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);\n"
"    vec3 specular = vec3(0.2) * spec;\n"
    
"   FragColor = vec4(ambient + diffuse + specular, 1.0f);\n"
"}\n";

#endif /* Shader_h */
