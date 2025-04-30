//
// Created by drave on 4/28/2025.
//

#ifndef TESTDG_LIGHT_H
#define TESTDG_LIGHT_H

#include "BaseComponent.h"

namespace DGEngine {
    class Light : public BaseComponent {
    public:
        void Update(float deltaTime) override;
        Light(glm::vec3 c, float intens) : color(c), intensity(intens) {};

        glm::vec3 GetPosition();

    public:
        glm::vec3 color;
        float intensity;
    };
}



#endif //TESTDG_LIGHT_H
