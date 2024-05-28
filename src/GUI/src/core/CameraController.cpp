/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraController.cpp
*/

#include "gui.hpp"
#include <cmath>

// Fonction pour normaliser un vecteur
Vector3 Vector3Normalize(Vector3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length != 0.0f) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
    return v;
}

// Fonction pour soustraire deux vecteurs
Vector3 Vector3Subtract(Vector3 v1, Vector3 v2) {
    return (Vector3){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// Fonction pour calculer le produit vectoriel de deux vecteurs
Vector3 Vector3CrossProduct(Vector3 v1, Vector3 v2) {
    return (Vector3){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

// Fonction pour ajouter deux vecteurs
Vector3 Vector3Add(Vector3 v1, Vector3 v2) {
    return (Vector3){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// Fonction pour multiplier un vecteur par un scalaire
Vector3 Vector3Scale(Vector3 v, float scale) {
    return (Vector3){ v.x * scale, v.y * scale, v.z * scale };
}

CameraController::CameraController() {
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Position de la caméra
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     // Cible initiale de la caméra
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         // Vecteur "up" de la caméra
    camera.fovy = 45.0f;                               // Champ de vision Y de la caméra
    camera.projection = CAMERA_PERSPECTIVE;            // Projection de la caméra
}

void CameraController::Update() {
    // Mettre à jour la caméra avec le mode CAMERA_FREE pour une liberté totale
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);

    // Calculer le vecteur de direction basé sur l'orientation de la caméra
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));

    // Calculer le vecteur de droite de la caméra
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

    // Mouvement de la caméra
    Vector3 movement = { 0.0f, 0.0f, 0.0f };
    if (IsKeyDown(KEY_W)) movement = Vector3Add(movement, Vector3Scale(forward, 0.2f));
    if (IsKeyDown(KEY_S)) movement = Vector3Add(movement, Vector3Scale(forward, -0.2f));
    if (IsKeyDown(KEY_A)) movement = Vector3Add(movement, Vector3Scale(right, -0.2f));
    if (IsKeyDown(KEY_D)) movement = Vector3Add(movement, Vector3Scale(right, 0.2f));
    if (IsKeyDown(KEY_Q)) movement.y += 0.2f;
    if (IsKeyDown(KEY_E)) movement.y -= 0.2f;

    camera.position = Vector3Add(camera.position, movement);
    camera.target = Vector3Add(camera.target, movement);
}

Camera CameraController::GetCamera() const {
    return camera;
}
