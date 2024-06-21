/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** CameraController
*/

#ifndef CAMERACONTROLLER_HPP_
#define CAMERACONTROLLER_HPP_

#include "raylib.h"
#include <memory>
#include "Player/Player.hpp"
#include "../Wrapper/Raylib/RLModel.hpp"

class CameraController {
public:
    CameraController();
    void Update();
    void UpdateLockedCamera(const std::shared_ptr<Player>& player);
    Camera GetCamera() const;
    void LockCameraOnPlayer(const std::shared_ptr<Player>& player);
    void UnlockCamera();
    void SetOriginalCameraPosition(const Vector3& position, const Vector3& target);
    void SmoothUnlockCamera();

private:
    void RotateCamera(float yaw, float pitch);

    Camera camera;
    bool firstMouseMove;
    Vector2 previousMousePosition;
    bool isLocked;

    Vector3 originalPosition;
    Vector3 originalTarget;

    Vector3 currentCameraPosition;
    Vector3 currentCameraTarget;

    float lerpSpeed;

    void SmoothMoveCamera(const Vector3& targetPosition, const Vector3& targetLookAt);
    RLModel rlModel;
    float maxPitch = 1.30f;
    float minPitch = -1.30f;
    float currentPitch = 0.0f;
};

#endif /* !CAMERACONTROLLER_HPP_ */