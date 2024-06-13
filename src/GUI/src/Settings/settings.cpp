/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** settings
*/

#include "gui.hpp"

Settings::Settings(int screenWidth, int screenHeight)
    : open(false), screenWidth(screenWidth), screenHeight(screenHeight), fps(60),
      selectedResolutionIndex(0), selectedFPSIndex(0),
      tempResolutionIndex(0), tempFPSIndex(0) {

    resolutions = { {1920, 1080}, {1280, 720}, {800, 600} };
    fpsOptions = { 30, 60, 120 };

    keyBindingsDescriptions = {
        "ENTER -> Connect",
        "ESCAPE -> Quit",
        "W -> Move Up",
        "S -> Move Down",
        "A -> Move Left",
        "D -> Move Right"
    };

    UpdateLayout(screenWidth, screenHeight);
}

void Settings::Open() {
    open = true;
    tempResolutionIndex = selectedResolutionIndex;
    tempFPSIndex = selectedFPSIndex;
    UpdateLayout(screenWidth, screenHeight);
}

void Settings::Close() {
    open = false;
}

bool Settings::IsOpen() const {
    return open;
}

int Settings::GetScreenWidth() const {
    return resolutions[selectedResolutionIndex].x;
}

int Settings::GetScreenHeight() const {
    return resolutions[selectedResolutionIndex].y;
}

int Settings::GetFPS() const {
    return fpsOptions[selectedFPSIndex];
}

void Settings::ApplySettings() {
    selectedResolutionIndex = tempResolutionIndex;
    selectedFPSIndex = tempFPSIndex;
    screenWidth = resolutions[selectedResolutionIndex].x;
    screenHeight = resolutions[selectedResolutionIndex].y;
    fps = fpsOptions[selectedFPSIndex];
    SetWindowSize(screenWidth, screenHeight);
    SetTargetFPS(fps);
}

void Settings::Update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), applyButton)) {
            ApplySettings();
            Close();
        } else if (CheckCollisionPointRec(GetMousePosition(), closeButton)) {
            tempResolutionIndex = selectedResolutionIndex;
            tempFPSIndex = selectedFPSIndex;
            Close();
        }
    }
}

void Settings::Draw() {
    if (!open) return;

    int dialogWidth = screenWidth * 3 / 4;
    int dialogHeight = screenHeight * 3 / 4;
    int dialogX = (screenWidth - dialogWidth) / 2;
    int dialogY = (screenHeight - dialogHeight) / 2;
    int i = 0;

    DrawRectangle(dialogX, dialogY, dialogWidth, dialogHeight, LIGHTGRAY);
    DrawRectangleLines(dialogX, dialogY, dialogWidth, dialogHeight, DARKGRAY);

    DrawText("Resolution:", resolutionBox.x - 100, resolutionBox.y + 5, 20, BLACK);
    std::vector<std::string> resolutionOptions = { "1920x1080", "1280x720", "800x600" };
    DrawDropDown(resolutionOptions, tempResolutionIndex, resolutionBox);

    DrawText("FPS:", fpsBox.x - 50, fpsBox.y + 5, 20, BLACK);
    std::vector<std::string> fpsOptionsText = { "30", "60", "120" };
    DrawDropDown(fpsOptionsText, tempFPSIndex, fpsBox);

    DrawText("Key Bindings:", keyBindingsBox.x - 150, keyBindingsBox.y - 25, 20, BLACK);

    for (const auto& description : keyBindingsDescriptions) {
        DrawText(description.c_str(), keyBindingsBox.x, keyBindingsBox.y + i * 20, 20, BLACK);
        i++;
    }

    DrawText("Apply", applyButton.x + 20, applyButton.y + 10, 20, BLACK);
    DrawRectangleLines(applyButton.x, applyButton.y, applyButton.width, applyButton.height, DARKGRAY);

    DrawText("Close", closeButton.x + 20, closeButton.y + 10, 20, BLACK);
    DrawRectangleLines(closeButton.x, closeButton.y, closeButton.width, closeButton.height, DARKGRAY);
}

void Settings::UpdateLayout(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    int centerX = screenWidth / 2;
    int baseY = screenHeight / 4;
    int spacing = 60;
    int keyBindingHeight = keyBindingsDescriptions.size() * 20;

    resolutionBox = { (float)(centerX - 100), (float)(baseY), 200, 30 };
    fpsBox = { (float)(centerX - 100), (float)(baseY + spacing), 200, 30 };
    keyBindingsBox = { (float)(centerX - 100), (float)(baseY + 2 * spacing), 200, (float)keyBindingHeight };
    applyButton = { (float)(centerX - 110), (float)(baseY + 3 * spacing + keyBindingHeight), 100, 40 };
    closeButton = { (float)(centerX + 10), (float)(baseY + 3 * spacing + keyBindingHeight), 100, 40 };
}

void Settings::DrawDropDown(const std::vector<std::string>& options, int& selectedIndex, Rectangle box) {
    DrawRectangleRec(box, WHITE);
    DrawText(options[selectedIndex].c_str(), box.x + 5, box.y + 5, 20, BLACK);
    DrawRectangleLines(box.x, box.y, box.width, box.height, DARKGRAY);

    if (CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedIndex = (selectedIndex + 1) % options.size();
    }
}
