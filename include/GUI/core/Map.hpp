/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Island.hpp"
#include <vector>
#include <memory>
#include "Player/Player.hpp"
#include "../Wrapper/Raylib/RLModel.hpp"
#include <atomic>

class Map {
public:
    Map();
    Map(int width, int height);
    ~Map();

    void AddIsland(std::shared_ptr<Island> island);
    void AddPlayer(std::shared_ptr<Player> player);
    void Draw();
    void DrawIslandWires(const std::shared_ptr<Island>& selectedIsland);
    void DrawPlayerWires(const std::shared_ptr<Player>& selectedPlayer);
    void Update();
    std::shared_ptr<Island> GetIslandByXY(int x, int y);
    std::vector<std::shared_ptr<Island>> GetIslands() const;
    std::vector<std::shared_ptr<Player>> GetPlayers() const;
    std::string GetMapSize() const;
    int GetPlayerCount() const;
    std::shared_ptr<Player> GetPlayerByNumber(int playerNumber);
    void RemoveEgg(int eggId);
    Map& operator=(const Map& other);

private:
    std::vector<std::shared_ptr<Island>> islands;
    int width;
    int height;
    std::vector<std::shared_ptr<Player>> players;
    std::atomic_flag playersLock = ATOMIC_FLAG_INIT;
    RLModel model;
};

#endif // MAP_HPP_

