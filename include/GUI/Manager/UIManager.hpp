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
    void DrawUI(const std::shared_ptr<Island>& selectedIsland, int fps);

private:
    int screenWidth;
    int screenHeight;

    void DrawTextBox(const std::string& text, int x, int y, int width, int height, Color bgColor, Color borderColor, int textSize);
};

#endif // UIMANAGER_HPP_

