#include "gui.hpp"

Player::Player(const std::string& modelPath) {
    model = ModelCollector::GetInstance().LoadModel(modelPath.c_str());
    std::shared_ptr<ModelAnimation> rawAnimations = AnimationCollector::GetInstance().LoadAnimation(modelPath.c_str(), &animCount);

    // Convertir les animations en vector de shared_ptr
    for (int i = 0; i < animCount; ++i) {
        animations.push_back(std::make_shared<ModelAnimation>(rawAnimations.get()[i]));
    }

    animIndex = 0;
    animCurrentFrame = 0;
    position = { 0.0f, 0.0f, 0.0f };

    // Initialisation du mapping des animations
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
    // Ajoutez d'autres animations ici selon vos besoins
}

Player::~Player() {
    // La désallocation se fait automatiquement grâce aux shared_ptr
}

void Player::Draw() {
    DrawModel(*model, position, 1.0f, WHITE);
}

void Player::UpdateAnimation() {
    if (!animations.empty() && animIndex < animations.size() && animations[animIndex]) {
        animCurrentFrame = (animCurrentFrame + 1) % animations[animIndex]->frameCount;
        UpdateModelAnimation(*model, *animations[animIndex], animCurrentFrame);
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

void Player::SetRotation(const Vector3& axis, float angleDegrees) {
    rotationAxis = axis;
    rotationAngle = angleDegrees;
}

void Player::SetAnimation(Animation animation) {
    if (animationMap.find(animation) != animationMap.end()) {
        animIndex = animationMap[animation];
        animCurrentFrame = 0; // Réinitialiser le cadre actuel pour commencer l'animation depuis le début
    }
}