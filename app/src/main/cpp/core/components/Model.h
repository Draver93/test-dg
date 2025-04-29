//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_MODEL_H
#define TESTDG_MODEL_H

#include "BaseComponent.h"

#include <GLES3/gl3.h>
#include <vector>

namespace DGEngine {
    class Model : public BaseComponent {
    public:
        void Update(float deltaTime) override;

    public:
        explicit Model();
        void SetMeshes(const std::vector<std::shared_ptr<Mesh>> &meshes);
        const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const { return m_Meshes; }

        GLuint GetVertexArrayObject() { return m_VertexArrayObject; }
        glm::mat4 GetTransformMatrix();

    private:
        std::vector<std::shared_ptr<Mesh>> m_Meshes;
        GLuint m_VertexArrayObject;
    };
}



#endif //TESTDG_MODEL_H
