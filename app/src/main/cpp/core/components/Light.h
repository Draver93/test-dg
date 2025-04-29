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
    };
}



#endif //TESTDG_LIGHT_H
