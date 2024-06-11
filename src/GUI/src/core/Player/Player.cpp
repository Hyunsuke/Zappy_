/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "gui.hpp"

Player::Player(int playerNumber, const std::string& teamName, int x, int y, int orientation, int level, const std::string& modelPath, std::shared_ptr<Island> island)
    : playerNumber(playerNumber), teamName(teamName), x(x), y(y), orientation(orientation), level(level), island(island) {
    model = ModelCollector::GetInstance().LoadModel(modelPath);
    // std::shared_ptr<ModelAnimation> rawAnimations = AnimationCollector::GetInstance().LoadAnimation(modelPath, &animCount);
    // std::shared_ptr<ModelAnimation> rawAnimations(LoadModelAnimations(modelPath.c_str(), &animCount), [](ModelAnimation* p) { delete[] p; });

    // for (int i = 0; i < animCount; ++i) {
    //     animations.push_back(std::make_shared<ModelAnimation>(rawAnimations.get()[i]));
    // }

    // animIndex = 0;
    // animCurrentFrame = 0;
    // // position = { static_cast<float>(x), 0.0f, static_cast<float>(y) };
    // position = island->GetPosition();

    // // Initialisation du mapping des animations
    // animationMap[Animation::Dance] = 0;
    // animationMap[Animation::Death] = 1;
    // animationMap[Animation::Idle] = 2;
    // animationMap[Animation::Jump] = 3;
    // animationMap[Animation::No] = 4;
    // animationMap[Animation::Punch] = 5;
    // animationMap[Animation::Run] = 6;
    // animationMap[Animation::Sit] = 7;
    // animationMap[Animation::Stand] = 8;
    // animationMap[Animation::ThumbsUp] = 9;
    // animationMap[Animation::Walk] = 10;

    UpdateScaleBasedOnLevel();
}

Player::~Player() {}

void Player::Draw() {
    Vector3 orientationVector;
    switch (orientation) {
        case 1: // North
            orientationVector = {0.0f, 1.0f, 0.0f};
            break;
        case 2: // East
            orientationVector = {1.0f, 0.0f, 0.0f};
            break;
        case 3: // South
            orientationVector = {0.0f, -1.0f, 0.0f};
            break;
        case 4: // West
            orientationVector = {-1.0f, 0.0f, 0.0f};
            break;
        default:
            orientationVector = {0.0f, 1.0f, 0.0f};
            break;
    }
    position = {0, 0, 0};
    std::cout << "Player position: " << position.x << " " << position.y << " " << position.z << std::endl;
    std::cout << "Player orientation: " << orientationVector.x << " " << orientationVector.y << " " << orientationVector.z << std::endl;
    std::cout << "Player rotation angle: " << rotationAngle << std::endl;
    std::cout << "Player scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;
    // DrawModelEx(*model, position, orientationVector, rotationAngle, scale, WHITE);
    DrawModel(*model, position, 10.0f, WHITE);
}

void Player::UpdateAnimation() {
    // if (!animations.empty() && animIndex < animations.size() && animations[animIndex]) {
    //     animCurrentFrame = (animCurrentFrame + 1) % animations[animIndex]->frameCount;
    //     UpdateModelAnimation(*model, *animations[animIndex], animCurrentFrame);
    // }
}

void Player::UpdatePosition() {
    // if (island) {
    //     Vector3 islandPosition = island->GetPosition();
    //     position.y = islandPosition.y;
    // }
}

void Player::SetPosition(Vector3 newPosition) {
    position = newPosition;
}

Vector3 Player::GetPosition() const {
    return position;
}

void Player::SetScale(const Vector3& newScale) {
    scale = newScale;
}

void Player::SetRotation(const Vector3& axis, float angleDegrees) {
    rotationAxis = axis;
    rotationAngle = angleDegrees;
}

void Player::SetAnimation(Animation animation) {
    // if (animationMap.find(animation) != animationMap.end()) {
    //     animIndex = animationMap[animation];
    //     animCurrentFrame = 0;
    // }
}

void Player::UpdateScaleBasedOnLevel() {
    // float baseScale = 1.0f;
    // float scaleFactor = 0.5f + 0.1f * level;
    // scale = {baseScale * scaleFactor, baseScale * scaleFactor, baseScale * scaleFactor};
    scale = {10.0f, 10.0f, 10.0f};
}
