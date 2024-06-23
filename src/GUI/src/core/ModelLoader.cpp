/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ModelLoader.cpp
*/

#include "gui.hpp"

ModelLoader::ModelLoader(const std::string& filePath) {
    model = ModelCollector::GetInstance().LoadModel(filePath);
    shader = {0, 0};
}

ModelLoader::~ModelLoader() {}

void ModelLoader::Draw(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint) {
    if (!model) return;
    for (int i = 0; i < model->materialCount; i++) {
        model->materials[i].shader = shader;
    }
    rlModel.DrawModelEx(model, position, rotationAxis, rotationAngle, (Vector3){scale, scale, scale}, tint);
}

void ModelLoader::DrawWires(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint) {
    rlModel.SetLineWidth(100.0f);
    rlModel.DrawModelWiresEx(model, position, rotationAxis, rotationAngle, (Vector3){scale, scale, scale}, tint);
    rlModel.SetLineWidth(1.0f);
}

void ModelLoader::SetShader(Shader newShader) {
    shader = newShader;
}

void ModelLoader::SetTexture(const std::string& texturePath) {
    std::shared_ptr<Texture2D> texture = TextureCollector::GetInstance().LoadTexture(texturePath);
    for (int i = 0; i < model->materialCount; i++) {
        rlModel.SetMaterialTexture(model->materials[i], MATERIAL_MAP_DIFFUSE, texture);
    }
}

BoundingBox ModelLoader::GetBoundingBox() const {
    BoundingBox bbox = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
    Mesh mesh = model->meshes[0];
    if (mesh.vertexCount > 0) {
        bbox.min = { FLT_MAX, FLT_MAX, FLT_MAX };
        bbox.max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
        for (int i = 0; i < mesh.vertexCount; i++) {
            Vector3 v = { mesh.vertices[i*3 + 0], mesh.vertices[i*3 + 1], mesh.vertices[i*3 + 2] };
            if (v.x < bbox.min.x) bbox.min.x = v.x;
            if (v.y < bbox.min.y) bbox.min.y = v.y;
            if (v.z < bbox.min.z) bbox.min.z = v.z;
            if (v.x > bbox.max.x) bbox.max.x = v.x;
            if (v.y > bbox.max.y) bbox.max.y = v.y;
            if (v.z > bbox.max.z) bbox.max.z = v.z;
        }
    }
    return bbox;
}