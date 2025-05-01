//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#ifndef TESTDG_MESH_H
#define TESTDG_MESH_H

#include <GLES3/gl3.h>
#include <glm/glm.hpp>

#include "Resource.h"

#include "Material.h"

namespace DGEngine {
    class ResourceDirector;
    class Model;

    class Mesh : public Resource {
    public:
        struct Attribute {
            int vao;
            std::vector<uint8_t> data;
            int size;
            int type;
            int target;
            bool normalized;
            int byteStride;
            size_t byteOffset;
        };

        friend Model;
        friend ResourceDirector;
    public:
        void Draw();
        void Bind();
        void UploadToGPU();
    private:
        Mesh(
                const std::vector<uint8_t> &indexData,
                const std::vector<Mesh::Attribute> &attributes,
                GLenum drawMode,
                GLenum indexType,
                GLsizei indexCount,
                size_t indexOffset );

    private:
        std::vector<Attribute> m_Attributes;
        std::vector<uint8_t> m_IndexData;

        GLenum m_DrawMode = GL_TRIANGLES;
        GLenum m_IndexType = 0;
        GLsizei m_IndexCount = 0;
        size_t m_IndexOffset = 0;

        std::shared_ptr<Material> m_Material;

    public:
        GLuint GetVertexArrayObject();

        void SetMaterial(std::shared_ptr<Material> material) { m_Material = material; }
        std::shared_ptr<Material> GetMaterial() { return m_Material; };
        void SetParent(Model* parent) { m_Parent = parent; };

    private:
        Model* m_Parent;

    };

}



#endif //TESTDG_MESH_H
