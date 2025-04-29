//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_TRANSFORM_H
#define TESTDG_TRANSFORM_H

#include "BaseComponent.h"

namespace DGEngine {
    class Transform : public BaseComponent {
    public:
        void Update(float deltaTime) override;
    };

}



#endif //TESTDG_TRANSFORM_H
