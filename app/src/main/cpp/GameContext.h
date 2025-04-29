#ifndef ANDROIDGLINVESTIGATIONS_RENDERER_H
#define ANDROIDGLINVESTIGATIONS_RENDERER_H

#include <EGL/egl.h>
#include <memory>

#include "core/GameScene.h"
#include "core/GameDirector.h"
#include "core/components/Renderer.h"
#include "core/components/Transform.h"
#include "core/utilities/GLTFLoader.h"

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

struct android_app;

class GameContext {
private:
    std::shared_ptr<DGEngine::GameScene> m_ActiveScene;

public:

    explicit GameContext(android_app *pApp);
    virtual ~GameContext();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();


    void update();

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

    android_app *app_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLint width_;
    EGLint height_;

    bool shaderNeedsNewProjectionMatrix_;

    TimePoint m_PreviousTime;
};

#endif //ANDROIDGLINVESTIGATIONS_RENDERER_H