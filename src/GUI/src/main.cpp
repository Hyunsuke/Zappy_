/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main.cpp
*/

#include "gui.hpp"

int main() {
    try {
        Game game(1920, 1080, 10, 10);
        game.Run();
    } catch (const GameException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CloseWindow();
        return 84;
    }
    return 0;
}