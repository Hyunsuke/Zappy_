/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "gui.hpp"

Player::Player(int playerNumber, const std::string& teamName, int x, int y, int orientation, int level, const std::string& modelPath, std::shared_ptr<Island> island)
    : playerNumber(playerNumber),
        teamName(teamName),
        x(x),
        y(y),
        orientation(orientation),
        level(level),
        island(island),
        modelLoader(modelPath) {

    std::shared_ptr<ModelAnimation> rawAnimations = AnimationCollector::GetInstance().LoadAnimation(modelPath, &animCount);

    for (int i = 0; i < animCount; ++i) {
        animations.push_back(std::make_shared<ModelAnimation>(rawAnimations.get()[i]));
    }

    animIndex = 0;
    animCurrentFrame = 0;
    rotationAxis = {0.0f, 1.0f, 0.0f};
    position = {island->GetPosition().x, island->GetPosition().y, island->GetPosition().z };

    animationMap[Animation::Dance] = 0;
    animationMap[Animation::Death] = 1;
    animationMap[Animation::Idle] = 2;
    animationMap[Animation::Jump] = 3;
    animationMap[Animation::No] = 4;
    animationMap[Animation::Punch] = 5;
    animationMap[Animation::Run] = 6;
    animationMap[Animation::Sit] = 7;
    animationMap[Animation::Stand] = 8;
    animationMap[Animation::ThumbsUp] = 9;
    animationMap[Animation::Walk] = 10;

    UpdateScaleBasedOnLevel();
    SetAnimation(Animation::Idle);
    UpdateRotationAngle();
}

Player::~Player() {}

void Player::Draw() {
    model = modelLoader.GetModel();
    DrawModelEx(*model, position, rotationAxis, rotationAngle, scale, WHITE);
}

void Player::DrawWires() {
    glLineWidth(5.0f);
    model = modelLoader.GetModel();
    DrawModelWiresEx(*model, position, rotationAxis, rotationAngle, scale, MAROON);
    glLineWidth(1.0f);
}

void Player::UpdateAnimation() {
    if (!animations.empty() && animIndex < animations.size() && animations[animIndex]) {
        animCurrentFrame = (animCurrentFrame + 1) % animations[animIndex]->frameCount;
        model = modelLoader.GetModel();
        UpdateModelAnimation(*model, *animations[animIndex], animCurrentFrame);
    }
}

void Player::UpdatePosition() {
    if (island) {
        Vector3 islandPosition = island->GetPosition();
        position.y = islandPosition.y + 0.5f;
    }
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

std::shared_ptr<Model> Player::GetModel() const {
    return model;
}

void Player::SetRotation(const Vector3& axis, float angleDegrees) {
    rotationAxis = axis;
    rotationAngle = angleDegrees;
}

void Player::SetAnimation(Animation animation) {
    if (animationMap.find(animation) != animationMap.end()) {
        animIndex = animationMap[animation];
        animCurrentFrame = 0;
    }
}

void Player::UpdateScaleBasedOnLevel() {
    float baseScale = 1.0f;
    float scaleFactor = 0.5f + 0.1f * level;
    scale = {baseScale * scaleFactor, baseScale * scaleFactor, baseScale * scaleFactor};
}

void Player::SetOrientation(int orientation) {
    this->orientation = orientation;
    UpdateRotationAngle();
}

void Player::UpdateRotationAngle() {
    switch (orientation) {
        case 1: // North
            rotationAngle = 0.0f;
            break;
        case 2: // East
            rotationAngle = 90.0f;
            break;
        case 3: // South
            rotationAngle = 180.0f;
            break;
        case 4: // West
            rotationAngle = -90.0f;
            break;
        default:
            rotationAngle = 0.0f;
            break;
    }
}

void Player::SetIsland(std::shared_ptr<Island> newIsland) {
    island = newIsland;
}

int Player::GetPlayerNumber() const {
    return playerNumber;
}

void Player::JumpTo(int newX, int newY, std::shared_ptr<Island> newIsland, float duration) {
    Vector3 startPos = position;
    Vector3 endPos = {newX * 15.0f, position.y, newY * 15.0f};

    SetAnimation(Animation::Jump);
    int totalFrames = animations[animIndex]->frameCount;
    float frameDuration = duration / totalFrames;

    float startTime = GetTime();
    float endTime = startTime + duration;
    float t = 0.0f;

    while (t < 1.0f) {
        float currentTime = GetTime();
        t = (currentTime - startTime) / (endTime - startTime);
        Vector3 newPos = Vector3Lerp(startPos, endPos, t);
        SetPosition(newPos);
        // UpdateAnimation();
        // Draw();
        // Ensure this loop allows rendering the rest of the scene, not blocking
    }
    this->x = newIsland->GetX();
    this->y = newIsland->GetY();
    SetIsland(newIsland);
}

int Player::getOBJquantity(std::string objName)
{
    if (objName == "food")
        return food;
    if (objName == "linemate")
        return linemate;
    if (objName == "deraumere")
        return deraumere;
    if (objName == "sibur")
        return sibur;
    if (objName == "mendiane")
        return mendiane;
    if (objName == "phiras")
        return phiras;
    if (objName == "thystame")
        return thystame;
    return 0;
}

int Player::getX() const
{
    return x;
}

int Player::getY() const
{
    return y;
}

int Player::GetLevel() const
{
    return level;
}


std::string Player::GetTeam() const
{
    return teamName;
}