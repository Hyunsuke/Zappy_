/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Object3D.cpp
*/

#include "gui.hpp"

Object3D::Object3D(const Vector3& position, const std::string& modelPath, const std::string& texturePath, float scale, Vector3 rotationAxis, float rotationAngle)
    : position(position), modelLoader(modelPath), scale(scale), rotationAxis(rotationAxis), rotationAngle(rotationAngle) {
    modelLoader.SetTexture(texturePath);
}

Object3D::~Object3D() {}

void Object3D::Draw() {
    modelLoader.Draw(position, scale, rotationAxis, rotationAngle, WHITE);
}

void Object3D::DrawWires() {
    modelLoader.DrawWires(position, scale, rotationAxis, rotationAngle, WHITE);
}

void Object3D::Move(Vector3 newPosition) {
    position = newPosition;
}

void Object3D::SetScale(float scale) {
    this->scale = scale;
}

float Object3D::GetScale() const {
    return scale;
}

void Object3D::SetRotation(Vector3 rotationAxis, float rotationAngle) {
    this->rotationAxis = rotationAxis;
    this->rotationAngle = rotationAngle;
}

Vector3 Object3D::GetRotationAxis() const {
    return rotationAxis;
}

float Object3D::GetRotationAngle() const {
    return rotationAngle;
}

Vector3 Object3D::GetPosition() const {
    return position;
}

void Object3D::SetShader(const Shader& shader) {
    this->shader = shader;
    modelLoader.SetShader(shader);
}

BoundingBox Object3D::GetBoundingBox() const {
    return modelLoader.GetBoundingBox();
}

std::shared_ptr<Model> Object3D::GetModel() const {
    return modelLoader.GetModel();
}

void Object3D::SetQuantity(int quantity) {
    this->quantity = quantity;
}

int Object3D::GetQuantity() const {
    return quantity;
}