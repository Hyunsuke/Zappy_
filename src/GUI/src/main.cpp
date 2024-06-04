/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main.cpp
*/

#include "gui.hpp"

void init_Window(int screenWidth, int screenHeight, const char* title) {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
}

int main() {
    try {
        int screenWidth = 1920;
        int screenHeight = 1080;
        init_Window(screenWidth, screenHeight, "Zappy GUI");

        Menu menu(screenWidth, screenHeight);
        menu.Run();

        if (menu.ShouldOpenSettings()) {
            // Open settings menu (not implemented here, but you can add it similarly)
        } else if (menu.ShouldStartGame()) {
            std::string host = menu.GetHost();
            int port = menu.GetPort();
            Game game(screenWidth, screenHeight, 10, 10); // Pass host and port to the Game
            game.Run();
        }

    } catch (const GameException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CloseWindow();
        return 84;
    }
    CloseWindow();
    return 0;
}