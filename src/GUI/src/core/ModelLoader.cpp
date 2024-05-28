/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ModelLoader.cpp
*/

#include "gui.hpp"

ModelLoader::ModelLoader(const std::string& filePath) {
    model = LoadModel(filePath.c_str());
    std::cout << "Model loaded from " << filePath << std::endl;
}

ModelLoader::~ModelLoader() {
    UnloadModel(model);
}

void ModelLoader::Draw(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint) {
    DrawModelEx(model, position, rotationAxis, rotationAngle, (Vector3){scale, scale, scale}, tint);
}