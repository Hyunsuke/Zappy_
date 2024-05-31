/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLModel
*/

#ifndef RLMODEL_HPP_
#define RLMODEL_HPP_

#include "raylib.h"
#include <string>

class RLModel {
public:
    RLModel(const std::string& modelPath, const std::string& texturePath);
    ~RLModel();

    void Draw(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint);
    void DrawWires(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint);
    BoundingBox GetBoundingBox() const;
    void SetShader(Shader shader);
    void SetTexture(const std::string& texturePath);

private:
    Model model;
    Shader shader;
};

#endif // RLMODEL_HPP_

