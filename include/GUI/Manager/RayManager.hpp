/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RayManager
*/

#ifndef RAYMANAGER_HPP_
#define RAYMANAGER_HPP_

#include <raylib.h>
#include "../core/Island.hpp"
#include <vector>
#include <memory>

class RayManager {
public:
    RayManager();
    void UpdateRay(Camera camera);
    std::shared_ptr<Island> GetIslandUnderMouse(const std::vector<std::shared_ptr<Island>>& islands);
    std::shared_ptr<Player> GetPlayerUnderMouse(const std::vector<std::shared_ptr<Player>>& players);

private:
    bool CheckRayCollisionModel(Ray ray, const Model& model, const Matrix& transform);
    bool CheckCollisionRayBox(Ray ray, BoundingBox box);
    Ray ray;
};

#endif // RAYMANAGER_HPP_
