/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <string>
#include <vector>
#include <raylib.h>

class Settings {
public:
    Settings(int screenWidth, int screenHeight);
    void Draw();
    void Update();
    void Open();
    void Close();
    bool IsOpen() const;
    void ApplySettings();

    int GetScreenWidth() const;
    int GetScreenHeight() const;
    int GetFPS() const;
    void UpdateLayout(int screenWidth, int screenHeight);

private:
    bool open;
    int screenWidth;
    int screenHeight;
    int fps;
    std::vector<std::string> keyBindingsDescriptions;

    Rectangle resolutionBox;
    Rectangle fpsBox;
    Rectangle keyBindingsBox;
    Rectangle applyButton;
    Rectangle closeButton;

    int selectedResolutionIndex;
    int selectedFPSIndex;
    std::vector<Vector2> resolutions;
    std::vector<int> fpsOptions;

    void DrawDropDown(const std::vector<std::string>& options, int& selectedIndex, Rectangle box);
};

#endif // SETTINGS_HPP_

