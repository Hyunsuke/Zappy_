/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraController.cpp
*/

#include "gui.hpp"
#include <cmath>

CameraController::CameraController() : firstMouseMove(true) {
    camera.position = (Vector3){ 10.0f, 20.0f, 10.0f };
    camera.target = (Vector3){ 150.0f, 0.0f, 100.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    previousMousePosition = GetMousePosition();
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
    // Handle camera rotation with mouse movement
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

    // Handle camera rotation with arrow keys
    float yaw = 0.0f;
    float pitch = 0.0f;
    float keyboardSensitivity = 0.03f;

    if (IsKeyDown(KEY_RIGHT)) yaw -= keyboardSensitivity;
    if (IsKeyDown(KEY_LEFT)) yaw += keyboardSensitivity;
    if (IsKeyDown(KEY_UP)) pitch += keyboardSensitivity;
    if (IsKeyDown(KEY_DOWN)) pitch -= keyboardSensitivity;

    RotateCamera(yaw, pitch);

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    int speed = 1;

    Vector3 movement = { 0.0f, 0.0f, 0.0f };
    if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 5;
    if (IsKeyDown(KEY_W)) movement = Vector3Add(movement, Vector3Scale(forward, 0.2f * speed));
    if (IsKeyDown(KEY_S)) movement = Vector3Add(movement, Vector3Scale(forward, -0.2f * speed));
    if (IsKeyDown(KEY_A)) movement = Vector3Add(movement, Vector3Scale(right, -0.2f * speed));
    if (IsKeyDown(KEY_D)) movement = Vector3Add(movement, Vector3Scale(right, 0.2f * speed));
    if (IsKeyDown(KEY_Q)) movement.y += 0.2f;
    if (IsKeyDown(KEY_E)) movement.y -= 0.2f;

    camera.position = Vector3Add(camera.position, movement);
    camera.target = Vector3Add(camera.target, movement);
}

Camera CameraController::GetCamera() const {
    return camera;
}