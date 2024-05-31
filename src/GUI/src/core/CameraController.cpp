/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraController.cpp
*/

#include "gui.hpp"
#include <cmath>

CameraController::CameraController() {
    camera.position = (Vector3){ 10.0f, 20.0f, 10.0f };
    camera.target = (Vector3){ 150.0f, 0.0f, 100.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void CameraController::Update() {
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    int speed = 1;

    Vector3 movement = { 0.0f, 0.0f, 0.0f };
    if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 5;
    if (IsKeyDown(KEY_W)) movement = Vector3Add(movement, Vector3Scale(forward, 0.2f * speed));
    if (IsKeyDown(KEY_S)) movement = Vector3Add(movement, Vector3Scale(forward, -0.2f * speed));
    if (IsKeyDown(KEY_A)) movement = Vector3Add(movement, Vector3Scale(right, -0.2f * speed));
    if (IsKeyDown(KEY_D)) movement = Vector3Add(movement, Vector3Scale(right, 0.2f * speed));
    if (IsKeyDown(KEY_Q)) {
        camera.up.x = 0.0f;
        camera.up.y = 1.0f;
        camera.up.z = 0.0f;
        movement.y += 0.2f;
    }
    if (IsKeyDown(KEY_E)) {
        camera.up.x = 0.0f;
        camera.up.y = 1.0f;
        camera.up.z = 0.0f;
        movement.y -= 0.2f;
    }


    camera.position = Vector3Add(camera.position, movement);
    camera.target = Vector3Add(camera.target, movement);
}

Camera CameraController::GetCamera() const {
    return camera;
}
