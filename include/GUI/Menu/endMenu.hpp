/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** EndMenu
*/

#ifndef ENDMENU_HPP
#define ENDMENU_HPP

#include "../Sky/Sky.hpp"
#include "../core/CameraController.hpp"
#include "../Menu/Button.hpp"

#include "raylib.h"
#include <string>

class EndMenu {
public:
    EndMenu(int screenWidth, int screenHeight);
    void Draw(const std::string& winningTeam);
    void HandleMouseInput();

private:
    int screenWidth;
    int screenHeight;
    Camera camera;
    Sky sky;

    bool closeButtonClicked;

    RLWindow window;
    RLModel rlModel;
    RLText rlText;
    Button button;
};

#endif // ENDMENU_HPP
