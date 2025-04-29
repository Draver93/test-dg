//
// Created by drave on 4/29/2025.
//

#ifndef TESTDG_MATERIAL_H
#define TESTDG_MATERIAL_H

#include "Resource.h"
#include "Shader.h"
#include <GLES3/gl3.h>

#include <map>

namespace DGEngine {
    class ResourceDirector;

    class Material : public Resource {
    private:
        friend ResourceDirector;

        Material(); // default material
    public:
        void LinkMaterial() { glLinkProgram(m_program); };
        ~Material() {
            if (m_program) {
                glDeleteProgram(m_program);
                m_program = 0;
            }
        }

        GLuint Get() const;
        void AttachShader(const std::shared_ptr <Shader> shader);
        void SetUniform(const std::string &name, float value);
        void SetUniform(const std::string &name, int value);
        void SetUniform(const std::string &name, const float *matrix);
        GLint GetUniformLocation(const std::string &name);
        GLint GetAttributeLocation(const std::string &name);

    private:
        GLuint m_program;
        std::unordered_map <GLenum, std::shared_ptr<Shader>> m_shaders;
        std::unordered_map <std::string, GLint> m_uniforms;
        std::unordered_map <std::string, GLint> m_attributes;
        void DefineUniform(const char *name);
    };
}

#endif //TESTDG_MATERIAL_H
