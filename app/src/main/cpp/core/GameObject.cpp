//
// Created by drave on 4/27/2025.
//

#include "GameObject.h"
#include "GameScene.h"

namespace DGEngine {
    void GameObject::SetScene(GameScene* scene) {
        if(m_Scene) {
            m_Scene->RemoveGameObject(this);
        }
        m_Scene = scene;
    }

    const GameScene* GameObject::GetScene() {
        return m_Scene;
    }

    void GameObject::Update(float deltaTime) {
        for(auto &component : m_Components)
            if(component.second->IsActive())component.second->Update(deltaTime);
    }

}

