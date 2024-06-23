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
#include "../Wrapper/Raylib/RLModel.hpp"

class RayManager {
public:
    RayManager();
    void UpdateRay(Camera camera);
    std::shared_ptr<Island> GetIslandUnderMouse(const std::vector<std::shared_ptr<Island>>& islands);
    std::shared_ptr<Player> GetPlayerUnderMouse(const std::vector<std::shared_ptr<Player>>& players);

private:
    bool CheckRayCollisionModel(Ray ray, std::shared_ptr<Model> model, const Matrix& transform);
    bool CheckCollisionRayBox(Ray ray, BoundingBox box);
    bool CheckCollisionRayTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, std::shared_ptr<Vector3> outCollisionPoint);
    Ray ray;
    RLModel rlModel;
};

#endif // RAYMANAGER_HPP_
