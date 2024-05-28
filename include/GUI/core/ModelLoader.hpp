/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ModelLoader
*/

#ifndef MODELLOADER_HPP_
#define MODELLOADER_HPP_

#include "raylib.h"
#include <string>
#include <vector>

class ModelLoader {
public:
    ModelLoader(const std::string& filePath);
    ~ModelLoader();
    void Draw(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint);

private:
    Model model;
    std::vector<Texture2D> textures;
};

#endif /* !MODELLOADER_HPP_ */
