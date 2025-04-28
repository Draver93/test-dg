//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_SHADER_H
#define TESTDG_SHADER_H

#include "Resource.h"

class ResourceDirector;

class Shader : public Resource {
private:
    friend ResourceDirector;

    Shader(){};
};


#endif //TESTDG_SHADER_H
