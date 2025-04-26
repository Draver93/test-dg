#ifndef TESTDG_SHADER_H
#define TESTDG_SHADER_H

#include <string>
#include <map>
#include <GLES3/gl3.h>
#include "Shader.h"

class Program;

class Shader {
public:
    Shader(GLenum shaderType, const std::string &shaderSource);
    bool Reload(const std::string &shaderSource);

private:
    bool Load(const std::string &shaderSource);

    GLenum m_shaderType;
    GLuint m_pShader;

    friend Program;
};


#endif //TESTDG_SHADER_H
