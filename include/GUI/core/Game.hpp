/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "CameraController.hpp"
#include "Object3D.hpp"
#include "ModelLoader.hpp"
#include <vector>
#include <iostream>
#include <raymath.h>
#include <raylib.h>
#include <cstring>
#include <GL/gl.h>


class Game {
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    void Run();

private:
    void Update();
    void Draw();

    int screenWidth;
    int screenHeight;
    CameraController cameraController;
    std::vector<Object3D> objects;
    ModelLoader* modelLoader;

    Ray ray;                       // Ray for picking
    RayCollision collision;        // Collision information
    Color cursorColor;             // Color of the cursor at hit point
    char hitObjectName[50];        // Name of the hit object
    BoundingBox modelBBox;         // Bounding box for the model
};

#endif /* !GAME_HPP_ */
