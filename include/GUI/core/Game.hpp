/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "../Sky/Sky.hpp"
#include "CameraController.hpp"
#include "Map.hpp"
#include "../Manager/ShaderManager.hpp"
#include "../Manager/UIManager.hpp"
#include "../Manager/RayManager.hpp"
#include "../Particles/ParticleSystem.hpp"
#include "../Settings/settings.hpp"
#include "../Socket/SocketManager.hpp"

#include <vector>
#include <iostream>
#include <raymath.h>
#include <raylib.h>
#include <cstring>
#include <GL/gl.h>
#include <sstream>

class Game {
public:
    Game(int screenWidth, int screenHeight, const std::string& mapSize, int timeUnit, const std::vector<std::string>& teamNames, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs);
    ~Game();
    void Run();
    void SetSocketManager(std::unique_ptr<SocketManager> socketManager);

    void RequestMapSize();
    void RequestTileContent(int x, int y);
    void RequestMapContent();
    void RequestTeamNames();
    void RequestPlayerPosition(int playerNumber);
    void RequestPlayerLevel(int playerNumber);
    void RequestPlayerInventory(int playerNumber);
    void RequestTimeUnit();
    void SetTimeUnit(int timeUnit);

private:
    void Update();
    void Draw();
    void InitializeMap(const std::string& mapSize, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs);

    ///////
    void HandleServerMessage(const std::string& message);

    void UpdateIslandResources(int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6);
    ///////

    int screenWidth;
    int screenHeight;
    CameraController cameraController;
    Map gameMap;
    int timeUnit;
    std::vector<std::string> teamNames;
    Sky sky;
    std::unique_ptr<ShaderManager> shaderManager;
    UIManager uiManager;
    RayManager rayManager;
    Settings settings;
    std::unique_ptr<SocketManager> socketManager;

    std::shared_ptr<Island> selectedIsland;
};

#endif /* !GAME_HPP_ */
