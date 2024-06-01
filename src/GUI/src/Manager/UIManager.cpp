/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** UIManager
*/

#include "gui.hpp"

UIManager::UIManager(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {}

void UIManager::DrawUI(const std::shared_ptr<Island>& selectedIsland, int fps) {
    const int baseX = 10;
    const int baseY = 10;
    const int lineSpacing = 30;
    const int padding = 10;
    const int textSize = 30;
    int lines = 9;

    int rectHeight = (lines * lineSpacing) + (2 * padding);
    int rectWidth = 500;

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
    }
}
