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
#include "../Sky/Sky.hpp"
#include "../Manager/ShaderManager.hpp"
#include "../Manager/UIManager.hpp"
#include "../Manager/RayManager.hpp"
#include "../Particles/ParticleSystem.hpp"
#include "../Settings/settings.hpp"

class Game {
public:
    Game(int screenWidth, int screenHeight, int mapWidth, int mapHeight);
    ~Game();
    void Run();
    void ToggleObjectActive(int x, int y, const std::string& objectType, int value);

private:
    void Update();
    void Draw();
    void InitializeMap(int width, int height);

    int screenWidth;
    int screenHeight;
    CameraController cameraController;
    Map gameMap;
    Sky sky;
    std::unique_ptr<ShaderManager> shaderManager;
    UIManager uiManager;
    RayManager rayManager;
    Settings settings;

    std::shared_ptr<Island> selectedIsland;
};

#endif /* !GAME_HPP_ */
