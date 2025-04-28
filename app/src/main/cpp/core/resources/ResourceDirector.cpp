//
// Created by drave on 4/28/2025.
//

#include "ResourceDirector.h"

std::shared_ptr<Mesh> ResourceDirector::CreateMesh() {
    return std::shared_ptr<Mesh>(new Mesh());
}
