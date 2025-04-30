//
// Created by drave on 4/27/2025.
//

#include "RotationScript.h"

#include "../core/components/Transform.h"
#include "../core/GameObject.h"

#include <android/keycodes.h>

void RotationScript::Update(float deltaTime) {
    DGEngine::Transform* transform = m_Owner->GetComponent<DGEngine::Transform>();
    if (transform) {
        glm::vec2 rot;
        if (isTouching)  m_RotVelocity = m_CurrentTouchPos - m_LastTouchPos;
        else {
            m_RotVelocity *= m_RotDamping;
            rot = m_RotVelocity;
        }

        glm::vec3 rotationChange = glm::vec3(
                -m_RotVelocity.y * m_RotAcceleration * deltaTime,
                m_RotVelocity.x * m_RotAcceleration * deltaTime,
                0.0f );

        transform->Rotate(rotationChange);
    }
    m_LastTouchPos = m_CurrentTouchPos;
}

void RotationScript::OnEvent(const DGEngine::Event& event) {
    if (const auto* touch = dynamic_cast<const DGEngine::TouchEvent*>(&event)) {
        switch (touch->type) {
            case DGEngine::TouchEvent::Type::Down: {
                m_LastTouchPos = glm::vec2(touch->pos.x, touch->pos.y);
                m_CurrentTouchPos = m_LastTouchPos;
                isTouching = true;
                break;
            }
            case DGEngine::TouchEvent::Type::Up: {
                isTouching = false;
                break;
            }
            case DGEngine::TouchEvent::Type::Move: {
                m_CurrentTouchPos = glm::vec2(touch->pos.x, touch->pos.y);
                break;
            }
        }
    }
    else if(const auto* keyPress = dynamic_cast<const DGEngine::KeyEvent*>(&event)) {
        if(keyPress->type == DGEngine::KeyEvent::Type::Up) {
            switch (keyPress->code) {
                case AKEYCODE_BACK: {
                    GameActivity_finish(keyPress->sender->activity);
                    keyPress->sender->destroyRequested = 1;
                    break;
                }
            }
        }
        else { /*Down*/ }
    }
}
