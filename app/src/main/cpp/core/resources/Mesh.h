//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_MESH_H
#define TESTDG_MESH_H

#include <GLES3/gl3.h>

#include "Resource.h"

#include "Material.h"

namespace DGEngine {
    class ResourceDirector;
    class Model;

    class Mesh : public Resource {
    public:
        struct Attribute {
            int vao;
            int size;
            int type;
            bool normalized;
            int byteStride;
            size_t byteOffset;
        };

        friend Model;
        friend ResourceDirector;
    public:
        void Draw();

    private:
        Mesh(int target, const uint8_t *buffer, long size, size_t offset);

    private:
        std::vector<Attribute> m_Attributes;
        GLuint m_VertexBufferObject = 0;
        GLuint m_IndexBufferObject = 0;
        GLuint m_VertexArrayObject = 0;

        GLenum m_DrawMode = GL_TRIANGLES;
        GLenum m_IndexType = 0;
        GLsizei m_IndexCount = 0;
        size_t m_IndexOffset = 0;

        int m_Target;
        std::shared_ptr<Material> m_Material;

    public:
        GLuint GetVertexArrayObject() { return m_VertexArrayObject; }
        void SetVertexArrayObject(GLuint vertexArrayObject) { m_VertexArrayObject = vertexArrayObject; }

        void SetMaterial(std::shared_ptr<Material> material) { m_Material = material; }
        std::shared_ptr<Material> GetMaterial() { return m_Material; };

        void SetAttributes(const std::vector<Attribute>& attributes);

        GLuint GetVertexBufferObject() { return m_VertexBufferObject; }
        void SetVertexBufferObject(GLuint vertexBufferObject) { m_VertexBufferObject = vertexBufferObject; }

        GLuint GetIndexBufferObject() { return m_IndexBufferObject; }
        void SetIndexBufferObject(GLuint indexBufferObject) { m_IndexBufferObject = indexBufferObject; }

        void SetDrawMode(GLenum drawMode) { m_DrawMode = drawMode; }
        void SetIndexType(GLenum indexType) { m_IndexType = indexType; };
        void SetIndexCount(GLsizei indexCount) { m_IndexCount = indexCount; };
        void SetIndexOffset(size_t indexOffset) { m_IndexOffset = indexOffset; };

    private:
        bool uploaded_ = false;

    public:
        bool IsUploaded() const { return uploaded_; }
        void MarkUploaded() { uploaded_ = true; }
    };

}



#endif //TESTDG_MESH_H
