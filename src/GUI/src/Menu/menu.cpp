/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** menu
*/

#include "gui.hpp"

Menu::Menu(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), host("localhost"), port(4242),
      startGame(false), openSettings(false), hostActive(false), portActive(false),
      hostBackspaceTime(0.0f), portBackspaceTime(0.0f) {
    std::strcpy(hostBuffer, host.c_str());
    std::sprintf(portBuffer, "%d", port);
}

void Menu::Run() {
    while (!WindowShouldClose() && !startGame && !openSettings) {
        HandleInput();
        Draw();
    }
}

std::string Menu::GetHost() const {
    return host;
}

int Menu::GetPort() const {
    return port;
}

bool Menu::ShouldStartGame() const {
    return startGame;
}

bool Menu::ShouldOpenSettings() const {
    return openSettings;
}

bool Menu::IsMouseOverButton(Rectangle button) {
    Vector2 mousePoint = GetMousePosition();
    return CheckCollisionPointRec(mousePoint, button);
}

bool Menu::IsMouseOverTextBox(Rectangle textBox) {
    Vector2 mousePoint = GetMousePosition();
    return CheckCollisionPointRec(mousePoint, textBox);
}

void Menu::HandleBackspace(char* buffer, bool& isActive, float& backspaceTime) {
    if (isActive) {
        if (IsKeyPressed(KEY_BACKSPACE) && std::strlen(buffer) > 0) {
            buffer[std::strlen(buffer) - 1] = '\0';
            backspaceTime = 0.0f;
        } else if (IsKeyDown(KEY_BACKSPACE) && std::strlen(buffer) > 0) {
            backspaceTime += GetFrameTime();
            if (backspaceTime >= 0.1f) {
                buffer[std::strlen(buffer) - 1] = '\0';
                backspaceTime = 0.05f; // Set a shorter interval for continuous deletion
            }
        } else {
            backspaceTime = 0.0f;
        }
    }
}

void Menu::HandleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        startGame = true;
    }

    if (IsKeyPressed(KEY_TAB)) {
        openSettings = true;
    }

    // Handle text input for host
    if (hostActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && std::strlen(hostBuffer) < sizeof(hostBuffer) - 1) {
                int len = std::strlen(hostBuffer);
                hostBuffer[len] = (char)key;
                hostBuffer[len + 1] = '\0';
            }
            key = GetCharPressed();
        }

        HandleBackspace(hostBuffer, hostActive, hostBackspaceTime);
    }

    // Handle text input for port
    if (portActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= '0') && (key <= '9') && std::strlen(portBuffer) < sizeof(portBuffer) - 1) {
                int len = std::strlen(portBuffer);
                portBuffer[len] = (char)key;
                portBuffer[len + 1] = '\0';
            }
            key = GetCharPressed();
        }

        HandleBackspace(portBuffer, portActive, portBackspaceTime);
    }

    // Handle mouse clicks for text boxes and buttons
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Rectangle hostBox = {(float)(screenWidth / 4 + 100), (float)(screenHeight / 2 - 60), 200.0f, 30.0f};
        Rectangle portBox = {(float)(screenWidth / 4 + 100), (float)(screenHeight / 2), 200.0f, 30.0f};
        Rectangle connectButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 150), 100.0f, 40.0f};
        Rectangle settingsButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 80), 100.0f, 40.0f};

        if (IsMouseOverTextBox(hostBox)) {
            hostActive = true;
            portActive = false;
        } else if (IsMouseOverTextBox(portBox)) {
            portActive = true;
            hostActive = false;
        } else if (IsMouseOverButton(connectButton)) {
            startGame = true;
        } else if (IsMouseOverButton(settingsButton)) {
            openSettings = true;
        } else {
            hostActive = false;
            portActive = false;
        }
    }

    // Update host and port values
    host = std::string(hostBuffer);
    port = std::atoi(portBuffer);
}

void Menu::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Zappy GUI", screenWidth / 2 - MeasureText("Zappy GUI", 40) / 2, screenHeight / 4, 40, LIGHTGRAY);

    DrawText("Host:", screenWidth / 4, screenHeight / 2 - 60, 20, DARKGRAY);
    DrawRectangle(screenWidth / 4 + 100, screenHeight / 2 - 60, 200, 30, hostActive ? LIGHTGRAY : GRAY);
    DrawText(hostBuffer, screenWidth / 4 + 110, screenHeight / 2 - 55, 20, BLACK);

    DrawText("Port:", screenWidth / 4, screenHeight / 2, 20, DARKGRAY);
    DrawRectangle(screenWidth / 4 + 100, screenHeight / 2, 200, 30, portActive ? LIGHTGRAY : GRAY);
    DrawText(portBuffer, screenWidth / 4 + 110, screenHeight / 2 + 5, 20, BLACK);

    DrawRectangle(screenWidth / 2 - 50, screenHeight - 150, 100, 40, LIGHTGRAY);
    DrawText("Connect", screenWidth / 2 - MeasureText("Connect", 20) / 2, screenHeight - 140, 20, BLACK);

    DrawRectangle(screenWidth / 2 - 50, screenHeight - 80, 100, 40, LIGHTGRAY);
    DrawText("Settings", screenWidth / 2 - MeasureText("Settings", 20) / 2, screenHeight - 70, 20, BLACK);

    EndDrawing();
}
