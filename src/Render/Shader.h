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
static std::string lightVertexShader =
"#version 300 es \n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoords;\n"

"out VS_OUT {\n"
"    vec3 FragPos;\n"
"    vec3 Normal;\n"
"    vec2 TexCoords;\n"
"} vs_out;\n"

"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"

"uniform bool inverse_normals;\n"

"void main()\n"
"{\n"
"    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));\n"
"    vs_out.TexCoords = aTexCoords;\n"
    
"    vec3 n = inverse_normals ? -aNormal : aNormal;\n"
    
"    mat3 normalMatrix = transpose(inverse(mat3(model)));\n"
"    vs_out.Normal = normalize(normalMatrix * n);\n"
    
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\n";

static std::string lightFragShader =
"#version 300 es\n"
"precision mediump float; \n"
"out vec4 FragColor;\n"

"in VS_OUT {\n"
"    vec3 FragPos;\n"
"    vec3 Normal;\n"
"    vec2 TexCoords;\n"
"} fs_in;\n"

"struct Light {\n"
"    vec3 Position;\n"
"    vec3 Color;\n"
"};\n"

"uniform Light lights[16];\n"
"uniform sampler2D diffuseTexture;\n"
"uniform vec3 viewPos;\n"

"void main()\n"
"{\n"
"    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;\n"
"    vec3 normal = normalize(fs_in.Normal);\n"
    // ambient
"    vec3 ambient = 1.0 * color;\n"
    // lighting
"    vec3 lighting = vec3(0.0);\n"
"    for(int i = 0; i < 16; i++)\n"
"    {\n"
        // diffuse
"        vec3 lightDir = normalize(lights[i].Position - fs_in.FragPos);\n"
"        float diff = max(dot(lightDir, normal), 0.0);\n"
"        vec3 diffuse = lights[i].Color * diff * color;\n"
"        vec3 result = diffuse;\n"
        // attenuation (use quadratic as we have gamma correction)
"        float distance = length(fs_in.FragPos - lights[i].Position);\n"
"        result *= 1.0 / (distance * distance);\n"
"        lighting += result;\n"
        
"    }\n"
"    FragColor = vec4(ambient + lighting, 1.0);\n"
//"    FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"

"}\n";


static std::string vertexShader =
"#version 300 es \n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec2 texCoords;\n"

"out vec2 TexCoords ;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 1.0f);\n"
"    TexCoords = texCoords;\n"
"}\n";

static std::string fragShader =
"#version 300 es\n"
"precision mediump float; \n"
"out vec4 FragColor;\n"
"in vec2 TexCoords;\n"

"uniform sampler2D hdrBuffer;\n"
"uniform float exposure;\n"

"uniform bool hdr;\n"

"void main()\n"
"{\n"
"   const float gamma = 2.2;\n"
"   vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;\n"
//"   vec3 hdrColor = vec3(1.0, 0.0, 0.0);\n"

"   if(hdr)\n"
"   {\n"
"       vec3 result = vec3(1.0) - exp(-hdrColor * exposure);\n"
    // also gamma correct while we're at it
"       result = pow(result, vec3(1.0 / gamma));\n"
"       FragColor = vec4(result, 1.0);\n"
"   }\n"
"   else\n"
"   {\n"
"       vec3 result = pow(hdrColor, vec3(1.0 / gamma));\n"
"       FragColor = vec4(result, 1.0);\n"
"   }\n"
"}\n";

#endif /* Shader_h */
