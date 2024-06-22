/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ModelLoader
*/

#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "raylib.h"
#include <string>
#include <vector>
#include <float.h>
#include "../Collector/ModelCollector.hpp"
#include <GL/gl.h>
#include "../Wrapper/Raylib/RLModel.hpp"

class ModelLoader {
public:
    ModelLoader(const std::string& filePath);
    ~ModelLoader();
    void Draw(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint);
    void DrawWires(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint);
    void SetShader(Shader shader);
    std::shared_ptr<Model> GetModel() const { return model; }
    void SetTexture(const std::string& texturePath);
    Matrix GetTransform() const { return model->transform; }
    BoundingBox GetBoundingBox() const;

private:
    std::shared_ptr<Model> model;
    Shader shader;
    std::vector<Color> objectColors;
    RLModel rlModel;
};

#endif // MODEL_LOADER_H
