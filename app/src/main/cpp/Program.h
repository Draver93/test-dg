#ifndef ANDROIDGLINVESTIGATIONS_SHADER_H
#define ANDROIDGLINVESTIGATIONS_SHADER_H

#include <string>
#include <map>
#include <GLES3/gl3.h>
#include "Shader.h"


class Model;

/*!
 * A class representing a simple shader program. It consists of vertex and fragment components. The
 * input attributes are a position (as a Vector3) and a uv (as a Vector2). It also takes a uniform
 * to be used as the entire model/view/projection matrix. The shader expects a single texture for
 * fragment shading, and does no other lighting calculations (thus no m_uniforms for lights or normal
 * attributes).
 */
class Program {
public:
    inline ~Program() {
        if (m_instance) {
            glDeleteProgram(m_instance);
            m_instance = 0;
        }
    }

    /*!
     * Prepares the shader for get, call this before executing any draw commands
     */
    GLuint get() const;

    /*!
     * Cleans up the shader after get, call this after executing any draw commands
     */
    void deactivate() const;

    /*!
     * Renders a single model
     * @param model a model to render
     */
    void drawModel(const Model &model);


    Program();
    void attachShader(const std::shared_ptr<Shader> shader);

    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const float* matrix);
    GLint getUniformLocation(const std::string& name);
    GLint getAttributeLocation(const std::string& name);

private:

    GLuint m_instance;
    std::unordered_map<GLenum, std::shared_ptr<Shader>> m_shaders;
    std::unordered_map<std::string, GLint> m_uniforms;
    std::unordered_map<std::string, GLint> m_attributes;

    void defineUniform(const char* name);
};

#endif //ANDROIDGLINVESTIGATIONS_SHADER_H

