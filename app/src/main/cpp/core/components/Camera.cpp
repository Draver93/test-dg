//
// Created by Finoshkin Aleksei on 4/28/2025.
//

#include "Camera.h"
#include "Transform.h"

#include "../GameObject.h"
#include "../../Utility.h"

namespace DGEngine {
    Camera::Camera(EGLDisplay display, EGLSurface surface)
        : m_Display(display), m_Surface(surface) {
        UpdateRenderArea();
    }

    void Camera::Update(float deltaTime) {
        Transform* transform = m_Owner->GetComponent<Transform>();
        if(transform) {
            if(m_NeedMatrixRecalculate) {
                m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
                m_NeedMatrixRecalculate = false;
            }
            m_ViewMatrix = glm::lookAt(transform->GetPosition(), transform->GetForward(), transform->GetUp());
        }

    };

    void Camera::UpdateRenderArea() {
        EGLint width;
        eglQuerySurface(m_Display, m_Surface, EGL_WIDTH, &width);

        EGLint height;
        eglQuerySurface(m_Display, m_Surface, EGL_HEIGHT, &height);

        if (width != m_Width || height != m_Height) {
            m_Width = width;
            m_Height = height;
            aspect = float(m_Width) / m_Height;
            glViewport(0, 0, width, height);
            m_NeedMatrixRecalculate = true;
        }
    }
}