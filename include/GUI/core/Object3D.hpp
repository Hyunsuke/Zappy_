/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Object3D
*/

#ifndef OBJECT3D_HPP_
#define OBJECT3D_HPP_

#include "raylib.h"

class Object3D {
public:
    Object3D(Vector3 position, float size, Color color);
    void Draw();
    Vector3 GetPosition() const;

private:
    Vector3 position;
    float size;
    Color color;
};

#endif /* !OBJECT3D_HPP_ */
