//
// Created by Finoshkin Aleksei on 4/28/2025.
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
        static std::shared_ptr<Mesh> CreateMesh(
                const std::vector<uint8_t> &indexData,
                const std::vector<Mesh::Attribute> &attributes,
                GLenum drawMode,
                GLenum indexType,
                GLsizei indexCount,
                size_t indexOffset );

        static std::shared_ptr<Material> DefaultMaterial();
        static std::shared_ptr<Shader> CreateShader(GLenum shaderType, const std::string &shaderSource);

        static void Clear();
    private:
        static std::unordered_map<std::string, std::shared_ptr<Resource>> s_ResourceCache;
    };
}




#endif //TESTDG_RESOURCEDIRECTOR_H
