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
    if (shader.id != 0) UnloadShader(shader);
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