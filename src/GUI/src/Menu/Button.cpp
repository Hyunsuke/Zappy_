#include "gui.hpp"

ButtonState GetButtonState(Rectangle button) {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, button)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            return PRESSED;
        } else {
            return HOVER;
        }
    }
    return NORMAL;
}

Color GetButtonColor(ButtonState state) {
    switch (state) {
        case NORMAL: return LIGHTGRAY;
        case HOVER: return YELLOW;
        case PRESSED: return GREEN;
        default: return LIGHTGRAY;
    }
}

void DrawButton(Rectangle button, const char* text, int fontSize) {
    ButtonState state = GetButtonState(button);
    Color color = GetButtonColor(state);

    DrawRectangleRec(button, color);
    DrawRectangleLines(button.x, button.y, button.width, button.height, DARKGRAY);

    int textWidth = MeasureText(text, fontSize);
    int textX = button.x + (button.width - textWidth) / 2;
    int textY = button.y + (button.height - fontSize) / 2;

    DrawText(text, textX, textY, fontSize, BLACK);
}
