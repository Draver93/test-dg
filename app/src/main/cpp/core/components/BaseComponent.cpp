//
// Created by drave on 4/27/2025.
//

#include "BaseComponent.h"
#include "../GameObject.h"

namespace DGEngine {
    template<typename T>
    T* BaseComponent::GetComponent() {
        if (owner)
            return owner->GetComponent<T>();
        return nullptr;
    }
}

