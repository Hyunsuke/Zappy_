/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Game.cpp
*/

#include "gui.hpp"

Game::Game(int screenWidth, int screenHeight, int mapWidth, int mapHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), gameMap(mapWidth,mapHeight), cursorColor(WHITE) {
    InitWindow(screenWidth, screenHeight, "Zappy 3D GUI with raylib");
    SetTargetFPS(60);

    // Load the shader
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

    std::cout << "Game initialized with window size: "
              << screenWidth << "x" << screenHeight << std::endl;
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

    // Get the picking ray from mouse position
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
    ClearBackground(RAYWHITE);

    BeginMode3D(cameraController.GetCamera());

    // Draw the game map
    gameMap.Draw();

    if (selectedIsland) {
         glLineWidth(100.0f);
        DrawModelWiresEx(selectedIsland->GetModel(), selectedIsland->GetPosition(), selectedIsland->GetRotationAxis(), selectedIsland->GetRotationAngle(), Vector3{selectedIsland->GetScale(), selectedIsland->GetScale(), selectedIsland->GetScale()}, RED);
        for (const auto& obj : selectedIsland->GetObjects()) {
            DrawModelWiresEx(obj->GetModel(), obj->GetPosition(), obj->GetRotationAxis(), obj->GetRotationAngle(), Vector3{obj->GetScale(), obj->GetScale(), obj->GetScale()}, RED);
        }
         glLineWidth(1.0f);
    }

    EndMode3D();

    // Draw UI elements
    DrawRectangle(10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 320, 93, BLUE);

    if (selectedIsland) {
        DrawText(TextFormat("Selected Island ID: %d", selectedIsland->GetId()), 20, 20, 10, BLACK);
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
    float spacing = 10.0f;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            Vector3 position = {i * spacing, 0.0f, j * spacing};
            float scale = 0.2f; // Set the desired scale here
            Vector3 rotationAxis = {0.0f, 1.0f, 0.0f}; // Set the desired rotation axis here
            float rotationAngle = 0.0f; // Set the desired rotation angle here
            auto island = std::make_shared<Island>(i * width + j, position, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", scale, rotationAxis, rotationAngle);
            island->SetShader(shader);
            gameMap.AddIsland(island);
        }
    }
}

void Game::ToggleObjectActive(int islandId, const std::string& objectType, bool active) {
    auto island = gameMap.GetIslandById(islandId);
    if (island) {
        if (objectType == "food") {
            island->food->SetActive(active);
        } else if (objectType == "linemate") {
            island->linemate->SetActive(active);
        } else if (objectType == "deraumere") {
            island->deraumere->SetActive(active);
        } else if (objectType == "sibur") {
            island->sibur->SetActive(active);
        } else if (objectType == "mendiane") {
            island->mendiane->SetActive(active);
        } else if (objectType == "phiras") {
            island->phiras->SetActive(active);
        } else if (objectType == "thystame") {
            island->thystame->SetActive(active);
        }
    }
}

void Game::SetIslandScale(int islandId, float scale) {
    auto island = gameMap.GetIslandById(islandId);
    if (island) {
        island->SetScale(scale);
    }
}

void Game::SetIslandRotation(int islandId, Vector3 rotationAxis, float rotationAngle) {
    auto island = gameMap.GetIslandById(islandId);
    if (island) {
        island->SetRotation(rotationAxis, rotationAngle);
    }
}
