//
// Created by Finoshkin Aleksei on 4/30/2025.
//

#include "EventDispatcher.h"

namespace DGEngine {

    template<typename T>
    void EventDispatcher::Subscribe(EventCallback<T> callback) {
        auto& vec = m_LambdaSubscribers[typeid(T)];
        vec.push_back([cb = std::move(callback)](const Event& e) {
            cb(static_cast<const T&>(e));
        });
    }

    void EventDispatcher::AddListener(IEventListener* listener) {
        m_Listeners.push_back(listener);
    }

    void EventDispatcher::RemoveListener(IEventListener* listener) {
        m_Listeners.erase(
                std::remove(m_Listeners.begin(), m_Listeners.end(), listener),
                m_Listeners.end()
        );
    }

    void EventDispatcher::Dispatch(const Event& event) {
        // 1. Lambdas
        auto it = m_LambdaSubscribers.find(typeid(event));
        if (it != m_LambdaSubscribers.end()) {
            for (auto& func : it->second) {
                func(event);
            }
        }

        // 2. Inheritance-based listeners
        for (auto* listener : m_Listeners) {
            listener->OnEvent(event);
        }
    }

    void EventDispatcher::QueueEvent(std::unique_ptr<Event> event) {
        m_EventQueue.push(std::move(event));
    }

    void EventDispatcher::PumpEvents() {
        while (!m_EventQueue.empty()) {
            Dispatch(*(m_EventQueue.front().get()));
            m_EventQueue.pop();
        }
    }

    IEventListener::IEventListener() {
        EventDispatcher::Get().AddListener(this);
    }

    IEventListener::~IEventListener() {
        EventDispatcher::Get().RemoveListener(this);
    }
}