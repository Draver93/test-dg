//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_BASECOMPONENT_H
#define TESTDG_BASECOMPONENT_H

#include "../resources/ResourceDirector.h"

class GameObject;

class BaseComponent {
protected:
    GameObject* owner = nullptr;
public:
    virtual ~BaseComponent() = default;

    void setOwner(GameObject* o) { owner = o; }

    template<typename T>
    T* GetComponent();

    virtual void Update(float deltaTime) = 0;
};


#endif //TESTDG_BASECOMPONENT_H
