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
    UnloadTexture(imageStudio);
}

void LoadingMenu::Draw()
{
    static float time = 0.0f;
    time += GetFrameTime();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    sky.DrawBackground();

    float scale = 0.1f;
    float offsetY = 10.0f * std::sin(time * 2.0f);
    Vector2 position1 = { screenWidth - image.width * scale - 20, screenHeight - image.height * scale - 30 + offsetY };
    DrawTextureEx(image, position1, 0.0f, scale, WHITE);

    Vector2 position2 = { screenWidth / 2 - imageStudio.width * 2.0f / 2, screenHeight / 2 - imageStudio.height * 2.0f / 2 };
    DrawTextureEx(imageStudio, position2, 0.0f, 2.0f, WHITE);

    EndDrawing();
}
