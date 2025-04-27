#include "Program.h"

#include "AndroidOut.h"
#include "Model.h"
#include "Utility.h"

Program::Program() {
    m_instance = glCreateProgram();
    if (!m_instance) aout << "Failed to create program with:\n" << std::endl;
}

void Program::attachShader(const std::shared_ptr<Shader> shader) {
    m_shaders[shader->m_shaderType] = shader;
    glAttachShader(m_instance, shader->m_pShader );
}

GLuint Program::get() const {
    return m_instance;
}

GLint Program::getUniformLocation(const std::string& name) {
    if(m_uniforms[name] == 0) defineUniform(name.c_str());
    return m_uniforms[name];
}

GLint Program::getAttributeLocation(const std::string& name) {
    if(m_attributes[name] == 0) m_attributes[name] = glGetAttribLocation(m_instance, name.c_str());
    return m_attributes[name];
}

void Program::defineUniform(const char *name) {
    m_uniforms[name] = glGetUniformLocation(m_instance, name);
}

void Program::setUniform(const std::string& name, float value) {
    if(m_uniforms[name] == 0) defineUniform(name.c_str());
    glUniform1f(m_uniforms[name], value);
}

void Program::setUniform(const std::string& name, int value) {
    if(m_uniforms[name] == 0) defineUniform(name.c_str());
    glUniform1i(m_uniforms[name], value);
}

void Program::setUniform(const std::string& name, const float* matrix) {
    if(m_uniforms[name] == 0) defineUniform(name.c_str());
    glUniformMatrix4fv(m_uniforms[name] , 1, GL_FALSE, matrix);
}