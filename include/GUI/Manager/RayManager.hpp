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

private:
    Ray ray;
};

#endif // RAYMANAGER_HPP_
