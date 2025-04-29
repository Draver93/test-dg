//
// Created by drave on 4/28/2025.
//

#ifndef TESTDG_CAMERA_H
#define TESTDG_CAMERA_H

#include <EGL/egl.h>
#include "BaseComponent.h"

namespace DGEngine {
    class Camera : public BaseComponent {
    public:
        void Update(float deltaTime) override;
        Camera(EGLDisplay display, EGLSurface surface);

        const glm::mat4& GetViewMatrix() const {
            return m_ViewMatrix;
        }

        const glm::mat4& GetProjectionMatrix() const {
            return m_ProjectionMatrix;
        }
    public:
        float fov = 60, aspect = 0, nearPlane = 0.1f, farPlane = 100;

    private:
        void UpdateRenderArea();

    private:
        EGLint m_Width;
        EGLint m_Height;

        EGLDisplay m_Display;
        EGLSurface m_Surface;

        bool m_NeedMatrixRecalculate = true;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;

        float m_cam_rot = 0;
    };
}

#endif //TESTDG_CAMERA_H
