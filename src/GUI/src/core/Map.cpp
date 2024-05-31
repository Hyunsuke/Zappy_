/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Map.cpp
*/

#include "gui.hpp"

Map::Map(int width, int height) : width(width), height(height) {}

Map::~Map() {}

void Map::AddIsland(std::shared_ptr<Island> island) {
    islands.push_back(island);
}

void Map::Draw() {
    for (auto& island : islands) {
        island->Draw();
    }
}

void Map::Update() {
    float time = GetTime();
    for (auto& island : islands) {
        float offset = 0.5f * sin(time + (island->GetX() * 0.3f) + (island->GetY() * 0.3f));
        Vector3 position = island->GetPosition();
        position.y = offset;
        island->Move(position);
    }
}


std::shared_ptr<Island> Map::GetIslandByXY(int x, int y) {
    for (auto& island : islands) {
        if (island->GetX() == x && island->GetY() == y) {
            return island;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Island>> Map::GetIslands() const {
    return islands;
}
