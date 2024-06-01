/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Game.cpp
*/

#include "gui.hpp"

Game::Game(int screenWidth, int screenHeight, int mapWidth, int mapHeight)
    :   screenWidth(screenWidth),
        screenHeight(screenHeight),
        gameMap(mapWidth,mapHeight),
        sky(screenWidth, screenHeight),
        uiManager(screenWidth, screenHeight) {

    InitWindow(screenWidth, screenHeight, "Zappy 3D GUI with raylib");
    SetTargetFPS(60);

    shaderManager = std::make_unique<ShaderManager>("src/GUI/assets/shaders/lighting.vs", "src/GUI/assets/shaders/lighting.fs");
    Vector3 lightPosition = { 10.0f, 10.0f, 10.0f };
    Vector3 viewPosition = { 0.0f, 10.0f, 10.0f };
    Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    Vector3 ambientColor = { 0.2f, 0.2f, 0.2f };
    shaderManager->SetShaderValue("lightPosition", &lightPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("viewPosition", &viewPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("lightColor", &lightColor, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("ambientColor", &ambientColor, SHADER_UNIFORM_VEC3);

    InitializeMap(mapWidth, mapHeight);
}

Game::~Game() {
    CloseWindow();
}

void Game::InitializeMap(int width, int height) {
    float spacing = 15.0f;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            Vector3 position = {i * spacing, 0.0f, j * spacing};
            float scale = 0.7f;
            Vector3 rotationAxis = {0.0f, 1.0f, 0.0f};
            float rotationAngle = 0.0f;
            auto island = std::make_shared<Island>(i, j, position, "src/GUI/assets/Island/Island01.obj", "src/GUI/assets/Island/TextIsland.png", scale, rotationAxis, rotationAngle);
            island->SetShader(shaderManager->GetShader());
            gameMap.AddIsland(island);
        }
    }
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void Game::Update() {
    cameraController.Update();
    gameMap.Update();

    sky.Update();

    Vector3 lightPos = sky.GetLightPosition();
    Vector3 lightCol = sky.GetLightColor();
    shaderManager->SetShaderValue("lightPosition", &lightPos, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("lightColor", &lightCol, SHADER_UNIFORM_VEC3);

    rayManager.UpdateRay(cameraController.GetCamera());
    selectedIsland = rayManager.GetIslandUnderMouse(gameMap.GetIslands());
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    sky.DrawBackground();

    BeginMode3D(cameraController.GetCamera());

    sky.DrawSunAndMoon();
    gameMap.Draw();
    gameMap.DrawIslandWires(selectedIsland);

    EndMode3D();
    uiManager.DrawUI(selectedIsland, GetFPS());
    EndDrawing();
}

void Game::ToggleObjectActive(int x, int y, const std::string& objectType, int value) {
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        if (objectType == "food") {
            island->food->SetQuantity(island->food->GetQuantity() + value);
        } else if (objectType == "linemate") {
            island->linemate->SetQuantity(island->linemate->GetQuantity() + value);
        } else if (objectType == "deraumere") {
            island->deraumere->SetQuantity(island->deraumere->GetQuantity() + value);
        } else if (objectType == "sibur") {
            island->sibur->SetQuantity(island->sibur->GetQuantity() + value);
        } else if (objectType == "mendiane") {
            island->mendiane->SetQuantity(island->mendiane->GetQuantity() + value);
        } else if (objectType == "phiras") {
            island->phiras->SetQuantity(island->phiras->GetQuantity() + value);
        } else if (objectType == "thystame") {
            island->thystame->SetQuantity(island->thystame->GetQuantity() + value);
        }
    }
}
