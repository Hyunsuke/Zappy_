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
#include "../Settings/settings.hpp"
#include "../Socket/SocketManager.hpp"
#include "../Manager/ChatManager.hpp"
#include "../Manager/CameraManager.hpp"

#include "../Wrapper/Raylib/RLWindow.hpp"
#include "../Wrapper/Raylib/RLModel.hpp"
#include "../Menu/endMenu.hpp"

#include <vector>
#include <iostream>
#include <raymath.h>
#include <raylib.h>
#include <cstring>
#include <GL/gl.h>
#include <sstream>
#include <set>
#include <algorithm>
#include <memory>
#include <future>
#include <chrono>

class Settings;

class Game {
public:
    Game(int screenWidth, int screenHeight, const std::string& mapSize, int timeUnit, const std::vector<std::string>& teamNames, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs, std::shared_ptr<Settings> settings);
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
    int GetTimeUnit() const;

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
    Map gameMap;
    int timeUnit;
    std::vector<std::string> teamNames;
    Sky sky;
    std::unique_ptr<ShaderManager> shaderManager;
    UIManager uiManager;
    RayManager rayManager;
    std::shared_ptr<Settings> settings;
    CameraController cameraController;
    CameraManager cameraManager;
    std::unique_ptr<SocketManager> socketManager;

    std::shared_ptr<Island> selectedIsland;
    std::shared_ptr<Player> selectedPlayer;
    RLWindow window;
    RLModel rlModel;

    bool gameOver = false;
    std::string winningTeam;
    EndMenu endMenu;
};

#endif /* !GAME_HPP_ */
