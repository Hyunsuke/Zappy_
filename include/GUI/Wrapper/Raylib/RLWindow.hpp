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
    RLWindow();
    ~RLWindow();

    void BeginDrawing();
    void EndDrawing();
    void BeginMode3D(Camera camera);
    void EndMode3D();
    bool WindowShouldClose();
    void ClearBackground(Color color);
    void InitWindow(int width, int height, const std::string& title);
    void SetTargetFPS(int fps);
    void CloseWindow();
    float GetFrameTime();
    void SetWindowSize(int width, int height);
    bool IsWindowResized();

private:
};

#endif // RLWINDOW_HPP_
