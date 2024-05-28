/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ModelLoader.cpp
*/

#include "gui.hpp"

ModelLoader::ModelLoader(const std::string& filePath, const std::vector<std::string>& texturePaths) {
    model = LoadModel(filePath.c_str());

    for (const auto& texturePath : texturePaths) {
        Texture2D texture = LoadTexture(texturePath.c_str());
        textures.push_back(texture);
    }

    // Associer les textures chargées aux matériaux du modèle
    for (int i = 0; i < model.materialCount && i < textures.size(); i++) {
        model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = textures[i];
    }

    std::cout << "Model loaded from " << filePath << " with " << textures.size() << " textures." << std::endl;
}

ModelLoader::~ModelLoader() {
    for (auto& texture : textures) {
        UnloadTexture(texture);
    }
    UnloadModel(model);
}

void ModelLoader::Draw(Vector3 position, float scale, Color tint) {
    DrawModel(model, position, scale, tint);
}