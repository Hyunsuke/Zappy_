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
