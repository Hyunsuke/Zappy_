/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RLModel.cpp
*/

#include "gui.hpp"

Model RLModel::LoadModel(const std::string& filePath) {
    return ::LoadModel(filePath.c_str());
}

void RLModel::UnloadModel(Model& model) {
    ::UnloadModel(model);
}

Texture2D RLModel::LoadTexture(const std::string& filePath) {
    return ::LoadTexture(filePath.c_str());
}

void RLModel::UnloadTexture(Texture2D& texture) {
    ::UnloadTexture(texture);
}

void RLModel::DrawModelEx(const Model& model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
    ::DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

void RLModel::SetLineWidth(float width) {
    ::glLineWidth(width);
}

void RLModel::DrawModelWiresEx(const Model& model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
    ::DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

float RLModel::GetFrameTime() {
    return ::GetFrameTime();
}

double RLModel::GetTime() {
    return ::GetTime();
}

void RLModel::UpdateModelAnimation(Model& model, ModelAnimation& anim, int frame) {
    ::UpdateModelAnimation(model, anim, frame);
}

Vector3 RLModel::Vector3Lerp(Vector3 start, Vector3 end, float amount) {
    return ::Vector3Lerp(start, end, amount);
}

Vector3 RLModel::Vector3Add(Vector3 v1, Vector3 v2) {
    return ::Vector3Add(v1, v2);
}

Vector3 RLModel::Vector3Normalize(Vector3 v) {
    return ::Vector3Normalize(v);
}

Vector3 RLModel::Vector3Subtract(Vector3 v1, Vector3 v2) {
    return ::Vector3Subtract(v1, v2);
}

float RLModel::Vector3DotProduct(Vector3 v1, Vector3 v2) {
    return ::Vector3DotProduct(v1, v2);
}

Matrix RLModel::MatrixRotate(Vector3 axis, float angle) {
    return ::MatrixRotate(axis, angle);
}

Vector3 RLModel::Vector3Transform(Vector3 v, Matrix mat) {
    return ::Vector3Transform(v, mat);
}

Vector3 RLModel::Vector3CrossProduct(Vector3 v1, Vector3 v2) {
    return ::Vector3CrossProduct(v1, v2);
}

Vector3 RLModel::Vector3Scale(Vector3 v, float scale) {
    return ::Vector3Scale(v, scale);
}

Vector2 RLModel::GetMousePosition() {
    return ::GetMousePosition();
}

bool RLModel::IsMouseButtonDown(int button) {
    return ::IsMouseButtonDown(button);
}

bool RLModel::IsMouseButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

bool RLModel::IsKeyDown(int key) {
    return ::IsKeyDown(key);
}


void RLModel::SetMaterialTexture(Material& material, int mapType, Texture2D& texture) {
    ::SetMaterialTexture(&material, mapType, texture);
}

BoundingBox RLModel::GetModelBoundingBox(const Model& model) {
    return ::GetModelBoundingBox(model);
}

Matrix RLModel::MatrixTranslate(float x, float y, float z) {
    return ::MatrixTranslate(x, y, z);
}

Matrix RLModel::MatrixMultiply(Matrix left, Matrix right) {
    return ::MatrixMultiply(left, right);
}

Matrix RLModel::MatrixScale(float x, float y, float z) {
    return ::MatrixScale(x, y, z);
}

Ray RLModel::GetMouseRay(Vector2 mousePosition, Camera camera) {
    return ::GetMouseRay(mousePosition, camera);
}

float RLModel::Vector3Distance(Vector3 v1, Vector3 v2) {
    return ::Vector3Distance(v1, v2);
}