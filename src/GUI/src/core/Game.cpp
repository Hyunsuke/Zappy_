/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Game.cpp
*/

#include "gui.hpp"

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {
    InitWindow(screenWidth, screenHeight, "Zappy 3D GUI with raylib");
    SetTargetFPS(60);

    // Initialize objects
    objects.emplace_back(Vector3{ 0.0f, 0.0f, 0.0f }, 2.0f, RED);   // Cube au centre
    objects.emplace_back(Vector3{ 3.0f, 1.0f, 3.0f }, 2.0f, BLUE);  // Cube à une autre position

    std::vector<std::string> texturePaths = {
        "src/GUI/assets/tree_texts/Trunk_4_Cartoon.png",
        "src/GUI/assets/tree_texts/Leafs2.png",
        // Ajoutez d'autres chemins de textures si nécessaire
    };
    modelLoader = new ModelLoader("src/GUI/assets/tree.obj", texturePaths);

    std::cout << "Game initialized with window size: "
              << screenWidth << "x" << screenHeight << std::endl;
}
Game::~Game() {
    delete modelLoader;
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
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(cameraController.GetCamera());

    // Draw a grid at the ground
    DrawGrid(10, 1.0f);

    // // Draw a basic cube to ensure drawing works
    // DrawCube((Vector3){0.0f, 1.0f, 0.0f}, 2.0f, 2.0f, 2.0f, RED);
    // DrawCubeWires((Vector3){0.0f, 1.0f, 0.0f}, 2.0f, 2.0f, 2.0f, MAROON);

    // Draw all objects
    for (auto& object : objects) {
        object.Draw();
    }

    if (modelLoader) {
        modelLoader->Draw((Vector3){5.0f, 1.0f, 5.0f}, 1.0f, WHITE);
    }

    EndMode3D();

    // Draw UI elements
    DrawRectangle(10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 320, 93, BLUE);

    DrawText("Free camera default controls:", 20, 20, 10, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
    DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
    DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

    EndDrawing();
}
