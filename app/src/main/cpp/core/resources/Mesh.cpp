//
// Created by drave on 4/27/2025.
//

#include "Mesh.h"
#include "../components/Model.h"
#include "../components/Transform.h"
#include "../GameObject.h"

#include "ResourceDirector.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace DGEngine {
    Mesh::Mesh(int target, const uint8_t *buffer, long size, size_t offset){
        m_Material = ResourceDirector::DefaultMaterial();
    };

    void Mesh::SetAttributes(const std::vector<Attribute>& attributes) {
        m_Attributes = attributes;
    }

    GLuint Mesh::GetVertexArrayObject() {
        return m_Parent ? m_Parent->GetVertexArrayObject() : 0;
    }
    glm::mat4 Mesh::GetTransformMatrix() {
        if(m_Parent)
            return m_Parent->GetTransformMatrix();
        return glm::mat4();
    }

    void Mesh::Draw() {
        glDrawElements(m_DrawMode, m_IndexCount, m_IndexType, BUFFER_OFFSET(m_IndexOffset));
    }
}


