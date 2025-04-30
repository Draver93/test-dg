//
// Created by drave on 4/27/2025.
//

#include "Transform.h"

namespace DGEngine {
    void Transform::Update(float deltaTime) { };

    glm::mat4 Transform::GetMatrix() const {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotate = glm::toMat4(rotation);
        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
        return translate * rotate * scaleMat;;
    }

    void Transform::RotateEuler(const glm::vec3& eulerRadians) {
        rotation *= glm::quat(eulerRadians);
    }
    glm::vec3 Transform::GetRotation() const {
        return glm::eulerAngles(rotation);
    }

    void Transform::Rotate(const glm::vec3& eulerRadians) {
        glm::quat deltaRotation = glm::quat(eulerRadians);
        rotation = glm::normalize(deltaRotation * rotation);
    }

    void Transform::SetRotationEuler(const glm::vec3& eulerRadians) {
        rotation = glm::quat(eulerRadians);
    }

    glm::vec3 Transform::GetPosition() const {
        return position;
    }

    glm::vec3 Transform::GetForward() const {
        return rotation * glm::vec3(0, 0, -1);
    }

    glm::vec3 Transform::GetUp() const {
        return rotation * glm::vec3(0, 1, 0);
    }
}

