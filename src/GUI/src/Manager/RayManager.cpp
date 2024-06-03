/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RayManager
*/

#include "gui.hpp"

RayManager::RayManager() {}

void RayManager::UpdateRay(Camera camera) {
    ray = GetMouseRay(GetMousePosition(), camera);
}

std::shared_ptr<Island> RayManager::GetIslandUnderMouse(const std::vector<std::shared_ptr<Island>>& islands) {
    for (auto& island : islands) {
        BoundingBox transformedBBox;
        transformedBBox.min = Vector3Add(Vector3Scale(island->GetBoundingBox().min, island->GetScale()), island->GetPosition());
        transformedBBox.max = Vector3Add(Vector3Scale(island->GetBoundingBox().max, island->GetScale()), island->GetPosition());

        RayCollision collision = GetRayCollisionBox(ray, transformedBBox);
        if (collision.hit) {
            return island;
        }
    }
    return nullptr;
}

