//
// Created by drave on 4/29/2025.
//

#include "Material.h"
#include "ResourceDirector.h"

static const char *default_vertex = R"vertex(#version 300 es
layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;

out vec2 fragUV;

uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    fragUV = in_texcoord;
	gl_Position = uProjection * uView  * vec4(in_vertex, 1);

    //gl_Position = uProjection * uView * vec4(inPosition, 1.0);
}
)vertex";

static const char *default_fragment = R"fragment(#version 300 es
precision mediump float;

in vec2 fragUV;

uniform sampler2D uTexture;

out vec4 outColor;

void main() {
    outColor = vec4(1);//texture(uTexture, fragUV);
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
}