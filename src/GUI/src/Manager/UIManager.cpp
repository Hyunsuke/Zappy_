/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** UIManager
*/

#include "gui.hpp"

UIManager::UIManager(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {
    UpdateButtonPositions();
}

void UIManager::UpdateButtonPositions() {
    settingsButton = { (float)(screenWidth - 220), (float)(screenHeight - 50), 100, 40 };
    closeButton = { (float)(screenWidth - 110), (float)(screenHeight - 50), 100, 40 };
}

void UIManager::OnWindowResized(int newScreenWidth, int newScreenHeight) {
    screenWidth = newScreenWidth;
    screenHeight = newScreenHeight;
    UpdateButtonPositions();
}

void UIManager::DrawUI(const std::shared_ptr<Island>& selectedIsland, const std::shared_ptr<Player>& selectedPlayer, int teamCount, int playerCount, int timeUnit, const std::string& mapSize, int fps) {
    DrawIslandInfo(selectedIsland, fps);
    if (selectedPlayer) {
        DrawPlayerInfo(selectedPlayer);
    }
    DrawAdditionalInfo(teamCount, playerCount, timeUnit, mapSize);
    DrawButtons();
}

void UIManager::DrawIslandInfo(const std::shared_ptr<Island>& selectedIsland, int fps) {
    const int padding = screenHeight * 0.01;
    const int lineSpacing = screenHeight * 0.03;
    const int textSize = screenHeight * 0.03;
    const int baseX = padding;
    const int baseY = padding;
    int lines = 10;

    int rectHeight = (lines * lineSpacing) + (2 * padding);
    int rectWidth = screenWidth * 0.25;

    Color bgColor = Fade(DARKBLUE, 0.5f);
    DrawRectangle(baseX, baseY, rectWidth, rectHeight, bgColor);
    DrawRectangleLines(baseX, baseY, rectWidth, rectHeight, BLUE);

    rlText.DrawText(rlText.TextFormat("FPS: %d", fps), baseX + padding, baseY + padding, textSize, BLACK);

    if (selectedIsland) {
        rlText.DrawText(rlText.TextFormat("Selected Island Pos : %d, %d", selectedIsland->GetX(), selectedIsland->GetY()), baseX + padding, baseY + padding + lineSpacing, textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Food : %d", selectedIsland->food->GetQuantity()), baseX + padding, baseY + padding + (2 * lineSpacing), textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Linemate : %d", selectedIsland->linemate->GetQuantity()), baseX + padding, baseY + padding + (3 * lineSpacing), textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Deraumere : %d", selectedIsland->deraumere->GetQuantity()), baseX + padding, baseY + padding + (4 * lineSpacing), textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Sibur : %d", selectedIsland->sibur->GetQuantity()), baseX + padding, baseY + padding + (5 * lineSpacing), textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Mendiane : %d", selectedIsland->mendiane->GetQuantity()), baseX + padding, baseY + padding + (6 * lineSpacing), textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Phiras : %d", selectedIsland->phiras->GetQuantity()), baseX + padding, baseY + padding + (7 * lineSpacing), textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Thystame : %d", selectedIsland->thystame->GetQuantity()), baseX + padding, baseY + padding + (8 * lineSpacing), textSize, BLACK);
        rlText.DrawText(rlText.TextFormat("Egg : %d", selectedIsland->GetEggs().size()), baseX + padding, baseY + padding + (9 * lineSpacing), textSize, BLACK);
    }
}

