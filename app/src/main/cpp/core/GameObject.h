//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_GAMEOBJECT_H
#define TESTDG_GAMEOBJECT_H


#include <map>
#include <typeindex>

#include "components/BaseComponent.h"

namespace DGEngine {
    class GameScene;

    class GameObject {
    public:
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            auto comp = std::make_unique<T>(std::forward<Args>(args)...);
            T* rawPtr = comp.get();
            rawPtr->SetOwner(this);
            m_Components[typeid(T)] = std::move(comp);
            return rawPtr;
        }

        // example: m_Owner->GetComponent<Transform>();
        template<typename T>
        T* GetComponent() {
            auto it = m_Components.find(typeid(T));
            if (it != m_Components.end()) {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;
        }

        void SetScene(GameScene* scene);
        const GameScene* GetScene();
    public:
        void Update(float deltaTime);

    private:
        GameScene* m_Scene = nullptr;
        std::unordered_map<std::type_index, std::unique_ptr<BaseComponent>> m_Components;
    };
}




#endif //TESTDG_GAMEOBJECT_H
