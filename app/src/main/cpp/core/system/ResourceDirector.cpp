//
// Created by drave on 4/28/2025.
//

#include "ResourceDirector.h"

namespace DGEngine {
    std::unordered_map<std::string, std::shared_ptr<Resource>> ResourceDirector::s_ResourceCache;

    std::shared_ptr<Mesh> ResourceDirector::CreateMesh(int target, const uint8_t *buffer, long size, size_t offset) {
        std::string key = HashArguments(buffer, size);

        auto it = s_ResourceCache.find(key);
        if (it != s_ResourceCache.end())
            return std::dynamic_pointer_cast<Mesh>(it->second);

        std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh(target, buffer, size, offset));
        s_ResourceCache[key] = mesh;
        return mesh;
    }

    std::shared_ptr<Material> ResourceDirector::DefaultMaterial() {
        std::string key = HashArguments("DefaultMaterial");

        auto it = s_ResourceCache.find(key);
        if (it != s_ResourceCache.end())
            return std::dynamic_pointer_cast<Material>(it->second);

        std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
        s_ResourceCache[key] = material;
        return material;
    }

    std::shared_ptr<Shader> ResourceDirector::CreateShader(GLenum shaderType, const std::string &shaderSource) {
        std::string key = HashArguments(shaderType, shaderSource);

        auto it = s_ResourceCache.find(key);
        if (it != s_ResourceCache.end())
            return std::dynamic_pointer_cast<Shader>(it->second);

        std::shared_ptr<Shader> shader = std::shared_ptr<Shader>(new Shader(shaderType, shaderSource));
        s_ResourceCache[key] = shader;
        return shader;
    }

    void ResourceDirector::Clear() {
        s_ResourceCache.clear();
    }

}

