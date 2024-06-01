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
        cursorColor(WHITE),
        sky(screenWidth, screenHeight) {
    InitWindow(screenWidth, screenHeight, "Zappy 3D GUI with raylib");
    SetTargetFPS(60);

    shader = LoadShader("src/GUI/assets/shaders/lighting.vs", "src/GUI/assets/shaders/lighting.fs");
    int lightPosLoc = GetShaderLocation(shader, "lightPosition");
    int viewPosLoc = GetShaderLocation(shader, "viewPosition");
    int lightColorLoc = GetShaderLocation(shader, "lightColor");
    int ambientColorLoc = GetShaderLocation(shader, "ambientColor");

    Vector3 lightPosition = { 10.0f, 10.0f, 10.0f };
    Vector3 viewPosition = { 0.0f, 10.0f, 10.0f };
    Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    Vector3 ambientColor = { 0.2f, 0.2f, 0.2f };

    SetShaderValue(shader, lightPosLoc, &lightPosition, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, viewPosLoc, &viewPosition, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, lightColorLoc, &lightColor, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, ambientColorLoc, &ambientColor, SHADER_UNIFORM_VEC3);

    InitializeMap(mapWidth, mapHeight);
}

Game::~Game() {
    if (shader.id != 0) UnloadShader(shader);
    CloseWindow();
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

    // Update the light position and color in the shader
    int lightPosLoc = GetShaderLocation(shader, "lightPosition");
    int lightColorLoc = GetShaderLocation(shader, "lightColor");
    Vector3 lightPos = sky.GetLightPosition();
    Vector3 lightCol = sky.GetLightColor();
    SetShaderValue(shader, lightPosLoc, &lightPos, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, lightColorLoc, &lightCol, SHADER_UNIFORM_VEC3);

    ray = GetMouseRay(GetMousePosition(), cameraController.GetCamera());
    collision.hit = false;
    cursorColor = WHITE;
    strcpy(hitObjectName, "None");
    selectedIsland = GetIslandUnderMouse();

    if (selectedIsland) {
        cursorColor = BLUE;
        strcpy(hitObjectName, "Island");
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(WHITE);

    sky.DrawBackground();


    BeginMode3D(cameraController.GetCamera());

    sky.DrawSunAndMoon();

    gameMap.Draw();

    if (selectedIsland) {
         glLineWidth(100.0f);
        DrawModelWiresEx(*selectedIsland->GetModel(), selectedIsland->GetPosition(), selectedIsland->GetRotationAxis(), selectedIsland->GetRotationAngle(), Vector3{selectedIsland->GetScale(), selectedIsland->GetScale(), selectedIsland->GetScale()}, RED);
        for (const auto& obj : selectedIsland->GetObjects()) {
            if (obj->GetQuantity() > 0)
            DrawModelWiresEx(*obj->GetModel(), obj->GetPosition(), obj->GetRotationAxis(), obj->GetRotationAngle(), Vector3{obj->GetScale(), obj->GetScale(), obj->GetScale()}, RED);
        }
         glLineWidth(1.0f);
    }

    EndMode3D();

    const int baseX = 10;
    const int baseY = 10;
    const int lineSpacing = 30;
    const int padding = 10;
    const int textSize = 30;
    int lines = 9;

    int rectHeight = (lines * lineSpacing) + (2 * padding);
    int rectWidth = 500;

    DrawRectangle(baseX, baseY, rectWidth, rectHeight, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(baseX, baseY, rectWidth, rectHeight, BLUE);

    RLText::DrawText(TextFormat("FPS: %d", GetFPS()), baseX + padding, baseY + padding, textSize, BLACK);
    if (selectedIsland) {
        RLText::DrawText(TextFormat("Selected Island Pos : %d, %d", selectedIsland->GetX(), selectedIsland->GetY()), baseX + padding, baseY + padding + lineSpacing, textSize, BLACK);
        RLText::DrawText(TextFormat("Food : %d", selectedIsland->food->GetQuantity()), baseX + padding, baseY + padding + (2 * lineSpacing), textSize, BLACK);
        RLText::DrawText(TextFormat("Linemate : %d", selectedIsland->linemate->GetQuantity()), baseX + padding, baseY + padding + (3 * lineSpacing), textSize, BLACK);
        RLText::DrawText(TextFormat("Deraumere : %d", selectedIsland->deraumere->GetQuantity()), baseX + padding, baseY + padding + (4 * lineSpacing), textSize, BLACK);
        RLText::DrawText(TextFormat("Sibur : %d", selectedIsland->sibur->GetQuantity()), baseX + padding, baseY + padding + (5 * lineSpacing), textSize, BLACK);
        RLText::DrawText(TextFormat("Mendiane : %d", selectedIsland->mendiane->GetQuantity()), baseX + padding, baseY + padding + (6 * lineSpacing), textSize, BLACK);
        RLText::DrawText(TextFormat("Phiras : %d", selectedIsland->phiras->GetQuantity()), baseX + padding, baseY + padding + (7 * lineSpacing), textSize, BLACK);
        RLText::DrawText(TextFormat("Thystame : %d", selectedIsland->thystame->GetQuantity()), baseX + padding, baseY + padding + (8 * lineSpacing), textSize, BLACK);
    }

    EndDrawing();
}


std::shared_ptr<Island> Game::GetIslandUnderMouse() {
    for (auto& island : gameMap.GetIslands()) {
        BoundingBox transformedBBox;
        transformedBBox.min = Vector3Add(Vector3Scale(island->GetBoundingBox().min, island->GetScale()), island->GetPosition());
        transformedBBox.max = Vector3Add(Vector3Scale(island->GetBoundingBox().max, island->GetScale()), island->GetPosition());

        RayCollision collision = GetRayCollisionBox(ray, transformedBBox);
        if (collision.hit) {
            return island;
        }
    }
    return nullptr;
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
            island->SetShader(shader);
            gameMap.AddIsland(island);
        }
    }
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

void Game::SetIslandScale(int x, int y, float scale) {
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        island->SetScale(scale);
    }
}

void Game::SetIslandRotation(int x, int y, Vector3 rotationAxis, float rotationAngle) {
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        island->SetRotation(rotationAxis, rotationAngle);
    }
}
