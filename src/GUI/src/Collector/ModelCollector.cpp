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

    Model rawModel = rlModel.LoadModel(filePath.c_str());
    if (rawModel.meshCount == 0) {
        throw GameException("Failed to load model: " + filePath);
    }
    std::shared_ptr<Model> model = std::make_shared<Model>(rawModel);
    modelCache[filePath] = model;

    return model;
}

void ModelCollector::UnloadAllModels() {
    for (auto& entry : modelCache) {
        if (entry.second)
            rlModel.UnloadModel(entry.second);
    }
    modelCache.clear();
}

ModelCollector::~ModelCollector() {
    UnloadAllModels();
}
