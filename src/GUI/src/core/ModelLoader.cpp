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
    // for (int i = 0; i < model.materialCount; i++) {
    //     model.materials[i].shader = shader;
    //     int objectColorLoc = GetShaderLocation(shader, "objectColor");
    //     Color materialColor = model.materials[i].maps[MATERIAL_MAP_DIFFUSE].color;
    //     float objectColorVal[3] = { (float)materialColor.r / 255.0f, (float)materialColor.g / 255.0f, (float)materialColor.b / 255.0f };
    //     SetShaderValue(shader, objectColorLoc, objectColorVal, SHADER_UNIFORM_VEC3);
    // }

    // for 

    DrawModelEx(model, position, rotationAxis, rotationAngle, (Vector3){scale, scale, scale}, tint);
}

void ModelLoader::SetShader(Shader newShader) {
    shader = newShader;
}