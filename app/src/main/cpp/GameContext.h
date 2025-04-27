#ifndef ANDROIDGLINVESTIGATIONS_RENDERER_H
#define ANDROIDGLINVESTIGATIONS_RENDERER_H

#include <EGL/egl.h>
#include <memory>

#include "Model.h"
#include "Program.h"


#include <tinygltf/tiny_gltf.h>

struct android_app;

class GameContext {
public:
    /*!
     * @param pApp the android_app this GameContext belongs to, needed to configure GL
     */
    inline GameContext(android_app *pApp) :
            app_(pApp),
            display_(EGL_NO_DISPLAY),
            surface_(EGL_NO_SURFACE),
            context_(EGL_NO_CONTEXT),
            width_(0),
            height_(0),
            shaderNeedsNewProjectionMatrix_(true) {
        initRenderer();
    }

    virtual ~GameContext();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();

    /*!
     * Renders all the models in the renderer
     */
    void render();

private:
    /*!
     * Performs necessary OpenGL initialization. Customize this if you want to change your EGL
     * context or application-wide settings.
     */
    void initRenderer();

    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void updateRenderArea();

    /*!
     * Creates the models for this sample. You'd likely load a scene configuration from a file or
     * get some other setup logic in your full game.
     */
    void createModels();

    void _drawModel(const Model &model);

    android_app *app_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLint width_;
    EGLint height_;

    bool shaderNeedsNewProjectionMatrix_;

    std::unique_ptr<Program> m_program;
    std::vector<Model> models_;
    float m_cam_rot = 0;
    tinygltf::Model m_model;
    std::pair<GLuint, std::map<int, GLuint>> m_vaoAndEbos;

    void drawMesh(const std::map<int, GLuint>& vbos, tinygltf::Model &model, tinygltf::Mesh &mesh);
    void drawModelNodes(const std::pair<GLuint, std::map<int, GLuint>>& vaoAndEbos, tinygltf::Model &model, tinygltf::Node &node);
    void drawModel(const std::pair<GLuint, std::map<int, GLuint>>& vaoAndEbos, tinygltf::Model &model);

    void bindMesh(std::map<int, GLuint>& vbos, tinygltf::Model &model, tinygltf::Mesh &mesh);
    void bindModelNodes(std::map<int, GLuint>& vbos, tinygltf::Model &model, tinygltf::Node &node);
    std::pair<GLuint, std::map<int, GLuint>> bindModel(tinygltf::Model &model);
};

#endif //ANDROIDGLINVESTIGATIONS_RENDERER_H