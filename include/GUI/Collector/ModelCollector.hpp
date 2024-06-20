/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ModelCollector
*/

#ifndef MODEL_COLLECTOR_HPP_
#define MODEL_COLLECTOR_HPP_

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <memory>
#include "../Wrapper/Raylib/RLModel.hpp"

class ModelCollector {
public:
    static ModelCollector& GetInstance();

    std::shared_ptr<Model> LoadModel(const std::string& filePath);
    void UnloadAllModels();

private:
    ModelCollector() = default;
    ~ModelCollector();

    std::unordered_map<std::string, std::shared_ptr<Model>> modelCache;
    RLModel rlModel;
};

#endif // MODEL_COLLECTOR_HPP_

