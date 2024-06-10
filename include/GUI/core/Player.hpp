// Player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "raylib.h"

class Player {
public:

    enum class Animation {
        Dance,
        Death,
        Idle,
        Jump,
        No,
        Punch,
        Run,
        Sit,
        Stand,
        ThumbsUp,
        Walk,
        // Ajoutez d'autres animations ici selon vos besoins
    };

    Player(const std::string& modelPath);
    ~Player();

    void Draw();
    void UpdateAnimation();
    void SetPosition(Vector3 position);
    Vector3 GetPosition() const;
    void SetScale(const Vector3& scale);
    void SetRotation(const Vector3& axis, float angleDegrees);
    void SetAnimation(Animation animation);

private:
    std::shared_ptr<Model> model;
    std::vector<std::shared_ptr<ModelAnimation>> animations;
    int animCount;
    unsigned int animIndex;
    unsigned int animCurrentFrame;
    Vector3 position;
    Vector3 scale;
    Vector3 rotationAxis;
    float rotationAngle;

    std::unordered_map<Animation, unsigned int> animationMap;
};

#endif // PLAYER_HPP