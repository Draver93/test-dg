//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_GAMESCENE_H
#define TESTDG_GAMESCENE_H

#include <list>

#include "GameObject.h"

class GameScene {
public:
    void AddGameObject(std::shared_ptr<GameObject> gameObject);

private:
    std::list<std::shared_ptr<GameObject>> m_Objects;
};


#endif //TESTDG_GAMESCENE_H
