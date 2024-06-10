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

    void DrawUI(const std::shared_ptr<Island>& selectedIsland, int teamCount, int playerCount, int timeUnit, const std::string& mapSize, int fps);
    void DrawIslandInfo(const std::shared_ptr<Island>& selectedIsland, int fps);
    void DrawAdditionalInfo(int teamCount, int playerCount, int timeUnit, const std::string& mapSize);


private:
    int screenWidth;
    int screenHeight;
};

#endif // UIMANAGER_HPP_

