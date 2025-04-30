//
// Created by drave on 4/28/2025.
//

#ifndef TESTDG_RESOURCEDIRECTOR_H
#define TESTDG_RESOURCEDIRECTOR_H

#include "../resources/Mesh.h"
#include "../resources/Shader.h"
#include "../resources/Material.h"
#include "../resources/Texture.h"

#include <sstream>
#include <map>

namespace DGEngine {
    template<typename... Args>
    std::string HashArguments(const Args&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        return oss.str();
    }

    class ResourceDirector {
    public:
        static std::shared_ptr<Mesh> CreateMesh(int target, const uint8_t *buffer, long size, size_t offset);
        static std::shared_ptr<Material> DefaultMaterial();
        static std::shared_ptr<Shader> CreateShader(GLenum shaderType, const std::string &shaderSource);

        static void Clear();
    private:
        static std::unordered_map<std::string, std::shared_ptr<Resource>> s_ResourceCache;
    };
}




#endif //TESTDG_RESOURCEDIRECTOR_H
