/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AnimationCollector
*/

#ifndef ANIMATIONCOLLECTOR_HPP
#define ANIMATIONCOLLECTOR_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "raylib.h"
#include "../Wrapper/Raylib/RLAnimation.hpp"

class AnimationCollector {
public:
    static AnimationCollector& GetInstance();

    std::shared_ptr<ModelAnimation> LoadAnimation(const std::string& filePath, int* animCount);
    void UnloadAllAnimations();

private:
    AnimationCollector() = default;
    ~AnimationCollector();
    AnimationCollector(const AnimationCollector&) = delete;
    AnimationCollector& operator=(const AnimationCollector&) = delete;

    std::unordered_map<std::string, std::shared_ptr<ModelAnimation>> animationCache;
    std::unordered_map<std::string, int> animCountCache;
    RLAnimation rlAnimation;
};

#endif // ANIMATIONCOLLECTOR_HPP
