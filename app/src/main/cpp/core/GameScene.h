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
    private:
        std::set<std::shared_ptr<GameObject>> m_Objects;

    };
}




#endif //TESTDG_GAMESCENE_H
