//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#include "Mesh.h"
#include "../components/Model.h"
#include "../components/Transform.h"
#include "../GameObject.h"

#include "../system/ResourceDirector.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace DGEngine {
    Mesh::Mesh(   const std::vector<uint8_t> &indexData,
                  const std::vector<Mesh::Attribute> &attributes,
                  GLenum drawMode,
                  GLenum indexType,
                  GLsizei indexCount,
                  size_t indexOffset ) :
            m_Material(ResourceDirector::DefaultMaterial()),
            m_IndexData(indexData),
            m_Attributes(attributes),
            m_DrawMode(drawMode),
            m_IndexType(indexType),
            m_IndexCount(indexCount),
            m_IndexOffset(indexOffset){}

    void Mesh::Bind() {
        // Setup vertex attributes
        for (const auto& attr : m_Attributes) {
            GLuint vertexBufferObject;
            glGenBuffers(1, &vertexBufferObject);
            glBindBuffer(attr.target, vertexBufferObject);
            glBufferData(attr.target, attr.data.size(), attr.data.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(attr.vao);
            glVertexAttribPointer(attr.vao,
                                  attr.size,
                                  attr.type,
                                  attr.normalized ? GL_TRUE : GL_FALSE,
                                  attr.byteStride,
                                  (void*)(intptr_t)(attr.byteOffset));
        }
        // Upload IBO if exists
        if (!m_IndexData.empty()) {
            GLuint indexBufferObject;
            glGenBuffers(1, &indexBufferObject);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         m_IndexData.size(),
                         m_IndexData.data(),
                         GL_STATIC_DRAW);
        }
    }

    GLuint Mesh::GetVertexArrayObject() {
        if(m_Parent) return m_Parent->GetVertexArrayObject();
        return 0;
    }

    void Mesh::Draw() {
        glDrawElements(m_DrawMode, m_IndexCount, m_IndexType, BUFFER_OFFSET(m_IndexOffset));
    }
}


