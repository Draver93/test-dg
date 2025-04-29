//
// Created by drave on 4/27/2025.
//

#include "RotationScript.h"

#include "../core/components/Transform.h"
#include "../core/GameObject.h"


void RotationScript::Update(float deltaTime) {
    DGEngine::Transform* transform = m_Owner->GetComponent<DGEngine::Transform>();
    if(transform) {
        glm::vec3 rot = transform->GetRotation();
        rot[0] +=  0.1f * deltaTime;
        rot[1] -=  0.3f * deltaTime;
        rot[2] +=  0.8f * deltaTime;

        transform->SetRotationEuler(rot);
    }
};
