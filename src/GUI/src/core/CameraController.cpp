/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraController.cpp
*/

#include "gui.hpp"
#include <cmath>

CameraController::CameraController() : firstMouseMove(true), isLocked(false), lerpSpeed(5.0f) {
    camera.position = (Vector3){ 10.0f, 20.0f, 10.0f };
    camera.target = (Vector3){ 150.0f, 0.0f, 100.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    previousMousePosition = rlModel.GetMousePosition();
    currentCameraPosition = camera.position;
    currentCameraTarget = camera.target;
}

void CameraController::RotateCamera(float yaw, float pitch) {
    currentPitch += pitch;

    if (currentPitch > maxPitch) {
        pitch -= (currentPitch - maxPitch);
        currentPitch = maxPitch;
    }
    if (currentPitch < minPitch) {
        pitch += (minPitch - currentPitch);
        currentPitch = minPitch;
    }

    Vector3 forward = rlModel.Vector3Normalize(rlModel.Vector3Subtract(camera.target, camera.position));
    Matrix rotationMatrix = rlModel.MatrixRotate(camera.up, yaw);
    forward = rlModel.Vector3Transform(forward, rotationMatrix);

    Vector3 right = rlModel.Vector3Normalize(rlModel.Vector3CrossProduct(forward, camera.up));
    rotationMatrix = rlModel.MatrixRotate(right, pitch);
    forward = rlModel.Vector3Transform(forward, rotationMatrix);

    camera.target = rlModel.Vector3Add(camera.position, forward);
}

void CameraController::SmoothUnlockCamera() {
    float lerpFactor = rlModel.GetFrameTime() * lerpSpeed;
    camera.position = rlModel.Vector3Lerp(currentCameraPosition, originalPosition, lerpFactor);
    camera.target = rlModel.Vector3Lerp(currentCameraTarget, originalTarget, lerpFactor);

    currentCameraPosition = camera.position;
    currentCameraTarget = camera.target;
    if (rlModel.Vector3Distance(camera.position, originalPosition) < 0.01f &&
        rlModel.Vector3Distance(camera.target, originalTarget) < 0.01f) {
        isLocked = false;
    }
}

void CameraController::Update() {
     if (isLocked) {
        SmoothUnlockCamera();
        return;
    }

    Vector2 mousePosition = rlModel.GetMousePosition();
    if (firstMouseMove) {
        previousMousePosition = mousePosition;
        firstMouseMove = false;
    }

    Vector2 mouseDelta = { mousePosition.x - previousMousePosition.x, mousePosition.y - previousMousePosition.y };
    previousMousePosition = mousePosition;

    float mouseSensitivity = 0.003f;
    if (rlModel.IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        RotateCamera(-mouseDelta.x * mouseSensitivity, -mouseDelta.y * mouseSensitivity);
    }

    int speedcam = 70;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float keyboardSensitivity = 0.03f;

    if (rlModel.IsKeyDown(KEY_RIGHT)) yaw -= keyboardSensitivity * rlModel.GetFrameTime() * speedcam;
    if (rlModel.IsKeyDown(KEY_LEFT)) yaw += keyboardSensitivity * rlModel.GetFrameTime() * speedcam;
    if (rlModel.IsKeyDown(KEY_UP)) pitch += keyboardSensitivity * rlModel.GetFrameTime() * speedcam;
    if (rlModel.IsKeyDown(KEY_DOWN)) pitch -= keyboardSensitivity * rlModel.GetFrameTime() * speedcam;

    RotateCamera(yaw, pitch);

    Vector3 forward = rlModel.Vector3Normalize(rlModel.Vector3Subtract(camera.target, camera.position));
    Vector3 right = rlModel.Vector3Normalize(rlModel.Vector3CrossProduct(forward, camera.up));

    float deltaTime = rlModel.GetFrameTime();
    int speed = 150;

    Vector3 movement = { 0.0f, 0.0f, 0.0f };
    if (rlModel.IsKeyDown(KEY_LEFT_SHIFT)) speed = 300;
    if (rlModel.IsKeyDown(KEY_W)) movement = rlModel.Vector3Add(movement, rlModel.Vector3Scale(forward, 0.2f * speed * deltaTime));
    if (rlModel.IsKeyDown(KEY_S)) movement = rlModel.Vector3Add(movement, rlModel.Vector3Scale(forward, -0.2f * speed * deltaTime));
    if (rlModel.IsKeyDown(KEY_A)) movement = rlModel.Vector3Add(movement, rlModel.Vector3Scale(right, -0.2f * speed * deltaTime));
    if (rlModel.IsKeyDown(KEY_D)) movement = rlModel.Vector3Add(movement, rlModel.Vector3Scale(right, 0.2f * speed * deltaTime));
    if (rlModel.IsKeyDown(KEY_Q)) movement.y += 0.2f * deltaTime * speed;
    if (rlModel.IsKeyDown(KEY_E)) movement.y -= 0.2f * deltaTime * speed;

    camera.position = rlModel.Vector3Add(camera.position, movement);
    camera.target = rlModel.Vector3Add(camera.target, movement);

    currentCameraPosition = camera.position;
    currentCameraTarget = camera.target;
}

void CameraController::UpdateLockedCamera(const std::shared_ptr<Player>& player) {
    if (!isLocked) return;

    Vector3 playerPosition = player->GetPosition();
    Vector3 offset;

     switch (player->GetOrientation()) {
        case 1: // North
            offset = (Vector3){0.0f, 5.0f, -10.0f};
            break;
        case 2: // East
            offset = (Vector3){-10.0f, 5.0f, 0.0f};
            break;
        case 3: // South
            offset = (Vector3){0.0f, 5.0f, 10.0f};
            break;
        case 4: // West
            offset = (Vector3){10.0f, 5.0f, 0.0f};
            break;
        default:
            offset = (Vector3){0.0f, 5.0f, 10.0f};
            break;
    }

    Vector3 targetPosition = rlModel.Vector3Add(playerPosition, offset);
    Vector3 targetLookAt = playerPosition;

    SmoothMoveCamera(targetPosition, targetLookAt);
}

void CameraController::SmoothMoveCamera(const Vector3& targetPosition, const Vector3& targetLookAt) {
    float lerpFactor = rlModel.GetFrameTime() * lerpSpeed;
    camera.position = rlModel.Vector3Lerp(currentCameraPosition, targetPosition, lerpFactor);
    camera.target = rlModel.Vector3Lerp(currentCameraTarget, targetLookAt, lerpFactor);

    currentCameraPosition = camera.position;
    currentCameraTarget = camera.target;
}

Camera CameraController::GetCamera() const {
    return camera;
}

void CameraController::LockCameraOnPlayer(const std::shared_ptr<Player>& player) {
    isLocked = true;
    UpdateLockedCamera(player);
}

void CameraController::UnlockCamera() {
    isLocked = true;
    SmoothUnlockCamera();
}

void CameraController::SetOriginalCameraPosition(const Vector3& position, const Vector3& target) {
    originalPosition = position;
    originalTarget = target;
    currentCameraPosition = position;
    currentCameraTarget = target;
}