//
// Created by drave on 4/27/2025.
//
#include "components/Model.h"
#include "components/Camera.h"


#include "resources/ResourceDirector.h"
#include "../Utility.h"
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

    void GameScene::Update(float deltaTime) {

        std::vector<std::shared_ptr<Camera>> activeCamera;
        std::unordered_map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Mesh>>> drawBatches;

        DGEngine::Camera *active_camera = nullptr;
        for(auto &go : m_Objects) {
            go->Update(deltaTime);

            DGEngine::Camera *camera = go->GetComponent<DGEngine::Camera>();
            if(camera && camera->IsActive()) {
                if(!active_camera) active_camera = camera;
                else camera->SetActive(false);
            }

            DGEngine::Model *model = go->GetComponent<DGEngine::Model>();
            if(model) {
                const std::vector<std::shared_ptr<Mesh>> meshes = model->GetMeshes();
                for(const std::shared_ptr<Mesh> &mesh : meshes)
                    drawBatches[mesh->GetMaterial()].push_back(mesh);
            }
        }

        GLuint lastBoundVAO = 0;
        for(auto [material, meshes] : drawBatches) {
            glUseProgram(material->Get());

            if(active_camera) {
                material->SetUniform("uProjection", glm::value_ptr(active_camera->GetProjectionMatrix()));
                material->SetUniform("uView", glm::value_ptr(active_camera->GetViewMatrix()));
            }

            for (auto& mesh : meshes) {
                GLuint vao = mesh->GetVertexArrayObject();
                material->SetUniform("uModelMatrix", glm::value_ptr(mesh->GetTransformMatrix()));
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



