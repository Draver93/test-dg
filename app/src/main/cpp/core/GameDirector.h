//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_GAMEDIRECTOR_H
#define TESTDG_GAMEDIRECTOR_H

#include "GameObject.h"

namespace DGEngine {
    class GameDirector {
    public:
        static std::shared_ptr<GameObject> CreateModel(const char* filename);
    };

}



#endif //TESTDG_GAMEDIRECTOR_H
