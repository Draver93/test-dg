//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#ifndef TESTDG_SHADER_H
#define TESTDG_SHADER_H

#include "Resource.h"

namespace DGEngine {
    class ResourceDirector;
    class Material;

    class Shader : public Resource {
    private:
        friend ResourceDirector;
        friend Material;

        Shader(GLenum shaderType, const std::string &shaderSource);
    public:
        bool Reload(const std::string &shaderSource);
    private:
        bool Load(const std::string &shaderSource);

        GLenum m_shaderType;
        GLuint m_pShader;
    };





}


#endif //TESTDG_SHADER_H
