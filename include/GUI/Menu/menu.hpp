/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <string>
#include <raylib.h>

class Menu {
public:
    Menu(int screenWidth, int screenHeight);
    void Run();
    std::string GetHost() const;
    int GetPort() const;
    bool ShouldStartGame() const;
    bool ShouldOpenSettings() const;

private:
    void Draw();
    void HandleInput();
    bool IsMouseOverButton(Rectangle button);
    bool IsMouseOverTextBox(Rectangle textBox);
    void HandleBackspace(char* buffer, bool& isActive, float& backspaceTime);

    int screenWidth;
    int screenHeight;
    std::string host;
    int port;
    bool startGame;
    bool openSettings;
    char hostBuffer[256];
    char portBuffer[6];
    bool hostActive;
    bool portActive;
    float hostBackspaceTime;
    float portBackspaceTime;
};

#endif // MENU_HPP_

