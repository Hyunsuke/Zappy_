/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** TextureCollector.hpp
*/

#ifndef TEXTURE_COLLECTOR_HPP_
#define TEXTURE_COLLECTOR_HPP_

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <memory>
#include "../Collector/TextureCollector.hpp"
#include "../Wrapper/Raylib/RLModel.hpp"

class TextureCollector {
public:
    static TextureCollector& GetInstance();

    std::shared_ptr<Texture2D> LoadTexture(const std::string& filePath);
    void UnloadAllTextures();

private:
    TextureCollector() = default;
    ~TextureCollector();

    std::unordered_map<std::string, std::shared_ptr<Texture2D>> textureCache;
    RLModel rlModel;
};

#endif // TEXTURE_COLLECTOR_HPP_
