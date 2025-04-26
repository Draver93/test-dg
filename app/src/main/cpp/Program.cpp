#include "Program.h"

#include "AndroidOut.h"
#include "Model.h"
#include "Utility.h"

/*Program *Program::loadShader(
        const std::string &vertexSource,
        const std::string &fragmentSource) {
    Program *shader = nullptr;

    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader) {
        return nullptr;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        return nullptr;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint logLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

            // If we fail to link the shader program, log the result for debugging
            if (logLength) {
                GLchar *log = new GLchar[logLength];
                glGetProgramInfoLog(program, logLength, nullptr, log);
                aout << "Failed to link program with:\n" << log << std::endl;
                delete[] log;
            }

            glDeleteProgram(program);
        } else {
            // Get the attribute and uniform locations by name. You may also choose to hardcode
            // indices with layout= in your shader, but it is not done in this sample
            GLint positionAttribute = glGetAttribLocation(program, positionAttributeName.c_str());
            GLint uvAttribute = glGetAttribLocation(program, uvAttributeName.c_str());
            GLint projectionMatrixUniform = glGetUniformLocation(
                    program,
                    projectionMatrixUniformName.c_str());

            // Only create a new shader if all the attributes are found.
            if (positionAttribute != -1
                && uvAttribute != -1
                && projectionMatrixUniform != -1) {

                shader = new Program(
                        program,
                        positionAttribute,
                        uvAttribute,
                        projectionMatrixUniform);
            } else {
                glDeleteProgram(program);
            }
        }
    }

    // The shaders are no longer needed once the program is linked. Release their memory.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}*/

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

void Program::drawModel(const Model &model) {

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