/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLText
*/

#ifndef RLTEXT_HPP_
#define RLTEXT_HPP_

#include "raylib.h"
#include <string>
#include <cstdarg>


class RLText {
public:
    static void DrawText(const std::string& text, int posX, int posY, int fontSize, Color color);
    static void DrawTextFormat(int posX, int posY, int fontSize, Color color, const char* text, ...);
    static Color Fade(Color color, float alpha);
    static void DrawRectangleRec(Rectangle rec, Color color);
    static int MeasureText(const std::string& text, int fontSize);

    static void DrawRectangle(int posX, int posY, int width, int height, Color color);
    static void DrawRectangleLines(int posX, int posY, int width, int height, Color color);
    static std::string TextFormat(const char* text, ...);
    static bool IsMouseOverButton(Rectangle button);
    static bool IsMouseButtonDown(int button);
    static void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);
    static Vector2 GetMousePosition();
    static bool CheckCollisionPointRec(Vector2 point, Rectangle rec);
    static bool IsMouseButtonPressed(int button);

    static void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
    static void DrawSphere(Vector3 centerPos, float radius, Color color);
    static float GetFrameTime();
    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static int GetCharPressed();
};

#endif // RLTEXT_HPP_