void UIManager::DrawPlayerInfo(const std::shared_ptr<Player>& selectedPlayer) {
    const int padding = screenHeight * 0.01;
    const int lineSpacing = screenHeight * 0.03;
    const int textSize = screenHeight * 0.03;
    const int baseX = padding;
    const int baseY = screenHeight * 0.4;
    int lines = 11;

    int rectHeight = (lines * lineSpacing) + (2 * padding);
    int rectWidth = screenWidth * 0.25;

    Color bgColor = rlText.Fade(SKYBLUE, 0.5f);
    rlText.DrawRectangle(baseX, baseY, rectWidth, rectHeight, bgColor);
    rlText.DrawRectangleLines(baseX, baseY, rectWidth, rectHeight, BLUE);

    rlText.DrawText(rlText.TextFormat("Selected Player Pos : %d, %d", selectedPlayer->getX(), selectedPlayer->getY()), baseX + padding, baseY + padding, textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Player Number : %d", selectedPlayer->GetPlayerNumber()), baseX + padding, baseY + padding + lineSpacing, textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Player Level : %d", selectedPlayer->GetLevel()), baseX + padding, baseY + padding + (2 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Player Team : %s", selectedPlayer->GetTeam().c_str()), baseX + padding, baseY + padding + (3 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Food : %d", selectedPlayer->getOBJquantity("food")), baseX + padding, baseY + padding + (4 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Linemate : %d", selectedPlayer->getOBJquantity("linemate")), baseX + padding, baseY + padding + (5 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Deraumere : %d", selectedPlayer->getOBJquantity("deraumere")), baseX + padding, baseY + padding + (6 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Sibur : %d", selectedPlayer->getOBJquantity("sibur")), baseX + padding, baseY + padding + (7 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Mendiane : %d", selectedPlayer->getOBJquantity("mendiane")), baseX + padding, baseY + padding + (8 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Phiras : %d", selectedPlayer->getOBJquantity("phiras")), baseX + padding, baseY + padding + (9 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Thystame : %d", selectedPlayer->getOBJquantity("thystame")), baseX + padding, baseY + padding + (10 * lineSpacing), textSize, BLACK);
}

void UIManager::DrawAdditionalInfo(int teamCount, int playerCount, int timeUnit, const std::string& mapSize) {
    const int padding = screenHeight * 0.01;
    const int lineSpacing = screenHeight * 0.03;
    const int textSize = screenHeight * 0.03;
    const int baseX = screenWidth - screenWidth * 0.25 - padding;
    const int baseY = padding;
    int lines = 4;

    int rectHeight = (lines * lineSpacing) + (2 * padding);
    int rectWidth = screenWidth * 0.25;

    rlText.DrawRectangle(baseX, baseY, rectWidth, rectHeight, rlText.Fade(SKYBLUE, 0.5f));
    rlText.DrawRectangleLines(baseX, baseY, rectWidth, rectHeight, BLUE);

    rlText.DrawText(rlText.TextFormat("Teams: %d", teamCount), baseX + padding, baseY + padding, textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Players: %d", playerCount), baseX + padding, baseY + padding + lineSpacing, textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Time Unit: %d", timeUnit), baseX + padding, baseY + padding + (2 * lineSpacing), textSize, BLACK);
    rlText.DrawText(rlText.TextFormat("Map Size: %s", mapSize.c_str()), baseX + padding, baseY + padding + (3 * lineSpacing), textSize, BLACK);
}

void UIManager::DrawButtons() {
    if (rlText.IsMouseOverButton(settingsButton)) {
        if (rlText.IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            settingsButtonColor = GREEN;
        } else {
            settingsButtonColor = YELLOW;
        }
    } else {
        settingsButtonColor = LIGHTGRAY;
    }

    if (rlText.IsMouseOverButton(closeButton)) {
        if (rlText.IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            closeButtonColor = GREEN;
        } else {
            closeButtonColor = YELLOW;
        }
    } else {
        closeButtonColor = LIGHTGRAY;
    }

    rlText.DrawRectangleRec(settingsButton, settingsButtonColor);
    rlText.DrawRectangleLinesEx(settingsButton, 2, DARKGRAY);
    rlText.DrawText("Settings", settingsButton.x + 10, settingsButton.y + 10, 20, BLACK);

    rlText.DrawRectangleRec(closeButton, closeButtonColor);
    rlText.DrawRectangleLinesEx(closeButton, 2, DARKGRAY);
    rlText.DrawText("Close", closeButton.x + 20, closeButton.y + 10, 20, BLACK);
}

bool UIManager::IsMouseOverButton(Rectangle button) {
    Vector2 mousePoint = rlText.GetMousePosition();
    return rlText.CheckCollisionPointRec(mousePoint, button);
}

bool UIManager::IsButtonClicked(Rectangle button) {
    return rlText.IsMouseOverButton(button) && rlText.IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
