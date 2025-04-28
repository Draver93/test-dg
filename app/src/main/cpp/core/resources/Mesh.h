//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_MESH_H
#define TESTDG_MESH_H

#include "Resource.h"

class ResourceDirector;

class Mesh : public Resource {
    friend ResourceDirector;
private:

    Mesh(){};
};


#endif //TESTDG_MESH_H
