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
"in vec2 position;\n"
"in vec3 color;\n"
"out vec3 fColor;\n"
"uniform vec2 offsets[100];\n"
"void main() {\n"
"   vec2 offset = offsets[gl_InstanceID];\n"
"   gl_Position = vec4(position + offset, 0.0, 1.0);\n"
"   fColor = color;\n"
"}\n";
static std::string fragShader =
"#version 300 es\n"
"precision mediump float;\n"
"in vec3 fColor;\n"
"out vec4 FragColor;\n"
"void main(){\n"
"   FragColor = vec4(fColor, 1.0);\n"
"\n"
"}\n";

//static std::string cubevertexShader =
//"attribute vec3 aPos; \n"
//"attribute vec3 aNormal; \n"
//
//"attribute vec2 aTexCoords; \n"
//"varying vec2 TexCoords; \n"
//"varying vec3 Position; \n"
//"varying vec3 Normal; \n"
//
//"uniform mat3 normalMat; \n"
//
//"uniform mat4 model; \n"
//"uniform mat4 view; \n"
//"uniform mat4 projection; \n"
//
//"void main() \n"
//"{ \n"
//"    Position = vec3(model * vec4(aPos, 1.0));\n"
//
//"    Normal = normalMat * aNormal;\n"
//"    gl_Position = projection * view *  model * vec4(aPos, 1.0); \n"
//"    TexCoords = aTexCoords; \n"
//"} \n";
//
//static std::string cubefragmentShader =
//"precision mediump float; \n"
//"varying vec2 TexCoords;\n"
//"varying vec3 Normal; \n"
//"varying vec3 Position; \n"
//"uniform float width;\n"
//"uniform float height;\n"
//
//"uniform float mixRote;\n"
//"uniform vec3 cameraPos;\n"
//"uniform samplerCube skybox;\n"
//"uniform sampler2D texture1;\n"
//"void main() \n"
//"{ \n"
//"   float halfW = width/4.0; \n"
//"   float halfH = height/2.0; \n"
//
//"   vec3 I = normalize(Position - cameraPos);\n"
//"   vec3 R = reflect(I, normalize(Normal));\n"
//"   vec4 rfragColor = vec4(textureCube(skybox, R).rgb, 1.0); \n"
//"   vec2 TexCoord = vec2(TexCoords.x, 1.0 - TexCoords.y); \n"
//"   vec4 fragColor = texture2D(texture1, TexCoords); \n"
//"   vec4 frag = mix(rfragColor, fragColor, mixRote);\n"
//"   if(gl_FragCoord.y < halfH) { \n"
//"       frag = fragColor;\n"
//"   } \n"
//"   gl_FragColor = frag; \n"
////"   gl_FragColor = rfragColor; \n"
//
//"}\n";
//
//static std::string skyboxVertexShader =
//"attribute vec3 aPos;\n"
//"varying vec3 TexCoords;\n"
//
//"uniform mat4 projection;\n"
//"uniform mat4 view;\n"
//
//"void main()\n"
//"{\n"
//"    TexCoords = aPos;\n"
//"    vec4 pos = projection * view * vec4(aPos, 1.0);\n"
//"    gl_Position = pos.xyww;\n"
////"    gl_Position = pos;\n"
//"}\n";
//
//static std::string skyboxFragmentShader =
//"precision mediump float; \n"
//"varying vec3 TexCoords;\n"
//"uniform samplerCube skybox;\n"
//"void main() \n"
//"{ \n"
//"   vec3 sampleVector = normalize(vec4(TexCoords, 1.0)).xyz; \n"
//
//"   vec4 fragColor = textureCube(skybox, sampleVector); \n"
//"   gl_FragColor = fragColor; \n"
////"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
//"}\n";
//
//static std::string screenVertexShader =
//"attribute vec2 aPos; \n"
//"attribute vec2 aTexCoords; \n"
//"varying vec2 TexCoords; \n"
//
//"uniform mat4 model; \n"
//"uniform mat4 view; \n"
//"uniform mat4 projection; \n"
//
//"void main() \n"
//"{ \n"
//"    gl_Position = vec4(aPos.x,aPos.y,0.0, 1.0); \n"
//"    TexCoords = aTexCoords; \n"
//"} \n";
//
//static std::string screenFragmentShader =
//"precision mediump float; \n"
//"varying vec2 TexCoords;\n"
//"uniform sampler2D texture1;\n"
//"void main() \n"
//"{ \n"
//"   vec2 TexCoord = vec2(TexCoords.x, 1.0 - TexCoords.y); \n"
//"   vec3 fragColor= texture2D(texture1, TexCoord).rgb; \n"
//"   gl_FragColor = vec4(fragColor, 1.0); \n"
//"}\n";
//
//
//static std::string vertexShader =
//"attribute vec3 position; \n"
//"attribute vec3 normal; \n"
//"attribute vec2 texCoords; \n"
//
//"varying vec3 Normal; \n"
//"varying vec3 FragPos; \n"
//"varying vec2 TexCoords; \n"
//
//"uniform mat4 model; \n"
//"uniform mat4 view; \n"
//"uniform mat4 projection; \n"
//"uniform mat3 normalMatrix; \n"
//
//"void main() \n"
//"{ \n"
//"    gl_Position = projection * view *  model * vec4(position, 1.0); \n"
//"    FragPos = vec3(model * vec4(position, 1.0)); \n"
//"    Normal = normalMatrix * normal; \n"
//"    TexCoords = texCoords; \n"
//"} \n";
//
//static std::string fragmentShader =
//"precision mediump float; \n"
//"struct Material {\n"
//"    sampler2D diffuse;  \n"
//"    sampler2D specular;  \n"
//"    float shininess;  \n"
//"};  \n"
//
//"struct DirLight {\n"
//"    vec3 direction;  \n"
//
//"    vec3 ambient;  \n"
//"    vec3 diffuse;  \n"
//"    vec3 specular;  \n"
//"};  \n"
//
//"struct PointLight {\n"
//"    vec3 position;  \n"
//
//"    float constant;  \n"
//"    float linear;  \n"
//"    float quadratic;  \n"
//
//"    vec3 ambient;  \n"
//"    vec3 diffuse;  \n"
//"    vec3 specular;  \n"
//"};  \n"
//
////"#define NR_POINT_LIGHTS 4 \n"
//
//"varying vec3 FragPos;  \n"
//"varying vec3 Normal;  \n"
//"varying vec2 TexCoords;  \n"
//
//"uniform vec3 viewPos;  \n"
//"uniform DirLight dirLight;  \n"
//"uniform PointLight pointLights[4];  \n"
//"uniform Material material;  \n"
//
//// Function prototypes
//"vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  \n"
//"vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  \n"
//
//"void main() \n"
//"{ \n"
//"    vec3 norm = normalize(Normal);  \n"
//"    vec3 viewDir = normalize(viewPos - FragPos);  \n"
//"    vec3 result = CalcDirLight(dirLight, norm, viewDir);  \n"
//"    for(int i = 0; i < 4; i++) \n"
//"        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);  \n"
//"    gl_FragColor = vec4(result, 1.0);  \n"
//"} \n"
//
//// Calculates the color when using a directional light.
//"vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) \n"
//"{ \n"
//"    vec3 lightDir = normalize(-light.direction);  \n"
//
//"    float diff = max(dot(normal, lightDir), 0.0);  \n"
//"    vec3 reflectDir = reflect(-lightDir, normal);  \n"
//"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  \n"
//// Combine results
//"    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));  \n"
//"    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));  \n"
//"    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));  \n"
//"    return (ambient + diffuse + specular);  \n"
//"} \n"
//
//// Calculates the color when using a point light.
//"vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) \n"
//"{ \n"
//"    vec3 lightDir = normalize(light.position - fragPos);  \n"
//// Diffuse shading
//"    float diff = max(dot(normal, lightDir), 0.0);  \n"
//// Specular shading
//"    vec3 reflectDir = reflect(-lightDir, normal);  \n"
//"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  \n"
//// Attenuation
//"    float distance = length(light.position - fragPos);  \n"
//"    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  \n"
//// Combine results
//"    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));  \n"
//"    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));  \n"
//"    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));  \n"
//"    ambient *= attenuation;  \n"
//"    diffuse *= attenuation;  \n"
//"    specular *= attenuation;  \n"
//"    return (ambient + diffuse + specular);  \n"
//"}\n";
//
//static std::string lightVertexShader =
//"attribute vec3 aPos;\n"
//
//"uniform mat4 model;\n"
//"uniform mat4 view;\n"
//"uniform mat4 projection;\n"
//"void main() \n"
//"{ \n"
//"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
//"} \n";
//
//static std::string lightFragmentShader =
//"void main()\n"
//"{\n"
//"    gl_FragColor = vec4(1.0); // set alle 4 vector values to 1.0\n"
//"}\n";


