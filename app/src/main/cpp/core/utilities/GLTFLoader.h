//
// Created by drave on 4/28/2025.
//

#ifndef TESTDG_GLTFLOADER_H
#define TESTDG_GLTFLOADER_H

#include <tiny_gltf.h>
#include <android/asset_manager.h>

namespace DGEngine {
    class GLTFLoader {
    public:
        static std::shared_ptr<tinygltf::Model> Load(const char *filename) {
            auto loader = Get()->m_Loader;

            std::shared_ptr<tinygltf::Model> result_model = std::make_shared<tinygltf::Model>();
            std::string err, warn;

            bool res = loader.LoadASCIIFromFile(result_model.get(), &err, &warn, filename);
            if (!warn.empty()) throw std::runtime_error("WARN: " + warn);
            if (!err.empty()) throw std::runtime_error("ERR: " + err);
            if (!res) throw std::runtime_error("Failed to load glTF: " + std::string(filename));

            return result_model;
        }

        static GLTFLoader* Init(AAssetManager *assetManager) {
            if(!s_Instance) s_Instance = new GLTFLoader(assetManager);
            return s_Instance;
        }


    private:
        tinygltf::TinyGLTF m_Loader;
        static inline GLTFLoader* s_Instance = nullptr;  // <--- C++17 "inline static"

    private:
        explicit GLTFLoader(AAssetManager *assetManager);
        static GLTFLoader* Get() {
            if (!s_Instance) throw std::runtime_error("GLTFLoader not initialized");
            return s_Instance;
        }
    };
}



#endif //TESTDG_GLTFLOADER_H
