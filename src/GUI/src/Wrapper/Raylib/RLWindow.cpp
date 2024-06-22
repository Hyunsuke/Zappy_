/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLWindow
*/

#include "gui.hpp"

RLWindow::RLWindow() {}


RLWindow::~RLWindow() {}

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

void RLWindow::InitWindow(int width, int height, const std::string& title) {
    ::InitWindow(width, height, title.c_str());
}

void RLWindow::SetTargetFPS(int fps) {
    ::SetTargetFPS(fps);
}

void RLWindow::CloseWindow() {
    ::CloseWindow();
}

float RLWindow::GetFrameTime() {
    return ::GetFrameTime();
}
void RLWindow::SetWindowSize(int width, int height) {
    ::SetWindowSize(width, height);
}

bool RLWindow::IsWindowResized() {
    return ::IsWindowResized();
}