//static std::string vertexShader =
//"attribute vec3 position;\n"
//"attribute vec3 vertexColor;\n"
//"attribute vec2 coord;\n"
//"uniform mat4 model; \n"
//"uniform mat4 view; \n"
//"uniform mat4 projection; \n"
//"uniform float move1;\n"
//"varying vec4 color;\n"
//"varying vec2 texCoord;\n"
//"varying vec2 texCoord2;\n"
//"void main()\n"
//"{\n"
//"   color = vec4(vertexColor,1.0);\n"
//"   float y = coord.y - move1;\n"
//"   vec2 testCoord= vec2(coord.x, y); \n"
//"   texCoord2 = testCoord;\n"
//"   texCoord = coord;"
//"   mat4 transform = projection * view * model; \n"
//"   gl_Position = transform * vec4(position, 1.0);\n"
//"}\n";

//static std::string fragmentShader =
//"precision mediump float; \n"
//"precision mediump int; \n"
//"varying vec4 color;\n"
//"varying vec2 texCoord;\n"
//"varying vec2 texCoord2;\n"
//"uniform sampler2D ourTexture0;\n"
//"uniform sampler2D ourTexture1;\n"
//"uniform int isHidden;\n"
//"uniform float changeAlpha;\n"
//"void main() \n"
//"{ \n"
//"   vec2 TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n"
//"   vec2 TexCoord2 = vec2(texCoord2.x, 1.0 - texCoord2.y); \n"
//"   vec4 texture0= texture2D(ourTexture0, TexCoord); \n"
//"   vec4 texture1= texture2D(ourTexture1, TexCoord2); \n"
//"   vec4 fragColor = mix(texture0, texture1, texture1.w);\n"
//"   gl_FragColor = fragColor; \n"
//"}\n";

