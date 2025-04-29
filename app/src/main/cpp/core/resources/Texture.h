//
// Created by drave on 4/27/2025.
//

#ifndef TESTDG_TEXTURE_H
#define TESTDG_TEXTURE_H

#include "Resource.h"

namespace DGEngine {
    class ResourceDirector;

    class Texture : public Resource {
    private:
        friend ResourceDirector;

        Texture(){};
    };

}



#endif //TESTDG_TEXTURE_H
