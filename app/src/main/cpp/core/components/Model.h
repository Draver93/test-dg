//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_MODEL_H
#define TESTDG_MODEL_H

#include <vector>

#include "BaseComponent.h"

class Model : public BaseComponent {
public:
    void Update(float deltaTime) override;

private:
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
};


#endif //TESTDG_MODEL_H
