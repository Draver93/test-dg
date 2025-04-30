//
// Created by Finoshkin Aleksei on 4/28/2025.
//

#include "Light.h"
#include "Transform.h"
#include "../GameObject.h"


namespace DGEngine {
    void Light::Update(float deltaTime) { };

    glm::vec3 Light::GetPosition() {
        Transform* transform = m_Owner->GetComponent<Transform>();
        if(transform) return transform->position;
        return glm::vec3();
    }
}