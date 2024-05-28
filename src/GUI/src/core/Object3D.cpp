/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Object3D.cpp
*/

#include "gui.hpp"

Object3D::Object3D(Vector3 position, float size, Color color)
    : position(position), size(size), color(color) {}

void Object3D::Draw() {
    DrawCube(position, size, size, size, color);
    DrawCubeWires(position, size, size, size, MAROON);
}

Vector3 Object3D::GetPosition() const {
    return position;
}