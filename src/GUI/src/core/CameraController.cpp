/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraController.cpp
*/

#include "gui.hpp"

CameraController::CameraController() {
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                              // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
}

void CameraController::Update() {
    // Camera movement controls
    if (IsKeyDown(KEY_W)) camera.position.z -= 0.2f;
    if (IsKeyDown(KEY_S)) camera.position.z += 0.2f;
    if (IsKeyDown(KEY_A)) camera.position.x -= 0.2f;
    if (IsKeyDown(KEY_D)) camera.position.x += 0.2f;
    if (IsKeyDown(KEY_Q)) camera.position.y += 0.2f;
    if (IsKeyDown(KEY_E)) camera.position.y -= 0.2f;

    // Update camera
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
}

Camera CameraController::GetCamera() const {
    return camera;
}