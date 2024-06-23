/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** LoadingMenu
*/

#include "gui.hpp"
#include <cmath>

LoadingMenu::LoadingMenu(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      sky(screenWidth, screenHeight) {
    image = TextureCollector::GetInstance().LoadTexture("src/GUI/assets/Island/SpriteIsland.png");
    imageStudio = TextureCollector::GetInstance().LoadTexture("src/GUI/assets/studio/SpriteStudio.png");
    window.SetTargetFPS(60);
}

void LoadingMenu::Draw() {
    static float time = 0.0f;
    time += rlText.GetFrameTime();

    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);
    sky.DrawBackground();

    float scale = 0.1f;
    float offsetY = 10.0f * std::sin(time * 2.0f);
    Vector2 position1 = { screenWidth - image->width * scale - 20, screenHeight - image->height * scale - 30 + offsetY };
    rlmodel.DrawTextureEx(image, position1, 0.0f, scale, WHITE);

    Vector2 position2 = { screenWidth / 2 - imageStudio->width * 2.0f / 2, screenHeight / 2 - imageStudio->height * 2.0f / 2 };
    rlmodel.DrawTextureEx(imageStudio, position2, 0.0f, 2.0f, WHITE);

    window.EndDrawing();
}