//static std::string fragmentShader =
//"precision mediump float; \n"
//"struct Material { \n"
//"   sampler2D diffuse; \n"
//"   sampler2D specular; \n"
//"   float shininess; \n"
//"};\n"
//"uniform Material material;\n"
//"struct Light\n"
//"{\n"
//"    vec3 position;\n"
//"    vec3 ambient;\n"
//"    vec3 diffuse;\n"
//"    vec3 specular;\n"
//"    float constant;\n"
//"    float linear;\n"
//"    float quadratic;\n"
//"};\n"
//"uniform Light light;\n"
//"uniform vec3 objectColor; \n"
//"uniform vec3 lightColor; \n"
//"uniform vec3 lightPos; \n"
//"varying vec3 fnormal;\n"
//"varying vec3 FragPos;\n"
//"uniform vec3 viewPos;\n"
//"varying vec2 texCoord;\n"
//"void main() \n"
//"{ \n"
//"   vec3 ambient = light.ambient * lightColor * vec3(texture2D(material.diffuse, texCoord)); \n"
//
//"   vec3 norm = normalize(fnormal);\n"
//"   vec3 lightDir = normalize(lightPos - FragPos); \n"
//"   float distance=length(lightPos - FragPos); \n"
//"   float attenuation = 1.0 / (light.constant + light.linear*distance +light.quadratic*(distance*distance));\n"
//"   float diff = max(dot(norm, lightDir), 0.0); \n"
//"   vec3 diffuse = light.diffuse * (diff * vec3(texture2D(material.diffuse, texCoord)))  * attenuation * lightColor; \n"
//
//"   vec3 viewDir = normalize(viewPos - FragPos);\n"
//"   vec3 reflectDir = reflect(-lightDir, norm);\n"
//"   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
//"   vec3 specular = light.specular * vec3(texture2D(material.specular, texCoord))  * attenuation * spec * lightColor;\n"
//"   vec3 result = (ambient + diffuse + specular); \n"
//"   gl_FragColor = vec4(result, 1.0); \n"
//"}\n";


//static std::string lightVertexShader =
//"attribute vec3 position;\n"
//"attribute vec3 normal;\n"
//"uniform mat4 model; \n"
//"uniform mat4 view; \n"
//"uniform mat4 projection; \n"
//"varying vec3 fnormal;\n"
//"varying vec3 FragPos;\n"
//"uniform mat3 normalMatrix;\n"
//"attribute vec2 coord;\n"
//"varying vec2 texCoord;\n"
//"void main() \n"
//"{ \n"
//"   mat4 transform = projection * view * model; \n"
//"   FragPos = vec3(model * vec4(position, 1.0));\n"
//"   gl_Position = transform * vec4(position, 1.0);\n"
//"   texCoord = coord; \n"
//"   fnormal= normalMatrix * normal; \n"
//"}\n";

//static std::string vertexShader =
//"precision mediump float; \n"
//"uniform vec3 lightColor; \n"
//"void main() \n"
//"{ \n"
//"   gl_FragColor = vec4(lightColor,1.0); \n"
////"      gl_FragColor = vec4(1.0,1.0,1.0,1.0);\n"
//"}\n";



#endif /* Shader_h */
