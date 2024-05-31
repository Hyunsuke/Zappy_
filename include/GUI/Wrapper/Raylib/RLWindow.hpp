/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLWindow
*/

#ifndef RLWINDOW_HPP_
#define RLWINDOW_HPP_

#include "raylib.h"
#include <string>

class RLWindow {
public:
    RLWindow(int width, int height, const std::string& title);
    ~RLWindow();

    void BeginDrawing();
    void EndDrawing();
    void BeginMode3D(Camera camera);
    void EndMode3D();
    bool WindowShouldClose();
    void ClearBackground(Color color);

private:
    int width;
    int height;
    std::string title;
};

#endif // RLWINDOW_HPP_
