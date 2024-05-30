/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** TextureCollector.cpp
*/

#include "gui.hpp"

TextureCollector& TextureCollector::GetInstance() {
    static TextureCollector instance;
    return instance;
}

std::shared_ptr<Texture2D> TextureCollector::LoadTexture(const std::string& filePath) {
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        return it->second;
    }

    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(::LoadTexture(filePath.c_str()));
    textureCache[filePath] = texture;

    return texture;
}

void TextureCollector::UnloadAllTextures() {
    for (auto& entry : textureCache) {
        ::UnloadTexture(*entry.second);
    }
    textureCache.clear();
}

TextureCollector::~TextureCollector() {
    UnloadAllTextures();
}
