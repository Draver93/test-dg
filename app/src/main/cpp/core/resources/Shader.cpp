//
// Created by drave on 4/27/2025.
//

#include "Shader.h"
#include "../../Utility.h"

namespace DGEngine {
    Shader::Shader(GLenum shaderType, const std::string &shaderSource) : m_shaderType(shaderType), m_pShader(0) {
        if(!Load(shaderSource)) {
            //aout << "Failed to load shader:\n" << shaderSource << std::endl;
        }
    }

    bool Shader::Reload(const std::string &shaderSource) {
        return Load(shaderSource);
    }

    bool Shader::Load(const std::string &shaderSource) {
        Utility::assertGlError();
        if(m_pShader) glDeleteShader(m_pShader);

        m_pShader = glCreateShader(m_shaderType);
        if (!m_pShader) return false;

        auto *shaderRawString = (GLchar *) shaderSource.c_str();
        GLint shaderLength = shaderSource.length();
        glShaderSource(m_pShader, 1, &shaderRawString, &shaderLength);
        glCompileShader(m_pShader);

        GLint shaderCompiled = 0;
        glGetShaderiv(m_pShader, GL_COMPILE_STATUS, &shaderCompiled);

        // If the shader doesn't compile, log the result to the terminal for debugging
        if (!shaderCompiled) {
            GLint infoLength = 0;
            glGetShaderiv(m_pShader, GL_INFO_LOG_LENGTH, &infoLength);

            if (infoLength) {
                auto *infoLog = new GLchar[infoLength];
                glGetShaderInfoLog(m_pShader, infoLength, nullptr, infoLog);
                //aout << "Failed to compile with:\n" << infoLog << std::endl;
                delete[] infoLog;
            }

            glDeleteShader(m_pShader);
            m_pShader = 0;
            return false;
        }

        return true;
    }
}