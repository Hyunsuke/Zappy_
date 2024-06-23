/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Island;

#include "../Island.hpp"
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "raylib.h"
#include <GL/gl.h>
#include "../../Wrapper/Raylib/RLModel.hpp"

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
        Walk
    };

    Player(int playerNumber, const std::string& teamName, int x, int y, int orientation, int level, const std::string& modelPath, std::shared_ptr<Island> island);
    ~Player();

    void Draw();
    void DrawWires();
    void UpdateAnimation();
    void UpdatePosition();
    void SetPosition(Vector3 position);
    Vector3 GetPosition() const;
    void SetScale(const Vector3& scale);
    void SetRotation(const Vector3& axis, float angleDegrees);
    void SetAnimation(Animation animation);
    void JumpTo(std::shared_ptr<Island> newIsland, float baseDuration);
    void SetIsland(std::shared_ptr<Island> newIsland);
    std::shared_ptr<Island> GetIsland() const;
    int GetPlayerNumber() const;
    void SetPlayerNumber(int playerNumber);
    std::shared_ptr<Model> GetModel();
    void SetOrientation(int orientation);
    int GetOrientation() const;
    int getOBJquantity(std::string objName);
    void setOBJquantity(std::string objName, int quantity);
    int getX() const;
    int getY() const;
    int GetLevel() const;
    void SetLevel(int level);
    std::string GetTeam() const;
    void SetDead();
    bool IsDead() const;
    Vector3 GetScale() const;
    std::shared_ptr<ModelAnimation> GetCurrentAnimation() const;
    int GetCurrentFrame() const;


    void WaitForAnimationEnd(Player::Animation animation);

private:
    std::vector<std::shared_ptr<ModelAnimation>> animations;
    int animCount;
    std::size_t animIndex;
    int animCurrentFrame;
    Vector3 position;
    Vector3 scale;
    Vector3 rotationAxis;
    float rotationAngle = 0.0f;
    std::unordered_map<Animation, std::size_t> animationMap;

    int playerNumber;
    std::string teamName;
    int x;
    int y;
    int orientation;
    int level;
    Camera PlayerCam;

    int food = 0;
    int linemate = 0;
    int deraumere = 0;
    int sibur = 0;
    int mendiane = 0;
    int phiras = 0;
    int thystame = 0;

    std::shared_ptr<Island> island;
    std::shared_ptr<Island> newIsland;

    std::shared_ptr<Model> model;
    ModelLoader modelLoader;

    void UpdateScaleBasedOnLevel();
    void UpdateRotationAngle();

    float animationTime;
    float animationSpeed;

    Vector3 startPos;
    Vector3 endPos;
    float moveStartTime;
    float moveDuration;
    bool isMoving = false;
    bool Dead = false;
    Color teamColor;

    RLModel rlModel;
    static Color GetTeamColor(const std::string& teamName);

    std::vector<Vector3> predefinedPositions;
    void InitializePredefinedPositions();
};

#endif // PLAYER_HPP
