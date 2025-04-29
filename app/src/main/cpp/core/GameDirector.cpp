//
// Created by drave on 4/27/2025.
//

#include "GameDirector.h"
#include "components/Model.h"
#include "utilities/GLTFLoader.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace DGEngine {

    void createMesh(std::vector<std::shared_ptr<Mesh>>& meshes, const std::shared_ptr<tinygltf::Model>& model, tinygltf::Mesh& mesh) {
        for (auto& primitive : mesh.primitives) {
            std::vector<Mesh::Attribute> attributes;
            std::shared_ptr<Mesh> m;
            std::map<int, GLuint> vbos; // map bufferView index to VBO

            // 1. Create VBOs first for all bufferViews (only if needed)
            for (size_t i = 0; i < model->bufferViews.size(); ++i) {
                const tinygltf::BufferView& bufferView = model->bufferViews[i];
                if (bufferView.target == 0) {
                    // skip non-vertex/index buffer
                    continue;
                }
                const tinygltf::Buffer& buffer = model->buffers[bufferView.buffer];

                GLuint vbo = 0;
                glGenBuffers(1, &vbo);
                glBindBuffer(bufferView.target, vbo);
                glBufferData(bufferView.target,
                             bufferView.byteLength,
                             &buffer.data.at(0) + bufferView.byteOffset,
                             GL_STATIC_DRAW);

                vbos[i] = vbo;
            }

            // 2. Now handle vertex attributes
            for (auto& attrib : primitive.attributes) {
                const tinygltf::Accessor& accessor = model->accessors[attrib.second];
                const tinygltf::BufferView& bufferView = model->bufferViews[accessor.bufferView];

                if (!m) {
                    // try to create (or Get cached) Mesh
                    m = ResourceDirector::CreateMesh(bufferView.target,
                                                     &model->buffers[bufferView.buffer].data.at(0),
                                                     static_cast<long>(bufferView.byteLength),
                                                     bufferView.byteOffset);
                }

                int size = (accessor.type == TINYGLTF_TYPE_SCALAR) ? 1 : accessor.type;
                int vertexArrayAttribute = -1;
                if (attrib.first == "POSITION") vertexArrayAttribute = 0;
                else if (attrib.first == "NORMAL") vertexArrayAttribute = 1;
                else if (attrib.first == "TEXCOORD_0") vertexArrayAttribute = 2;
                if (vertexArrayAttribute == -1) continue;

                Mesh::Attribute attr = {
                        .vao = vertexArrayAttribute,
                        .size = size,
                        .type = accessor.componentType,
                        .normalized = accessor.normalized,
                        .byteStride = accessor.ByteStride(bufferView),
                        .byteOffset = accessor.byteOffset
                };
                attributes.push_back(attr);


                auto iter = vbos.find(accessor.bufferView);
                if (iter != vbos.end()) {
                    glBindBuffer(GL_ARRAY_BUFFER, iter->second);
                    m->SetVertexBufferObject(iter->second);
                }

                glEnableVertexAttribArray(vertexArrayAttribute);
                glVertexAttribPointer(vertexArrayAttribute,
                                      attr.size,
                                      attr.type,
                                      attr.normalized ? GL_TRUE : GL_FALSE,
                                      attr.byteStride,
                                      (void*)(intptr_t)(attr.byteOffset));
            }

            // 3. Handle EBO (index buffer)
            if (primitive.indices >= 0) {
                const tinygltf::Accessor& indexAccessor = model->accessors[primitive.indices];
                const tinygltf::BufferView& indexBufferView = model->bufferViews[indexAccessor.bufferView];
                const tinygltf::Buffer& indexBuffer = model->buffers[indexBufferView.buffer];

                GLuint ibo = 0;
                glGenBuffers(1, &ibo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             indexBufferView.byteLength,
                             &indexBuffer.data.at(0) + indexBufferView.byteOffset,
                             GL_STATIC_DRAW);

                m->SetIndexBufferObject(ibo);
                m->SetDrawMode(primitive.mode);
                m->SetIndexType(indexAccessor.componentType);
                m->SetIndexCount(static_cast<GLsizei>(indexAccessor.count));
                m->SetIndexOffset(static_cast<size_t>(indexAccessor.byteOffset));

            }

            // 4. Save attributes only once
            m->SetAttributes(attributes);
            m->MarkUploaded();

            // 5. Push mesh into list
            if (m) {
                meshes.push_back(m);
            }
        }
    }

    void getMeshes(std::vector<std::shared_ptr<Mesh>>& meshes, const std::shared_ptr<tinygltf::Model>& model, tinygltf::Node &node) {
        if ((node.mesh >= 0) && (node.mesh < model->meshes.size()))
            createMesh(meshes, model, model->meshes[node.mesh]);

        for (auto &ch : node.children)
            getMeshes(meshes, model, model->nodes[ch]);
    }

    std::shared_ptr<GameObject> GameDirector::CreateModel(const char* filename) {
        auto go = std::make_shared<GameObject>();

        auto model = go->AddComponent<Model>();

        auto gltfModel = GLTFLoader::Load(filename);
        const tinygltf::Scene &scene = gltfModel->scenes[gltfModel->defaultScene];

        glBindVertexArray(model->GetVertexArrayObject());

        std::vector<std::shared_ptr<Mesh>> meshes;
        for (auto &node : scene.nodes)
            getMeshes(meshes, gltfModel, gltfModel->nodes[node]);

        model->SetMeshes(meshes);

        glBindVertexArray(0);

        return go;
    }
}


