#include "gui.hpp"
#include <cmath>

LoadingScreen::LoadingScreen(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
    sky(screenWidth, screenHeight) {
    image = LoadTexture("src/GUI/assets/Island/SpriteIsland.png");
}

LoadingScreen::~LoadingScreen() {
    UnloadTexture(image);
}

void LoadingScreen::Draw(const std::string& message, float progress) {
    static float time = 0.0f;
    time += GetFrameTime();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    sky.DrawBackground();
    DrawText("Connecting to the server", screenWidth / 2 - MeasureText("Connecting to the server", 40) / 2, screenHeight / 2 - 20, 40, DARKGRAY);
    DrawText(message.c_str(), screenWidth / 2 - MeasureText(message.c_str(), 20) / 2, screenHeight / 2 + 20, 20, DARKGRAY);

    DrawRectangle(screenWidth / 2 - 200, screenHeight / 2 + 60, 400, 30, LIGHTGRAY);
    DrawRectangle(screenWidth / 2 - 200, screenHeight / 2 + 60, static_cast<int>(400 * progress), 30, DARKGRAY);

    float scale = 0.1f;    float offsetY = 10.0f * std::sin(time * 2.0f);
    Vector2 position = { screenWidth - image.width * scale - 20, screenHeight - image.height * scale - 30 + offsetY };
    DrawTextureEx(image, position, 0.0f, scale, WHITE);

    EndDrawing();
}
