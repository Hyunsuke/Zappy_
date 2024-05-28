/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Game.cpp
*/

#include "gui.hpp"

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), modelLoader(nullptr) {
    InitWindow(screenWidth, screenHeight, "Zappy 3D GUI with raylib");
    SetTargetFPS(60);

    // Initialize objects
    objects.emplace_back(Vector3{ 0.0f, 1.0f, 0.0f }, 2.0f, RED);   // Cube au centre
    objects.emplace_back(Vector3{ 3.0f, 1.0f, 3.0f }, 2.0f, BLUE);  // Cube à une autre position

    modelLoader = new ModelLoader("src/GUI/assets/tree_texts/Low_Poly_Tree_Blender.glb"); // Chargez votre modèle GLB ici

    // if (modelLoader->GetModel().materialCount > 0) {
    //     std::cout << "Material count: " << modelLoader->GetModel().materialCount << std::endl;
    //     modelLoader->GetModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].color = (Color){0, 255, 0, 255}; // Rouge
    // }
    // if (modelLoader->GetModel().materialCount > 1) {
    //     modelLoader->GetModel().materials[1].maps[MATERIAL_MAP_DIFFUSE].color = (Color){0, 255, 0, 255}; // Vert
    // }

    // Load shader
    // Shader shader = LoadShader("src/GUI/assets/shaders/lighting.vs", "src/GUI/assets/shaders/lighting.fs");
    // modelLoader->SetShader(shader);

    // // Configure shader
    // int lightPosLoc = GetShaderLocation(shader, "lightPosition");
    // int viewPosLoc = GetShaderLocation(shader, "viewPosition");
    // int lightColorLoc = GetShaderLocation(shader, "lightColor");
    // int ambientColorLoc = GetShaderLocation(shader, "ambientColor");

    // Vector3 lightPosition = { 10.0f, 10.0f, 10.0f };
    // Vector3 viewPosition = { 0.0f, 10.0f, 10.0f };
    // Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    // Vector3 ambientColor = { 0.2f, 0.2f, 0.2f };

    // SetShaderValue(shader, lightPosLoc, &lightPosition, SHADER_UNIFORM_VEC3);
    // SetShaderValue(shader, viewPosLoc, &viewPosition, SHADER_UNIFORM_VEC3);
    // SetShaderValue(shader, lightColorLoc, &lightColor, SHADER_UNIFORM_VEC3);
    // SetShaderValue(shader, ambientColorLoc, &ambientColor, SHADER_UNIFORM_VEC3);

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

    // Draw all objects
    for (auto& object : objects) {
        object.Draw();
    }

    if (modelLoader) {
        modelLoader->Draw((Vector3){5.0f, 1.0f, 5.0f}, 0.1f, (Vector3){1.0f, 0.0f, 0.0f}, 90.0f, WHITE); // Rotation de 45 degrés autour de l'axe Y
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
