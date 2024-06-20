/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLAnimation
*/

#ifndef RLANIMATION_HPP_
#define RLANIMATION_HPP_

#include <raylib.h>
#include <string>
#include <memory>

class RLAnimation {
public:
    static ModelAnimation* LoadModelAnimations(const std::string& filePath, int* animCount);
    static void UnloadModelAnimations(ModelAnimation* animations, int animCount);
};

#endif /* !RLANIMATION_HPP_ */
