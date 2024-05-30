/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Game.cpp
*/

#include "gui.hpp"

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), modelLoader(nullptr), cursorColor(WHITE) {
    InitWindow(screenWidth, screenHeight, "Zappy 3D GUI with raylib");
    SetTargetFPS(60);

    modelLoader = new ModelLoader("src/GUI/assets/duck/RubberDuck_LOD0.obj");
    modelLoader->SetTexture("src/GUI/assets/duck/duck_text.png");

    Shader shader = LoadShader("src/GUI/assets/shaders/lighting.vs", "src/GUI/assets/shaders/lighting.fs");
    modelLoader->SetShader(shader);

    // Configure shader
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

    modelBBox = GetMeshBoundingBox(modelLoader->GetModel().meshes[0]);

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

    // Get the picking ray from mouse position
    ray = GetMouseRay(GetMousePosition(), cameraController.GetCamera());
    collision.hit = false;
    cursorColor = WHITE;
    strcpy(hitObjectName, "None");

    // Define the model position and scale
    Vector3 modelPosition = { 5.0f, 1.0f, 5.0f };
    float modelScale = 0.1f;

    // Transform the bounding box to account for the model's position and scale
    BoundingBox transformedBBox;
    transformedBBox.min = Vector3Add(Vector3Scale(modelBBox.min, modelScale), modelPosition);
    transformedBBox.max = Vector3Add(Vector3Scale(modelBBox.max, modelScale), modelPosition);

    // Check collision with the transformed bounding box
    RayCollision modelBoxCollision = GetRayCollisionBox(ray, transformedBBox);
    if (modelBoxCollision.hit && (!collision.hit || modelBoxCollision.distance < collision.distance)) {
        collision = modelBoxCollision;
        cursorColor = BLUE;
        strcpy(hitObjectName, "Model Box");
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(cameraController.GetCamera());

    // Draw a grid at the ground
    DrawGrid(10, 1.0f);

    // Define the model position and scale
    Vector3 modelPosition = { 5.0f, 1.0f, 5.0f };
    float modelScale = 0.1f;

    // Draw the model
    if (modelLoader) {
        modelLoader->Draw(modelPosition, modelScale, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f, WHITE);
    }

    if (collision.hit) {
        glLineWidth(1000.0f);  // Set the line width to 3 pixels (or any desired width)
        DrawModelWiresEx(modelLoader->GetModel(), modelPosition, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f, (Vector3){modelScale, modelScale, modelScale}, BLACK);
        glLineWidth(1.0f);  // Reset the line width to default (1 pixel)
    }

    // Transform the bounding box to account for the model's position and scale
    BoundingBox transformedBBox;
    transformedBBox.min = Vector3Add(Vector3Scale(modelBBox.min, modelScale), modelPosition);
    transformedBBox.max = Vector3Add(Vector3Scale(modelBBox.max, modelScale), modelPosition);

    // Draw bounding box for the model
    // DrawBoundingBox(transformedBBox, LIME);

    // If there is a collision, draw the collision point and normal
    if (collision.hit) {
        DrawCube(collision.point, 0.3f, 0.3f, 0.3f, cursorColor);
        DrawCubeWires(collision.point, 0.3f, 0.3f, 0.3f, RED);

        Vector3 normalEnd;
        normalEnd.x = collision.point.x + collision.normal.x;
        normalEnd.y = collision.point.y + collision.normal.y;
        normalEnd.z = collision.point.z + collision.normal.z;

        DrawLine3D(collision.point, normalEnd, RED);
    }

    EndMode3D();

    // Draw UI elements
    DrawRectangle(10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 320, 93, BLUE);

    DrawText("Free camera default controls:", 20, 20, 10, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
    DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
    DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

    // Draw debug information
    DrawText(TextFormat("Hit Object: %s", hitObjectName), 10, 110, 10, BLACK);
    if (collision.hit) {
        int ypos = 130;
        DrawText(TextFormat("Distance: %3.2f", collision.distance), 10, ypos, 10, BLACK);
        DrawText(TextFormat("Hit Pos: %3.2f %3.2f %3.2f",
                            collision.point.x,
                            collision.point.y,
                            collision.point.z), 10, ypos + 15, 10, BLACK);
        DrawText(TextFormat("Hit Norm: %3.2f %3.2f %3.2f",
                            collision.normal.x,
                            collision.normal.y,
                            collision.normal.z), 10, ypos + 30, 10, BLACK);
    }

    EndDrawing();
}