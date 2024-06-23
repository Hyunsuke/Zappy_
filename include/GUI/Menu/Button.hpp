/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Button
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <gui.hpp>

enum ButtonState {
    NORMAL,
    HOVER,
    PRESSED
};

class Button {
public:
    Button();
    ButtonState GetButtonState(Rectangle button);
    Color GetButtonColor(ButtonState state);
    void DrawButton(Rectangle button, const std::string& text, int fontSize);
private:
    Rectangle button;
    ButtonState state;
    RLText rlText;
};

#endif // BUTTON_HPP
