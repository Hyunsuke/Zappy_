/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ModelCollector
*/

#include "gui.hpp"

ModelCollector& ModelCollector::GetInstance() {
    static ModelCollector instance;
    return instance;
}

std::shared_ptr<Model> ModelCollector::LoadModel(const std::string& filePath) {
    auto it = modelCache.find(filePath);
    if (it != modelCache.end()) {
        return it->second;
    }

    std::shared_ptr<Model> model = std::make_shared<Model>(::LoadModel(filePath.c_str()));
    modelCache[filePath] = model;

    return model;
}

void ModelCollector::UnloadAllModels() {
    for (auto& entry : modelCache) {
        ::UnloadModel(*entry.second);
    }
    modelCache.clear();
}

ModelCollector::~ModelCollector() {
    UnloadAllModels();
}
