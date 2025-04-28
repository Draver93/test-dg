//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_RENDERER_H
#define TESTDG_RENDERER_H

#include "BaseComponent.h"

class Renderer : public BaseComponent { //new Program replacement
public:
    void Update(float deltaTime) override;
};


#endif //TESTDG_RENDERER_H
