/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Button
*/

#include "gui.hpp"

Button::Button() {}

ButtonState Button::GetButtonState(Rectangle button) {
    Vector2 mousePoint = rlText.GetMousePosition();
    if (rlText.CheckCollisionPointRec(mousePoint, button)) {
        if (rlText.IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            return PRESSED;
        } else {
            return HOVER;
        }
    }
    return NORMAL;
}

Color Button::GetButtonColor(ButtonState state) {
    switch (state) {
        case NORMAL: return LIGHTGRAY;
        case HOVER: return YELLOW;
        case PRESSED: return GREEN;
        default: return LIGHTGRAY;
    }
}

void Button::DrawButton(Rectangle button, const std::string& text, int fontSize) {
    ButtonState state = GetButtonState(button);
    Color color = GetButtonColor(state);

    rlText.DrawRectangleRec(button, color);
    rlText.DrawRectangleLines(button.x, button.y, button.width, button.height, DARKGRAY);

    int textWidth = rlText.MeasureText(text, fontSize);
    int textX = button.x + (button.width - textWidth) / 2;
    int textY = button.y + (button.height - fontSize) / 2;

    rlText.DrawText(text, textX, textY, fontSize, BLACK);
}
