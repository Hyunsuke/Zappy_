/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "CameraController.hpp"
#include "Map.hpp"
#include <vector>
#include <iostream>
#include <raymath.h>
#include <raylib.h>
#include <cstring>
#include <GL/gl.h>

class Game {
public:
    Game(int screenWidth, int screenHeight, int mapWidth, int mapHeight);
    ~Game();
    void Run();
    void ToggleObjectActive(int islandId, const std::string& objectType, int value);
    void SetIslandScale(int islandId, float scale);
    void SetIslandRotation(int islandId, Vector3 rotationAxis, float rotationAngle);

private:
    void Update();
    void Draw();
    void InitializeMap(int width, int height);
    std::shared_ptr<Island> GetIslandUnderMouse();

    int screenWidth;
    int screenHeight;
    CameraController cameraController;
    Map gameMap;
    Shader shader;

    Ray ray;
    RayCollision collision;
    Color cursorColor;
    char hitObjectName[50];
    std::shared_ptr<Island> selectedIsland;
};

#endif /* !GAME_HPP_ */
