/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Map.cpp
*/

#include "gui.hpp"

Map::Map() : width(0), height(0) {}

Map::Map(int width, int height) :
    width(width),
    height(height)
{}

Map::~Map() {}

void Map::AddIsland(std::shared_ptr<Island> island) {
    islands.push_back(island);
}

void Map::AddPlayer(std::shared_ptr<Player> player) {
    players.push_back(player);
}


void Map::Draw() {
    for (auto& island : islands) {
        island->Draw();
    }
    for (auto& player : players) {
        player->Draw();
    }
}

void Map::DrawIslandWires(const std::shared_ptr<Island>& selectedIsland) {
    if (!selectedIsland)
        return;
    for (auto& island : islands) {
        if (island == selectedIsland) {
            island->DrawWires();
        }
    }
}

void Map::DrawPlayerWires(const std::shared_ptr<Player>& selectedPlayer) {
    if (!selectedPlayer)
        return;
    for (auto& player : players) {
        if (player == selectedPlayer) {
            player->DrawWires();
        }
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
    for (auto& player : players) {
        if (player) {
            player->UpdateAnimation();
            player->UpdatePosition();
        }
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

std::shared_ptr<Player> Map::GetPlayerByNumber(int playerNumber) {
    for (auto& player : players) {
        if (player->GetPlayerNumber() == playerNumber) {
            return player;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Island>> Map::GetIslands() const {
    return islands;
}

std::vector<std::shared_ptr<Player>> Map::GetPlayers() const {
    return players;
}

int Map::GetPlayerCount() const {
    return players.size();
}

std::string Map::GetMapSize() const {
    return std::to_string(width) + "x" + std::to_string(height);
}