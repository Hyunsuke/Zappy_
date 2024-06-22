/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RLText.cpp
*/

#include "gui.hpp"

void RLText::DrawText(const std::string& text, int posX, int posY, int fontSize, Color color) {
    ::DrawText(text.c_str(), posX, posY, fontSize, color);
}

void RLText::DrawTextFormat(int posX, int posY, int fontSize, Color color, const char* text, ...) {
    va_list args;
    va_start(args, text);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), text, args);
    va_end(args);
    ::DrawText(buffer, posX, posY, fontSize, color);
}

Color RLText::Fade(Color color, float alpha) {
    return ::Fade(color, alpha);
}

void RLText::DrawRectangleRec(Rectangle rec, Color color) {
    ::DrawRectangleRec(rec, color);
}

int RLText::MeasureText(const std::string& text, int fontSize) {
    return ::MeasureText(text.c_str(), fontSize);
}

void RLText::DrawRectangle(int posX, int posY, int width, int height, Color color) {
    ::DrawRectangle(posX, posY, width, height, color);
}

void RLText::DrawRectangleLines(int posX, int posY, int width, int height, Color color) {
    ::DrawRectangleLines(posX, posY, width, height, color);
}

std::string RLText::TextFormat(const char* text, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, text);
    vsnprintf(buffer, sizeof(buffer), text, args);
    va_end(args);
    return std::string(buffer);
}

bool RLText::IsMouseOverButton(Rectangle button) {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, button);
}

bool RLText::IsMouseButtonDown(int button) {
    return ::IsMouseButtonDown(button);
}

void RLText::DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color) {
    ::DrawRectangleLinesEx(rec, lineThick, color);
}

Vector2 RLText::GetMousePosition() {
    return ::GetMousePosition();
}

bool RLText::CheckCollisionPointRec(Vector2 point, Rectangle rec) {
    return ::CheckCollisionPointRec(point, rec);
}

bool RLText::IsMouseButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

void RLText::DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
    ::DrawLine(startPosX, startPosY, endPosX, endPosY, color);
}

void RLText::DrawSphere(Vector3 centerPos, float radius, Color color) {
    ::DrawSphere(centerPos, radius, color);
}

float RLText::GetFrameTime() {
    return ::GetFrameTime();
}

bool RLText::IsKeyPressed(int key) {
    return ::IsKeyPressed(key);
}

bool RLText::IsKeyDown(int key) {
    return ::IsKeyDown(key);
}

int RLText::GetCharPressed() {
    return ::GetCharPressed();
}
