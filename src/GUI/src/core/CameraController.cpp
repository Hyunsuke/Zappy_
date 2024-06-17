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
    previousMousePosition = GetMousePosition();
    currentCameraPosition = camera.position;
    currentCameraTarget = camera.target;
}

void CameraController::RotateCamera(float yaw, float pitch) {
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Matrix rotationMatrix = MatrixRotate(camera.up, yaw);
    forward = Vector3Transform(forward, rotationMatrix);

    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    rotationMatrix = MatrixRotate(right, pitch);
    forward = Vector3Transform(forward, rotationMatrix);

    camera.target = Vector3Add(camera.position, forward);
}

void CameraController::Update() {
    if (isLocked) return;

    Vector2 mousePosition = GetMousePosition();
    if (firstMouseMove) {
        previousMousePosition = mousePosition;
        firstMouseMove = false;
    }

    Vector2 mouseDelta = { mousePosition.x - previousMousePosition.x, mousePosition.y - previousMousePosition.y };
    previousMousePosition = mousePosition;

    float mouseSensitivity = 0.003f;
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        RotateCamera(-mouseDelta.x * mouseSensitivity, -mouseDelta.y * mouseSensitivity);
    }

    int speedcam = 70;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float keyboardSensitivity = 0.03f;

    if (IsKeyDown(KEY_RIGHT)) yaw -= keyboardSensitivity * GetFrameTime() * speedcam;
    if (IsKeyDown(KEY_LEFT)) yaw += keyboardSensitivity * GetFrameTime() * speedcam;
    if (IsKeyDown(KEY_UP)) pitch += keyboardSensitivity * GetFrameTime() * speedcam;
    if (IsKeyDown(KEY_DOWN)) pitch -= keyboardSensitivity * GetFrameTime() * speedcam;

    RotateCamera(yaw, pitch);

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

    float deltaTime = GetFrameTime();
    int speed = 150;

    Vector3 movement = { 0.0f, 0.0f, 0.0f };
    if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 300;
    if (IsKeyDown(KEY_W)) movement = Vector3Add(movement, Vector3Scale(forward, 0.2f * speed * deltaTime));
    if (IsKeyDown(KEY_S)) movement = Vector3Add(movement, Vector3Scale(forward, -0.2f * speed * deltaTime));
    if (IsKeyDown(KEY_A)) movement = Vector3Add(movement, Vector3Scale(right, -0.2f * speed * deltaTime));
    if (IsKeyDown(KEY_D)) movement = Vector3Add(movement, Vector3Scale(right, 0.2f * speed * deltaTime));
    if (IsKeyDown(KEY_Q)) movement.y += 0.2f * deltaTime * speed;
    if (IsKeyDown(KEY_E)) movement.y -= 0.2f * deltaTime * speed;

    camera.position = Vector3Add(camera.position, movement);
    camera.target = Vector3Add(camera.target, movement);

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

    Vector3 targetPosition = Vector3Add(playerPosition, offset);
    Vector3 targetLookAt = playerPosition;

    SmoothMoveCamera(targetPosition, targetLookAt);
}

void CameraController::SmoothMoveCamera(const Vector3& targetPosition, const Vector3& targetLookAt) {
    float lerpFactor = GetFrameTime() * lerpSpeed;
    camera.position = Vector3Lerp(currentCameraPosition, targetPosition, lerpFactor);
    camera.target = Vector3Lerp(currentCameraTarget, targetLookAt, lerpFactor);

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
    isLocked = false;
    camera.position = originalPosition;
    camera.target = originalTarget;
    currentCameraPosition = camera.position;
    currentCameraTarget = camera.target;
}

void CameraController::SetOriginalCameraPosition(const Vector3& position, const Vector3& target) {
    originalPosition = position;
    originalTarget = target;
    currentCameraPosition = position;
    currentCameraTarget = target;
}