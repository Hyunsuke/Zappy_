/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** UIManager
*/

#ifndef UIMANAGER_HPP_
#define UIMANAGER_HPP_

#include <raylib.h>
#include <string>
#include <memory>
#include "../core/Island.hpp"

class UIManager {
public:
    UIManager(int screenWidth, int screenHeight);

    void DrawUI(const std::shared_ptr<Island>& selectedIsland, const std::shared_ptr<Player>& selectedPlayer, int teamCount, int playerCount, int timeUnit, const std::string& mapSize, int fps);
    void DrawAdditionalInfo(int teamCount, int playerCount, int timeUnit, const std::string& mapSize);
    void DrawButtons();
    void DrawIslandInfo(const std::shared_ptr<Island>& selectedIsland, int fps);
    void DrawPlayerInfo(const std::shared_ptr<Player>& selectedPlayer);

    void OnWindowResized(int newScreenWidth, int newScreenHeight);
    Rectangle settingsButton;
    Rectangle closeButton;

private:
    int screenWidth;
    int screenHeight;


    void UpdateButtonPositions();
    void UpdateTextSizes();
};

#endif // UIMANAGER_HPP_
