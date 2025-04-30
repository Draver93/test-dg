//
// Created by Finoshkin Aleksei on 4/29/2025.
//

#include "Material.h"
#include "../system/ResourceDirector.h"
#include <glm/gtc/type_ptr.hpp>

static const char *default_vertex = R"vertex(#version 300 es
layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;

out vec2 fragUV;
out vec3 fragPos;
out vec3 fragNormal;
out vec3 cameraPos;

uniform mat4 uProjection;
uniform mat4 uModelMatrix;
uniform mat4 uView;

vec3 getCameraPosition() {
    mat4 invView = inverse(uView);
    return vec3(invView[3]); // Extract translation column
}

void main() {
    fragUV = in_texcoord;
    fragPos = vec3(uModelMatrix * vec4(in_vertex, 1.0));
    mat3 normalMatrix = mat3(transpose(inverse(uModelMatrix)));
    fragNormal = normalMatrix * in_normal;
    cameraPos = getCameraPosition();

	gl_Position = uProjection * uView * uModelMatrix * vec4(in_vertex, 1);
}
)vertex";

static const char *default_fragment = R"fragment(#version 300 es
precision mediump float;

in vec2 fragUV;
in vec3 fragPos;
in vec3 fragNormal;
in vec3 cameraPos;

#define MAX_LIGHTS 8

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

uniform Light uLights[MAX_LIGHTS];
uniform int uLightCount;

uniform sampler2D uTexture;

out vec4 outColor;

void main() {
    outColor = vec4(1.0);

    vec3 finalColor = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(cameraPos - fragPos);

    for (int i = 0; i < uLightCount; ++i) {
        vec3 lightDir = normalize(uLights[i].position - fragPos);
        float diff = max(dot(normal, lightDir), 0.0);

        // Optionally: add specular lighting
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

        vec3 diffuse = diff * uLights[i].color * uLights[i].intensity;
        vec3 specular = spec * uLights[i].color * 0.5; // Adjust strength
        finalColor += diffuse + specular;
    }

    if(uLightCount != 0) outColor = vec4(finalColor, 1);
}
)fragment";


namespace DGEngine {
    Material::Material() {
        m_program = glCreateProgram();

        AttachShader(ResourceDirector::CreateShader(GL_VERTEX_SHADER, default_vertex));
        AttachShader(ResourceDirector::CreateShader(GL_FRAGMENT_SHADER, default_fragment));

        LinkMaterial();
    };


    void Material::AttachShader(const std::shared_ptr<Shader> shader) {
        m_shaders[shader->m_shaderType] = shader;
        glAttachShader(m_program, shader->m_pShader );
    }

    GLuint Material::Get() const {
        return m_program;
    }

    GLint Material::GetUniformLocation(const std::string& name) {
        if(m_uniforms[name] == 0) DefineUniform(name.c_str());
        return m_uniforms[name];
    }

    GLint Material::GetAttributeLocation(const std::string& name) {
        if(m_attributes[name] == 0) m_attributes[name] = glGetAttribLocation(m_program, name.c_str());
        return m_attributes[name];
    }

    void Material::DefineUniform(const char *name) {
        m_uniforms[name] = glGetUniformLocation(m_program, name);
    }

    void Material::SetUniform(const std::string& name, float value) {
        if(m_uniforms[name] == 0) DefineUniform(name.c_str());
        glUniform1f(m_uniforms[name], value);
    }

    void Material::SetUniform(const std::string& name, int value) {
        if(m_uniforms[name] == 0) DefineUniform(name.c_str());
        glUniform1i(m_uniforms[name], value);
    }

    void Material::SetUniform(const std::string& name, const float* matrix) {
        if(m_uniforms[name] == 0) DefineUniform(name.c_str());
        glUniformMatrix4fv(m_uniforms[name] , 1, GL_FALSE, matrix);
    }

    void Material::SetUniform(const std::string& name, const glm::vec3& value) {
        if (m_uniforms[name] == 0) DefineUniform(name.c_str());
        glUniform3fv(m_uniforms[name], 1, glm::value_ptr(value));
    }

    void Material::SetUniform(const std::string& name, const glm::vec4& value) {
        if (m_uniforms[name] == 0) DefineUniform(name.c_str());
        glUniform4fv(m_uniforms[name], 1, glm::value_ptr(value));
    }

}