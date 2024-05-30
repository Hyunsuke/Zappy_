/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ModelLoader.cpp
*/

#include "gui.hpp"

ModelLoader::ModelLoader(const std::string& filePath) {
    model = LoadModel(filePath.c_str());
    shader = {0, 0};

    std::cout << "Model loaded from " << filePath << std::endl;
}

ModelLoader::~ModelLoader() {
    UnloadModel(model);
    // if (shader.id != 0) UnloadShader(shader);
}

void ModelLoader::Draw(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint) {
    for (int i = 0; i < model.materialCount; i++) {
        model.materials[i].shader = shader;
    }
    DrawModelEx(model, position, rotationAxis, rotationAngle, (Vector3){scale, scale, scale}, tint);
}

void ModelLoader::SetShader(Shader newShader) {
    shader = newShader;
}

void ModelLoader::SetTexture(const std::string& texturePath) {
    Texture2D texture = LoadTexture(texturePath.c_str());
    for (int i = 0; i < model.materialCount; i++) {
        SetMaterialTexture(&model.materials[i], MATERIAL_MAP_DIFFUSE, texture);
    }
}

BoundingBox ModelLoader::GetBoundingBox() const {
    BoundingBox bbox = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
    Mesh mesh = model.meshes[0];
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