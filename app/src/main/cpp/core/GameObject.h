//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_GAMEOBJECT_H
#define TESTDG_GAMEOBJECT_H


#include <map>
#include <typeindex>

#include "components/BaseComponent.h"

class GameObject {
private:
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponent>> components;
public:
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPtr = comp.get();
        rawPtr->setOwner(this);
        components[typeid(T)] = std::move(comp);
        return rawPtr;
    }

    template<typename T>
    T* GetComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }
};


#endif //TESTDG_GAMEOBJECT_H
