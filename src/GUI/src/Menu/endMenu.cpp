#include "gui.hpp"

EndMenu::EndMenu(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      sky(screenWidth, screenHeight) {}

void EndMenu::Draw(const std::string& winningTeam) {
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);

    sky.DrawBackground();

    window.BeginMode3D(camera);

    window.EndMode3D();

    rlText.DrawText("Game Is Over", screenWidth / 2 - rlText.MeasureText("Game Is Over", 100) / 2, screenHeight / 4, 100, BLACK);
    rlText.DrawText(("Winning Team: " + winningTeam + " !").c_str(), screenWidth / 2 - rlText.MeasureText(("Winning Team: " + winningTeam + " !").c_str(), 60) / 2, screenHeight / 2, 60, LIGHTGRAY);

    Rectangle CloseButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 150), 100.0f, 40.0f};
    rlText.DrawButton(CloseButton, "Close", 20);

    window.EndDrawing();
}

void EndMenu::HandleMouseInput() {
    Rectangle CloseButton = {(float)(screenWidth / 2 - 50), (float)(screenHeight - 150), 100.0f, 40.0f};
    if (rlText.IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (IsMouseOverButton(CloseButton)) {
            window.CloseWindow();
            std::exit(0);
        }
    }
}

bool EndMenu::IsMouseOverButton(Rectangle button) {
    Vector2 mousePoint = rlText.GetMousePosition();
    return rlText.CheckCollisionPointRec(mousePoint, button);
}
