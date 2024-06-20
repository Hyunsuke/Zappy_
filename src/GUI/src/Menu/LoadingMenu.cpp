#include "gui.hpp"
#include <cmath>

LoadingMenu::LoadingMenu(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
    sky(screenWidth, screenHeight) {
    image = LoadTexture("src/GUI/assets/Island/SpriteIsland.png");
    imageStudio = LoadTexture("src/GUI/assets/studio/SpriteStudio.png");
    SetTargetFPS(60);
}

LoadingMenu::~LoadingMenu() {
    UnloadTexture(image);
}

void LoadingMenu::Draw()
{
    static float time = 0.0f;
    time += GetFrameTime();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    sky.DrawBackground();

    float scale = 0.1f;    float offsetY = 10.0f * std::sin(time * 2.0f);
    Vector2 position = { screenWidth - image.width * scale - 20, screenHeight - image.height * scale - 30 + offsetY };
    DrawTextureEx(image, position, 0.0f, scale, WHITE);

    DrawTextureEx(imageStudio, position, 0.0f, 1.0f, WHITE);

    EndDrawing();
}
