/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLAnimation
*/

#include "gui.hpp"

ModelAnimation* RLAnimation::LoadModelAnimations(const std::string& filePath, int* animCount) {
    return ::LoadModelAnimations(filePath.c_str(), animCount);
}

void RLAnimation::UnloadModelAnimations(ModelAnimation* animations, int animCount) {
    ::UnloadModelAnimations(animations, animCount);
}