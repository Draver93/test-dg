//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#include "BaseComponent.h"
#include "../GameObject.h"

namespace DGEngine {
    template<typename T>
    T* BaseComponent::GetComponent() {
        if (m_Owner)
            return m_Owner->GetComponent<T>();
        return nullptr;
    }
}

