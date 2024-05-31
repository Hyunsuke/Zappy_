/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RLRay.hpp
*/

#ifndef RLRAY_HPP_
#define RLRAY_HPP_

#include "raylib.h"

class RLRay {
public:
    static Ray GetMouseRay(Vector2 mousePosition, Camera camera);
    static RayCollision GetRayCollisionBox(Ray ray, BoundingBox box);
};

#endif // RLRAY_HPP_
