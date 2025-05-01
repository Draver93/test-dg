//
// Created by Finoshkin Aleksei on 4/27/2025.
//

#include "GameDirector.h"
#include "components/Model.h"
#include "components/Light.h"
#include "components/Camera.h"
#include "components/Transform.h"

#include "utilities/GLTFLoader.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace DGEngine {

    struct MeshData {
        std::vector<Mesh::Attribute> attributes;
        //std::vector<uint8_t> vertexData;
        std::vector<uint8_t> indexData;
        GLenum drawMode;
        GLenum indexType;
        GLsizei indexCount;
        size_t indexOffset;
    };

    int getAttributeLocation(const char *name) {
        if (!strcmp(name, "POSITION")) return 0;
        else if (!strcmp(name, "NORMAL")) return 1;
        else if (!strcmp(name, "TEXCOORD_0")) return 2;
        return -1;
    }

    void createMeshObjects(std::vector<std::shared_ptr<Mesh>>& meshes, const std::shared_ptr<tinygltf::Model>& model, tinygltf::Mesh& gltfMesh) {
        for (auto& primitive : gltfMesh.primitives) {
            MeshData meshData;

            // 1. Gather vertex attributes and data
            meshData.attributes.reserve(primitive.attributes.size());
            for (auto& attrib : primitive.attributes) {
                const tinygltf::Accessor& accessor = model->accessors[attrib.second];
                const tinygltf::BufferView& bufferView = model->bufferViews[accessor.bufferView];
                const tinygltf::Buffer& buffer = model->buffers[bufferView.buffer];

                int val = getAttributeLocation(attrib.first.c_str());
                if(val == -1) continue;

                // Set up attribute description
                Mesh::Attribute attr;
                attr.vao = getAttributeLocation(attrib.first.c_str());
                attr.size = (accessor.type == TINYGLTF_TYPE_SCALAR) ? 1 : accessor.type;
                attr.type = accessor.componentType;
                attr.target = bufferView.target;
                attr.normalized = accessor.normalized;
                attr.byteStride = accessor.ByteStride(bufferView);
                attr.byteOffset = accessor.byteOffset;
                attr.data.assign(
                        buffer.data.begin() + bufferView.byteOffset,
                        buffer.data.begin() + bufferView.byteOffset + bufferView.byteLength
                );
                meshData.attributes.push_back(attr);
            }

            // 2. Handle index data if present
            if (primitive.indices >= 0) {
                const tinygltf::Accessor& indexAccessor = model->accessors[primitive.indices];
                const tinygltf::BufferView& indexBufferView = model->bufferViews[indexAccessor.bufferView];
                const tinygltf::Buffer& indexBuffer = model->buffers[indexBufferView.buffer];

                // Store raw index data
                meshData.indexData.assign(
                        indexBuffer.data.begin() + indexBufferView.byteOffset,
                        indexBuffer.data.begin() + indexBufferView.byteOffset + indexBufferView.byteLength
                );

                meshData.drawMode = primitive.mode;
                meshData.indexType = indexAccessor.componentType;
                meshData.indexCount = static_cast<GLsizei>(indexAccessor.count);
                meshData.indexOffset = static_cast<size_t>(indexAccessor.byteOffset);
            }

            std::shared_ptr<Mesh> mesh = ResourceDirector::CreateMesh(
                    meshData.indexData,
                    meshData.attributes,
                    meshData.drawMode,
                    meshData.indexType,
                    meshData.indexCount,
                    meshData.indexOffset);

            meshes.push_back(mesh);
        }
    }

    void getMeshes(std::vector<std::shared_ptr<Mesh>>& meshes, const std::shared_ptr<tinygltf::Model>& model, tinygltf::Node &node) {
        if ((node.mesh >= 0) && (node.mesh < model->meshes.size()))
            createMeshObjects(meshes, model, model->meshes[node.mesh]);

        for (auto &ch : node.children)
            getMeshes(meshes, model, model->nodes[ch]);
    }

    std::shared_ptr<GameObject> GameDirector::CreateModel(const char* filename) {
        //create GameObject
        auto go = std::make_shared<GameObject>();
        go->AddComponent<Transform>();

        //Load Unique Meshes
        std::vector<std::shared_ptr<Mesh>> meshes;
        auto gltfModel = GLTFLoader::Load(filename);
        const tinygltf::Scene &scene = gltfModel->scenes[gltfModel->defaultScene];
        for (auto &node : scene.nodes) getMeshes(meshes, gltfModel, gltfModel->nodes[node]);

        //Bind Meshes
        auto model = go->AddComponent<Model>();
        glBindVertexArray(model->GetVertexArrayObject());
        for (auto &mesh : meshes) mesh->Bind();
        glBindVertexArray(0);

        model->SetMeshes(meshes);
        return go;
    }


    std::shared_ptr<GameObject> GameDirector::CreateCamera(EGLDisplay m_Display, EGLSurface m_Surface) {
        auto go = std::make_shared<GameObject>();
        go->AddComponent<Camera>(m_Display, m_Surface);
        go->AddComponent<Transform>();
        return go;
    }


    std::shared_ptr<GameObject> GameDirector::CreateLight(glm::vec3 color, float intensity) {
        auto go = std::make_shared<GameObject>();
        go->AddComponent<Light>(color, intensity);
        go->AddComponent<Transform>();
        return go;
    }

}


