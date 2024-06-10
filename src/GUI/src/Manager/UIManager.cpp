/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** UIManager
*/

#include "gui.hpp"

UIManager::UIManager(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {}

void UIManager::DrawUI(const std::shared_ptr<Island>& selectedIsland, int teamCount, int playerCount, int timeUnit, const std::string& mapSize, int fps) {
    DrawIslandInfo(selectedIsland, fps);
    DrawAdditionalInfo(teamCount, playerCount, timeUnit, mapSize);
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

    DrawRectangle(baseX, baseY, rectWidth, rectHeight, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(baseX, baseY, rectWidth, rectHeight, BLUE);

    DrawText(TextFormat("FPS: %d", fps), baseX + padding, baseY + padding, textSize, BLACK);

    if (selectedIsland) {
        DrawText(TextFormat("Selected Island Pos : %d, %d", selectedIsland->GetX(), selectedIsland->GetY()), baseX + padding, baseY + padding + lineSpacing, textSize, BLACK);
        DrawText(TextFormat("Food : %d", selectedIsland->food->GetQuantity()), baseX + padding, baseY + padding + (2 * lineSpacing), textSize, BLACK);
        DrawText(TextFormat("Linemate : %d", selectedIsland->linemate->GetQuantity()), baseX + padding, baseY + padding + (3 * lineSpacing), textSize, BLACK);
        DrawText(TextFormat("Deraumere : %d", selectedIsland->deraumere->GetQuantity()), baseX + padding, baseY + padding + (4 * lineSpacing), textSize, BLACK);
        DrawText(TextFormat("Sibur : %d", selectedIsland->sibur->GetQuantity()), baseX + padding, baseY + padding + (5 * lineSpacing), textSize, BLACK);
        DrawText(TextFormat("Mendiane : %d", selectedIsland->mendiane->GetQuantity()), baseX + padding, baseY + padding + (6 * lineSpacing), textSize, BLACK);
        DrawText(TextFormat("Phiras : %d", selectedIsland->phiras->GetQuantity()), baseX + padding, baseY + padding + (7 * lineSpacing), textSize, BLACK);
        DrawText(TextFormat("Thystame : %d", selectedIsland->thystame->GetQuantity()), baseX + padding, baseY + padding + (8 * lineSpacing), textSize, BLACK);
        DrawText(TextFormat("Egg : %d", selectedIsland->egg->GetQuantity()), baseX + padding, baseY + padding + (9 * lineSpacing), textSize, BLACK);
    }
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

    DrawRectangle(baseX, baseY, rectWidth, rectHeight, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(baseX, baseY, rectWidth, rectHeight, BLUE);

    DrawText(TextFormat("Teams: %d", teamCount), baseX + padding, baseY + padding, textSize, BLACK);
    DrawText(TextFormat("Players: %d", playerCount), baseX + padding, baseY + padding + lineSpacing, textSize, BLACK);
    DrawText(TextFormat("Time Unit: %d", timeUnit), baseX + padding, baseY + padding + (2 * lineSpacing), textSize, BLACK);
    DrawText(TextFormat("Map Size: %s", mapSize.c_str()), baseX + padding, baseY + padding + (3 * lineSpacing), textSize, BLACK);
}
