//
// Created by Finoshkin Aleksei on 4/30/2025.
//

#ifndef TESTDG_EVENTDISPATCHER_H
#define TESTDG_EVENTDISPATCHER_H

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <memory>
#include <queue>

namespace DGEngine {
    struct Event {
    public:
        android_app* sender;
        Event(android_app* app_sender) : sender(app_sender) {}
        virtual ~Event() = default;
    };

    struct TouchEvent : public Event {
        enum class Type { Down, Up, Move };
        int pointerId;
        glm::vec2 pos;
        Type type;
        TouchEvent(int id, glm::vec2 touch_pos, Type eventType, android_app* sender)
            : pointerId(id), pos(touch_pos), type(eventType), Event(sender)  {}
    };

    struct KeyEvent : public Event {
        enum class Type { Down, Up };
        int code;
        Type type;
        KeyEvent(int key_code, Type eventType, android_app* sender)
                : code(key_code), type(eventType), Event(sender)  {}
    };

    class IEventListener;

    class EventDispatcher {
    public:
        static EventDispatcher& Get() {
            static EventDispatcher instance;
            return instance;
        }

        template<typename T>
        using EventCallback = std::function<void(const T&)>;

        template<typename T>
        void Subscribe(EventCallback<T> callback);

        void AddListener(IEventListener* listener);
        void RemoveListener(IEventListener* listener);

        void QueueEvent(std::unique_ptr<Event> event);
        void PumpEvents();

    private:
        void Dispatch(const Event& event);

    private:
        std::unordered_map<std::type_index, std::vector<std::function<void(const Event&)>>> m_LambdaSubscribers;
        std::vector<IEventListener*> m_Listeners;
        std::queue<std::unique_ptr<Event>> m_EventQueue;
    };

    class IEventListener {
    public:
        IEventListener();

        virtual ~IEventListener();
        virtual void OnEvent(const Event& event) = 0;
    };
}

#endif //TESTDG_EVENTDISPATCHER_H
