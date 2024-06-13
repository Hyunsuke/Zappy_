/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ReactionFunc
*/

#include "gui.hpp"

void Game::UpdateIslandResources(int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6) {
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        island->food->SetQuantity(q0);
        island->linemate->SetQuantity(q1);
        island->deraumere->SetQuantity(q2);
        island->sibur->SetQuantity(q3);
        island->mendiane->SetQuantity(q4);
        island->phiras->SetQuantity(q5);
        island->thystame->SetQuantity(q6);
    }
}