/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Loading
*/

#ifndef LOADINGSCREEN_HPP
#define LOADINGSCREEN_HPP

#include "../core/CameraController.hpp"
#include "../Sky/Sky.hpp"

#include <string>
#include <raylib.h>

class LoadingScreen {
public:
    LoadingScreen(int screenWidth, int screenHeight);
    void Draw(const std::string& message, float progress);
private:
    int screenWidth;
    int screenHeight;
    Camera camera;
    Sky sky;
    std::shared_ptr<Texture2D> image;
    RLText rlText;
    RLWindow window;
    RLModel rlmodel;
};

#endif // LOADINGSCREEN_HPP
