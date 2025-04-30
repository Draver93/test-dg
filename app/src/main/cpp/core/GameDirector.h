//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_GAMEDIRECTOR_H
#define TESTDG_GAMEDIRECTOR_H

#include <EGL/egl.h>
#include "GameObject.h"

namespace DGEngine {
    class GameDirector {
    public:
        static std::shared_ptr<GameObject> CreateModel(const char* filename);
        static std::shared_ptr<GameObject> CreateCamera(EGLDisplay m_Display, EGLSurface m_Surface);
        static std::shared_ptr<GameObject> CreateLight(glm::vec3 color, float intensity);
    };

}



#endif //TESTDG_GAMEDIRECTOR_H
