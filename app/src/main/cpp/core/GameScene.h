//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_GAMESCENE_H
#define TESTDG_GAMESCENE_H

#include <set>
#include <EGL/egl.h>

#include "GameObject.h"

namespace DGEngine {
    class GameScene {
    public:
        void AddGameObject(std::shared_ptr<GameObject> gameObject);
        void RemoveGameObject(GameObject* gameObject);
        void Update(float deltaTime);
        void SetDisplaySize(EGLint width, EGLint height);
    private:
        std::set<std::shared_ptr<GameObject>> m_Objects;

        float m_ProjectionMatrix[16];
        EGLint m_Width = 800;
        EGLint m_Height = 600;
        float m_cam_rot = 0;
    };
}




#endif //TESTDG_GAMESCENE_H
