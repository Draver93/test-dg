//
// Created by Finoshkin Aleksei on 4/28/2025.
//

#include "ResourceDirector.h"

namespace DGEngine {
    std::unordered_map<std::string, std::shared_ptr<Resource>> ResourceDirector::s_ResourceCache;

    std::shared_ptr<Mesh> ResourceDirector::CreateMesh(
            const std::vector<uint8_t> &indexData,
            const std::vector<Mesh::Attribute> &attributes,
            GLenum drawMode,
            GLenum indexType,
            GLsizei indexCount,
            size_t indexOffset ) {

        std::string key = HashArguments(indexData.data());

        auto it = s_ResourceCache.find(key);
        if (it != s_ResourceCache.end())
            return std::dynamic_pointer_cast<Mesh>(it->second);

        std::shared_ptr<Mesh> mesh = std::shared_ptr<Mesh>(new Mesh(indexData,
                                                                    attributes,
                                                                    drawMode,
                                                                    indexType,
                                                                    indexCount,
                                                                    indexOffset ));
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

