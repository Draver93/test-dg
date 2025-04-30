//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#ifndef TESTDG_BASECOMPONENT_H
#define TESTDG_BASECOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../system/ResourceDirector.h"

namespace DGEngine {
    class GameObject;

    class BaseComponent {
    public:
        virtual ~BaseComponent() = default;
        void SetOwner(GameObject *owner) { m_Owner = owner; }

        bool IsActive() { return m_Active; }
        void SetActive(bool state) { m_Active = state; }

        template<typename T>
        T *GetComponent();

        virtual void Update(float deltaTime) = 0;

    protected:
        GameObject *m_Owner = nullptr;

    private:
        bool m_Active = true;
    };

}

#endif //TESTDG_BASECOMPONENT_H
