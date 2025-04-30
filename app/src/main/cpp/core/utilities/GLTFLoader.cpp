//
// Created by Finoshkin Aleksei on 4/28/2025.
//
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "GLTFLoader.h"

#include <string>
#include <vector>

namespace DGEngine {
    GLTFLoader::GLTFLoader(AAssetManager *assetManager)
    {
        auto file_exists_fn = [](const std::string& path, void* user_data) -> bool {
            AAssetManager* assetManager = reinterpret_cast<AAssetManager*>(user_data);
            AAsset* asset = AAssetManager_open(assetManager, path.c_str(), AASSET_MODE_BUFFER);
            if (asset) {
                AAsset_close(asset);
                return true;
            }
            return false;
        };

        auto expand_file_path_fn = [](const std::string& path, void* user_data) -> std::string {
            return path; // No expansion needed on Android
        };

        auto read_whole_file_fn = [](std::vector<unsigned char>* out, std::string* err, const std::string& path, void* user_data) -> bool {
            AAssetManager* assetManager = reinterpret_cast<AAssetManager*>(user_data);
            AAsset* asset = AAssetManager_open(assetManager, path.c_str(), AASSET_MODE_BUFFER);

            if (!asset) {
                if (err) *err = "Failed to open asset: " + path;
                return false;
            }

            off_t length = AAsset_getLength(asset);
            out->resize(length); // Resize the vector to fit the data
            AAsset_read(asset, out->data(), length); // Read into the buffer
            AAsset_close(asset); // Close the asset

            return true; // Successfully read the file
        };

        auto write_whole_file_fn = [](std::string* err, const std::string& filepath, const std::vector<unsigned char>& contents, void* user_data) -> bool {
            // This example does not implement writing, so we return false
            if (err) *err = "Write operation is not implemented.";
            return false;  // No-op: we don't handle writing in this case
        };

        auto get_file_size_fn = [](size_t* filesize_out, std::string* err, const std::string& filepath, void* user_data) -> bool {
            AAssetManager* assetManager = reinterpret_cast<AAssetManager*>(user_data);
            AAsset* asset = AAssetManager_open(assetManager, filepath.c_str(), AASSET_MODE_BUFFER);

            if (!asset) {
                if (err) *err = "Failed to open asset: " + filepath;
                return false;
            }

            size_t size = AAsset_getLength(asset);
            *filesize_out = size; // Set the file size
            AAsset_close(asset); // Close the asset

            return true; // Successfully retrieved the file size
        };

        tinygltf::FsCallbacks fs_callbacks = {
                file_exists_fn, // FileExists function
                expand_file_path_fn,    // ExpandFilePath function
                read_whole_file_fn, // ReadWholeFile function
                write_whole_file_fn,    // WriteWholeFile function (optional, no-op in this case)
                get_file_size_fn,   // GetFileSizeInBytes function
                assetManager    // Set user_data as AAssetManager
        };
        m_Loader.SetFsCallbacks(fs_callbacks);
    }
}

