//
// Created by drave on 4/27/2025.
//

#include "GameScene.h"

void GameScene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    m_Objects.push_back(gameObject);
}