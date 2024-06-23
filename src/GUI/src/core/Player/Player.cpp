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
        modelLoader(modelPath),
        animationTime(0.0f),
        animationSpeed(60.0f) {

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

    if (teamName == "menu")
        teamColor = WHITE;
    else
        teamColor = GetTeamColor(teamName);

    InitializePredefinedPositions();
    UpdateScaleBasedOnLevel();
    SetAnimation(Animation::Idle);
    UpdateRotationAngle();

    if (playerNumber < static_cast<int>(predefinedPositions.size())) {
        Vector3 islandPos = island->GetPosition();
        position = Vector3Add(islandPos, predefinedPositions[playerNumber]);
    } else {
        int randomIndex = rand() % static_cast<int>(predefinedPositions.size());
        Vector3 islandPos = island->GetPosition();
        position = Vector3Add(islandPos, predefinedPositions[randomIndex]);
    }
}

void Player::InitializePredefinedPositions() {
    float radius = 2.0f;
    predefinedPositions = {
        {0.0f, 0.0f, radius},
        {radius * std::cos(PI / 6), 0.0f, radius * std::sin(PI / 6)},
        {radius * std::cos(PI / 3), 0.0f, radius * std::sin(PI / 3)},
        {radius, 0.0f, 0.0f},
        {radius * std::cos(2 * PI / 3), 0.0f, radius * std::sin(2 * PI / 3)},
        {radius * std::cos(5 * PI / 6), 0.0f, radius * std::sin(5 * PI / 6)},
        {0.0f, 0.0f, -radius},
        {-radius * std::cos(PI / 6), 0.0f, -radius * std::sin(PI / 6)},
        {-radius * std::cos(PI / 3), 0.0f, -radius * std::sin(PI / 3)},
        {-radius, 0.0f, 0.0f},
        {-radius * std::cos(2 * PI / 3), 0.0f, -radius * std::sin(2 * PI / 3)},
        {-radius * std::cos(5 * PI / 6), 0.0f, -radius * std::sin(5 * PI / 6)}
    };
}


Player::~Player() {}

void Player::Draw() {
    model = modelLoader.GetModel();
    rlModel.DrawModelEx(model, position, rotationAxis, rotationAngle, scale, teamColor);
}


void Player::DrawWires() {
    rlModel.SetLineWidth(1.0f);
    model = modelLoader.GetModel();
    rlModel.DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, WHITE);
    rlModel.SetLineWidth(1.0f);
}

void Player::UpdateAnimation() {
    if (!animations.empty() && animIndex < animations.size() && animations[animIndex] && Dead == false) {
        float deltaTime = rlModel.GetFrameTime();
        animationTime += deltaTime;

        int framesToAdvance = static_cast<int>(animationTime * animationSpeed);

        if (Dead && animIndex == animationMap[Animation::Death]) {
            animCurrentFrame = std::min(animCurrentFrame + framesToAdvance, animations[animIndex]->frameCount - 1);
        } else {
            animCurrentFrame = (animCurrentFrame + framesToAdvance) % animations[animIndex]->frameCount;
        }

        animationTime -= framesToAdvance / animationSpeed;

        model = modelLoader.GetModel();
        rlModel.UpdateModelAnimation(model, animations[animIndex], animCurrentFrame);
    }
}

void Player::WaitForAnimationEnd(Player::Animation animation) {
    std::thread([this, animation]() {
        int totalFrames = animations[animIndex]->frameCount;
        float frameDuration = animations[animIndex]->frameCount / 60.0f;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(frameDuration * 1000 * totalFrames)));
        SetAnimation(animation);
    }).detach();
}

void Player::UpdatePosition() {
    if (isMoving) {
        float currentTime = rlModel.GetTime();
        float t = (currentTime - moveStartTime) / moveDuration;

        if (t >= 1.0f) {
            t = 1.0f;
            isMoving = false;
            SetAnimation(Animation::Idle);

            this->x = newIsland->GetX();
            this->y = newIsland->GetY();
            SetIsland(newIsland);

        }

        Vector3 newPos = rlModel.Vector3Lerp(startPos, endPos, t);
        SetPosition(newPos);
    } else if (island) {
        Vector3 islandPosition = island->GetPosition();
        position.y = islandPosition.y + 0.5f;
    }
}

