//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#ifndef TESTDG_TRANSFORM_H
#define TESTDG_TRANSFORM_H

#include "BaseComponent.h"

namespace DGEngine {
    class Transform : public BaseComponent {
    public:
        void Update(float deltaTime) override;

        glm::vec3 position{0.0f};
        glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f}; // identity quaternion
        glm::vec3 scale{1.0f};

        glm::mat4 GetMatrix() const;
        void Rotate(const glm::vec3& eulerRadians);
        void RotateEuler(const glm::vec3& eulerRadians);
        void SetRotationEuler(const glm::vec3& eulerRadians);

        glm::vec3 GetRotation() const;
        glm::vec3 GetPosition() const;
        glm::vec3 GetForward() const;
        glm::vec3 GetUp() const;

    };

}



#endif //TESTDG_TRANSFORM_H
