//
// Created by Finoshkin Aleksei on 4/28/2025.
//

#ifndef TESTDG_SPRITE_H
#define TESTDG_SPRITE_H

#include "BaseComponent.h"

namespace DGEngine {
    class Sprite : public BaseComponent {
    public:
        void Update(float deltaTime) override;
    };
}



#endif //TESTDG_SPRITE_H
