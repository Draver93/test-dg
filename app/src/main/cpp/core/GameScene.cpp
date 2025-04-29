//
// Created by drave on 4/27/2025.
//
#include "components/Model.h"
#include "components/Camera.h"


#include "resources/ResourceDirector.h"
#include "../../Utility.h"
#include "GameScene.h"

namespace DGEngine {
    void GameScene::AddGameObject(std::shared_ptr <GameObject> gameObject) {
        gameObject->SetScene(this);
        m_Objects.insert(gameObject);
    }

    void GameScene::RemoveGameObject(GameObject *gameObject) {
        gameObject->SetScene(nullptr);
        auto it = std::find_if(m_Objects.begin(), m_Objects.end(),
                               [gameObject](const std::shared_ptr <GameObject> &obj) {
                                   return obj.get() == gameObject;
                               });
        if (it != m_Objects.end()) m_Objects.erase(it);

    }

    void GameScene::SetDisplaySize(EGLint width, EGLint height) {
        m_Height = height;
        m_Width = width;
        Utility::buildPerspectiveMatrix(
                m_ProjectionMatrix,
                60.f,
                float(m_Width) / m_Height,
                0.1f,
                100.f);
    }


    void GameScene::Update(float deltaTime) {

        std::vector<std::shared_ptr<Camera>> activeCamera;
        std::unordered_map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Mesh>>> drawBatches;

        for(auto &go : m_Objects) {
            go->Update(deltaTime);


            //DGEngine::Camera *camera = go->GetComponent<DGEngine::Camera>();
            //if(camera) {

            //}

            DGEngine::Model *model = go->GetComponent<DGEngine::Model>();
            if(model) {
                const std::vector<std::shared_ptr<Mesh>> meshes = model->GetMeshes();
                for(const std::shared_ptr<Mesh> &mesh : meshes)
                    drawBatches[mesh->GetMaterial()].push_back(mesh);
            }
        }

        //camera
        float lookAtMatrix[16] = {0};
        {
            Utility::buildLookAtMatrix(lookAtMatrix,
                                       {0.f, m_cam_rot, -5.f},
                                       {0.f, 0.f, 0.f},
                                       {0.f, 1.f, 0.f} );

            m_cam_rot += 1.0f;
            if(m_cam_rot > 20) m_cam_rot = -20;

        }

        GLuint lastBoundVAO = 0;
        for(auto [material, meshes] : drawBatches) {
            glUseProgram(material->Get());

            material->SetUniform("uProjection", m_ProjectionMatrix);
            material->SetUniform("uView", lookAtMatrix);

            for (auto& mesh : meshes) {
                GLuint vao = mesh->GetVertexArrayObject();
                if (vao != lastBoundVAO) {
                    glBindVertexArray(vao);
                    lastBoundVAO = vao;
                }
                mesh->Draw(); // No VAO binding inside
            }
        }
        glBindVertexArray(0);
    }
}



