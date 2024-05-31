/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RLRay.cpp
*/

#include "gui.hpp"

Ray RLRay::GetMouseRay(Vector2 mousePosition, Camera camera) {
    return ::GetMouseRay(mousePosition, camera);
}

RayCollision RLRay::GetRayCollisionBox(Ray ray, BoundingBox box) {
    return ::GetRayCollisionBox(ray, box);
}