void Player::JumpTo(std::shared_ptr<Island> newIsland, float baseDuration) {
    startPos = position;
    endPos = newIsland->GetPosition();

    moveDuration = baseDuration;
    moveStartTime = rlModel.GetTime();
    isMoving = true;

    SetAnimation(Animation::Jump);

    this->newIsland.reset();
    this->newIsland = newIsland;

    if (playerNumber < static_cast<int>(predefinedPositions.size())) {
        Vector3 islandPos = newIsland->GetPosition();
        endPos = Vector3Add(islandPos, predefinedPositions[playerNumber]);
    } else {
        int randomIndex = rand() % static_cast<int>(predefinedPositions.size());
        Vector3 islandPos = newIsland->GetPosition();
        endPos = Vector3Add(islandPos, predefinedPositions[randomIndex]);
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

std::shared_ptr<Model> Player::GetModel() {
    model = modelLoader.GetModel();
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
        animationTime = 0.0f;
    }
}

void Player::UpdateScaleBasedOnLevel() {
    float baseScale = 0.7f;
    float scaleFactor = 0.5f + 0.1f * level;
    scale = {baseScale * scaleFactor, baseScale * scaleFactor, baseScale * scaleFactor};
}

void Player::SetOrientation(int orientation) {
    this->orientation = orientation;
    UpdateRotationAngle();
}

int Player::GetOrientation() const {
    return orientation;
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

std::shared_ptr<Island> Player::GetIsland() const {
    return island;
}

int Player::GetPlayerNumber() const {
    return playerNumber;
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

void Player::setOBJquantity(std::string objName, int quantity)
{
    if (objName == "food")
        food = quantity;
    if (objName == "linemate")
        linemate = quantity;
    if (objName == "deraumere")
        deraumere = quantity;
    if (objName == "sibur")
        sibur = quantity;
    if (objName == "mendiane")
        mendiane = quantity;
    if (objName == "phiras")
        phiras = quantity;
    if (objName == "thystame")
        thystame = quantity;
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

void Player::SetLevel(int level)
{
    this->level = level;
    UpdateScaleBasedOnLevel();
}

std::string Player::GetTeam() const
{
    return teamName;
}

void Player::SetDead() {
    SetAnimation(Animation::Death);
    // std::thread([this]() {
    //     int totalFrames = animations[animIndex]->frameCount;
    //     float frameDuration = animations[animIndex]->frameCount / 60.0f;
    //     std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(frameDuration * 1000 * totalFrames)));
    //     Dead = true;
    // }).detach();
}

bool Player::IsDead() const {
    return Dead;
}

void Player::SetPlayerNumber(int playerNumber)
{
    this->playerNumber = playerNumber;
}

Vector3 Player::GetScale() const
{
    return scale;
}

std::shared_ptr<ModelAnimation> Player::GetCurrentAnimation() const {
    if (animIndex < animations.size()) {
        return animations[animIndex];
    }
    return nullptr;
}

int Player::GetCurrentFrame() const {
    return animCurrentFrame;
}

std::vector<Color> GetPredefinedColors() {
    std::vector<Color> predefinedColors = {
        { 255, 0, 0, 255 },   // Red
        { 0, 255, 0, 255 },   // Green
        { 0, 0, 255, 255 },   // Blue
        { 255, 255, 0, 255 }, // Yellow
        { 255, 0, 255, 255 }, // Magenta
        { 0, 255, 255, 255 }, // Cyan
        { 255, 165, 0, 255 }, // Orange
        { 128, 0, 128, 255 }  // Violet
    };
    return predefinedColors;
}

Color Player::GetTeamColor(const std::string& teamName) {
    std::hash<std::string> hashFn;
    std::size_t hash = hashFn(teamName);
    Color color = GetPredefinedColors()[hash % GetPredefinedColors().size()];

    return color;
}