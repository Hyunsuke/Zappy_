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
};

#endif // RLTEXT_HPP_
