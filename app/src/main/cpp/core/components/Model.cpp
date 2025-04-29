//
// Created by drave on 4/27/2025.
//

#include "Model.h"

#include "Transform.h"
#include "../GameObject.h"

namespace DGEngine {
    Model::Model() {
        glGenVertexArrays(1, &m_VertexArrayObject);
    }

    void Model::SetMeshes(const std::vector<std::shared_ptr<Mesh>> &meshes) {
        m_Meshes = meshes;
        for(auto &mesh : m_Meshes) {
            mesh->SetParent(this);
        }
    }

    void Model::Update(float deltaTime) {

    };

    glm::mat4 Model::GetTransformMatrix() {
        Transform* transform = m_Owner->GetComponent<Transform>();
        if(transform) {
            return transform->GetMatrix();
        }
        return glm::mat4();
    }

}



