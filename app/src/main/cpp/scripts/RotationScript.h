//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#ifndef TESTDG_ROTATIONSCRIPT_H
#define TESTDG_ROTATIONSCRIPT_H

#include "../core/components/BaseComponent.h"
#include "../core/system/EventDispatcher.h"


class RotationScript : public DGEngine::BaseComponent, DGEngine::IEventListener {
public:
    void Update(float deltaTime) override;
    void OnEvent(const DGEngine::Event& event) override;

private:

    glm::vec2 m_LastTouchPos = glm::vec2(0.f, 0.f);
    glm::vec2 m_CurrentTouchPos = glm::vec2(0.f, 0.f);
    bool isTouching = false;

    glm::vec2 m_RotVelocity = glm::vec2(0.f, 0.f);
    float m_RotDamping = 0.98f;
    float m_RotAcceleration = 0.1f;
};


#endif //TESTDG_ROTATIONSCRIPT_H
