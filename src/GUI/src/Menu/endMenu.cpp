#include "gui.hpp"

EndMenu::EndMenu(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      sky(screenWidth, screenHeight) {}

void EndMenu::Draw(const std::string& winningTeam) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    sky.DrawBackground();

    BeginMode3D(camera);

    EndMode3D();

    DrawText("Game Is Over", screenWidth / 2 - MeasureText("Game Is Over", 100) / 2, screenHeight / 4, 100, BLACK);
    DrawText(("Winning Team: " + winningTeam + " !").c_str(), screenWidth / 2 - MeasureText(("Winning Team: " + winningTeam + " !").c_str(), 60) / 2, screenHeight / 2, 60, LIGHTGRAY);

    Rectangle CloseButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 150), 100.0f, 40.0f};
    DrawButton(CloseButton, "Close", 20);

    EndDrawing();
}

void EndMenu::HandleMouseInput(Vector2 mousePosition) {
    Rectangle CloseButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 150), 100.0f, 40.0f};
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (IsMouseOverButton(CloseButton)) {
            CloseWindow();
            std::exit(0);
        }
    }
}

bool EndMenu::IsMouseOverButton(Rectangle button) {
    Vector2 mousePoint = GetMousePosition();
    return CheckCollisionPointRec(mousePoint, button);
}
