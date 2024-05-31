/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLWindow
*/

#include "gui.hpp"

RLWindow::RLWindow(int width, int height, const std::string& title)
    : width(width), height(height), title(title) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
}

RLWindow::~RLWindow() {
    CloseWindow();
}

void RLWindow::BeginDrawing() {
    ::BeginDrawing();
}

void RLWindow::EndDrawing() {
    ::EndDrawing();
}

void RLWindow::BeginMode3D(Camera camera) {
    ::BeginMode3D(camera);
}

void RLWindow::EndMode3D() {
    ::EndMode3D();
}

bool RLWindow::WindowShouldClose() {
    return ::WindowShouldClose();
}

void RLWindow::ClearBackground(Color color) {
    ::ClearBackground(color);
}


