//
// Created by drave on 4/27/2025.
//

#include "Model.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace DGEngine {
    Model::Model() {
        glGenVertexArrays(1, &m_VertexArrayObject);
    }

    void Model::SetMeshes(const std::vector<std::shared_ptr<Mesh>> &meshes) {
        m_Meshes = meshes;
        for(auto &mesh : m_Meshes) {
            mesh->SetVertexArrayObject(m_VertexArrayObject);
        }
    }

    void Model::Update(float deltaTime) {
    };
}



