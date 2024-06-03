/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameException
*/

#include "gui.hpp"

GameException::GameException(const std::string& message)
    : message(message) {}

const char* GameException::what() const noexcept {
    return message.c_str();
}
