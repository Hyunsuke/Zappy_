/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** menu
*/

#include "gui.hpp"

Menu::Menu(int screenWidth, int screenHeight, const std::string& host, int port)
    : screenWidth(screenWidth), screenHeight(screenHeight), host(host), port(port),
      startGame(false), hostActive(false), portActive(false),
      hostBackspaceTime(0.0f), portBackspaceTime(0.0f), settings(screenWidth, screenHeight, "menu"),
      sky(screenWidth, screenHeight)
{
    std::strcpy(hostBuffer, host.c_str());
    std::sprintf(portBuffer, "%d", port);

    shaderManager = std::make_unique<ShaderManager>("src/GUI/assets/shaders/lighting.vs", "src/GUI/assets/shaders/lighting.fs");
    Vector3 lightPosition = { 10.0f, 10.0f, 10.0f };
    Vector3 viewPosition = { 0.0f, 10.0f, 10.0f };
    Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    Vector3 ambientColor = { 0.2f, 0.2f, 0.2f };
    shaderManager->SetShaderValue("lightPosition", &lightPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("viewPosition", &viewPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("lightColor", &lightColor, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("ambientColor", &ambientColor, SHADER_UNIFORM_VEC3);

    islandModel = LoadModel("src/GUI/assets/Island/Island01.obj");
    islandTexture = LoadTexture("src/GUI/assets/Island/TextIsland.png");
    islandModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = islandTexture;
    islandModel.materials[0].shader = shaderManager->GetShader();

    camera.position = { 0.0f, 5.0f, 20.0f };
    camera.target = { 0.0f, 2.5f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    std::shared_ptr<Island> island = std::make_shared<Island>(0, 0, Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/Island/Island01.obj", "src/GUI/assets/Island/TextIsland.png", 0.7f, Vector3{0.0f, 1.0f, 0.0f}, 0.0f);
    player = std::make_unique<Player>(1, "menu", 0, 0, 1, 1, "src/GUI/assets/Player/robot.glb", island);
    player->SetAnimation(Player::Animation::Dance);
}

void Menu::Run() {
    while (!WindowShouldClose() && !startGame) {
        HandleInput();
        player->UpdateAnimation();
        player->UpdatePosition();

        player->SetPosition({0.0f, 1.0f, 2.5f});
        player->SetScale({1.0f, 1.0f, 1.0f});

        sky.Update();

        Draw();
    }
}

std::string Menu::GetHost() const {
    return host;
}

int Menu::GetPort() const {
    return port;
}

int Menu::GetScreenWidth() const {
    return screenWidth;
}

int Menu::GetScreenHeight() const {
    return screenHeight;
}

bool Menu::ShouldStartGame() const {
    return startGame;
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
                backspaceTime = 0.05f;
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
            settings.Open();
        } else {
            hostActive = false;
            portActive = false;
        }
    }

    host = std::string(hostBuffer);
    port = std::atoi(portBuffer);

    if (settings.IsOpen()) {
        settings.Update();
        if (!settings.IsOpen()) {
            UpdateWindowSize(settings.GetScreenWidth(), settings.GetScreenHeight());
        }
    }
}

void Menu::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    sky.DrawBackground();

    BeginMode3D(camera);

    DrawModel(islandModel, {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
    player->Draw();

    EndMode3D();

    DrawText("Zappy GUI", screenWidth / 2 - MeasureText("Zappy GUI", 40) / 2, screenHeight / 4, 40, LIGHTGRAY);

    DrawText("Host:", screenWidth / 4, screenHeight / 2 - 60, 20, DARKGRAY);
    DrawRectangle(screenWidth / 4 + 100, screenHeight / 2 - 60, 200, 30, hostActive ? LIGHTGRAY : GRAY);
    DrawText(hostBuffer, screenWidth / 4 + 110, screenHeight / 2 - 55, 20, BLACK);

    DrawText("Port:", screenWidth / 4, screenHeight / 2, 20, DARKGRAY);
    DrawRectangle(screenWidth / 4 + 100, screenHeight / 2, 200, 30, portActive ? LIGHTGRAY : GRAY);
    DrawText(portBuffer, screenWidth / 4 + 110, screenHeight / 2 + 5, 20, BLACK);

    Rectangle connectButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 150), 100.0f, 40.0f};
    DrawButton(connectButton, "Connect", 20);

    Rectangle settingsButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 80), 100.0f, 40.0f};
    DrawButton(settingsButton, "Settings", 20);

    settings.Draw();

    EndDrawing();
}

void Menu::UpdateWindowSize(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    SetWindowSize(screenWidth, screenHeight);
    settings.UpdateLayout(screenWidth, screenHeight);
}
