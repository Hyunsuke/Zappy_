/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Menu
*/

#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <raylib.h>
#include "gui.hpp"
#include "../Menu/Button.hpp"

class Menu {
public:
    Menu(int screenWidth, int screenHeight, const std::string& host, int port);
    void Run();

    std::string GetHost() const;
    int GetPort() const;
    int GetScreenWidth() const;
    int GetScreenHeight() const;
    bool ShouldStartGame() const;

private:
    void HandleInput();
    void Draw();
    void UpdateWindowSize(int width, int height);
    bool IsMouseOverButton(Rectangle button);
    bool IsMouseOverTextBox(Rectangle textBox);
    // void HandleBackspace(std::string& buffer, bool& isActive, float& backspaceTime);
    // void HandleBackspace(int& buffer, bool& isActive, float& backspaceTime);
    // void HandleBackspace(std::string& buffer, bool& isActive, float& backspaceTime);
    void HandleBackspace(std::string& buffer, bool& isActive, float& backspaceTime);
    void HandleBackspace(int& buffer, bool& isActive, float& backspaceTime);
    int screenWidth;
    int screenHeight;
    std::string host;
    int port;
    bool startGame;
    bool hostActive;
    bool portActive;
    float hostBackspaceTime;
    float portBackspaceTime;
    // std::string host;
    // int port;
    // char hostBuffer[128];
    // char portBuffer[6];
    std::unique_ptr<ShaderManager> shaderManager;
    std::shared_ptr<Island> islandModel;
    Camera camera;
    std::unique_ptr<Player> player;
    Settings settings;
    Sky sky;
    RLWindow window;
    RLModel rlModel;
    RLText rlText;
    Button button;
};

#endif // MENU_HPP
