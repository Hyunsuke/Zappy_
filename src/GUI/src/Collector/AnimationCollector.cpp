// AnimationCollector.cpp

#include "gui.hpp"

AnimationCollector& AnimationCollector::GetInstance() {
    static AnimationCollector instance;
    return instance;
}

std::shared_ptr<ModelAnimation> AnimationCollector::LoadAnimation(const std::string& filePath, int* animCount) {
    auto it = animationCache.find(filePath);
    if (it != animationCache.end()) {
        *animCount = animCountCache[filePath];
        return it->second;
    }

    ModelAnimation* rawAnimations = ::LoadModelAnimations(filePath.c_str(), animCount);
    if (*animCount == 0) {
        throw GameException("Failed to load animations: " + filePath);
    }

    int animCountValue = *animCount;
    std::shared_ptr<ModelAnimation> animations(rawAnimations, [animCountValue](ModelAnimation* anims) {
        ::UnloadModelAnimations(anims, animCountValue);
    });

    animationCache[filePath] = animations;
    animCountCache[filePath] = *animCount;

    return animations;
}

void AnimationCollector::UnloadAllAnimations() {
    animationCache.clear();
    animCountCache.clear();
}

AnimationCollector::~AnimationCollector() {
    UnloadAllAnimations();
}
