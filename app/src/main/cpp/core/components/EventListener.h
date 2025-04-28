//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_EVENTLISTENER_H
#define TESTDG_EVENTLISTENER_H

#include "BaseComponent.h"

class EventListener : public BaseComponent {
public:
    void Update(float deltaTime) override;
};


#endif //TESTDG_EVENTLISTENER_H
