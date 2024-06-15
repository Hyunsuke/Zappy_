#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <gui.hpp>

enum ButtonState {
    NORMAL,
    HOVER,
    PRESSED
};

ButtonState GetButtonState(Rectangle button);
Color GetButtonColor(ButtonState state);
void DrawButton(Rectangle button, const char* text, int fontSize);

#endif // BUTTON_HPP
