/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Settings
*/

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <vector>
#include <string>
#include <ctime>
#include <raylib.h>
#include "../Sky/Sky.hpp"
#include "../Manager/UIManager.hpp"
#include "../Manager/ChatManager.hpp"
#include "../Wrapper/Raylib/RLWindow.hpp"
#include "../Menu/Button.hpp"

class Game;

class Settings {
public:
    Settings(int screenWidth, int screenHeight, std::string InstanceName);
    void Open();
    void Close();
    bool IsOpen() const;
    int GetScreenWidth() const;
    int GetScreenHeight() const;
    int GetFPS() const;
    void ApplySettings();
    void Update();
    void Draw();
    void UpdateLayout(int screenWidth, int screenHeight);
    void HandleMouseInput(Vector2 mousePosition, Rectangle settingsButton, Rectangle closeButton);
    void HandleWindowResize(Sky& sky, UIManager& uiManager);
    void SendMessage(int n, std::shared_ptr<Player> Player, std::string message);
    void SetGameInstance(std::shared_ptr<Game> gameInstance);

private:
    void DrawDropDown(const std::vector<std::string>& options, int& selectedIndex, Rectangle box);

    bool open;
    std::string instanceName;
    int screenWidth;
    int screenHeight;
    int fps;
    int selectedResolutionIndex;
    int selectedFPSIndex;
    int tempResolutionIndex;
    int tempFPSIndex;
    std::vector<Vector2> resolutions;
    std::vector<int> fpsOptions;
    std::vector<std::string> keyBindingsDescriptions;
    Rectangle resolutionBox;
    Rectangle fpsBox;
    Rectangle keyBindingsBox;
    Rectangle applyButton;
    Rectangle closeButton;

    int selectedTimeUnitIndex;
    int tempTimeUnitIndex;
    std::vector<int> timeUnitOptions;
    Rectangle timeUnitBox;


    ChatManager chat;
    std::shared_ptr<Game> game;

    RLWindow window;
    RLModel rlModel;
    RLText rlText;
    Button button;
};

#endif // SETTINGS_HPP
