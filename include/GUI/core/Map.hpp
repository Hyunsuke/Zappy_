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

class Map {
public:
    Map();
    Map(int width, int height);
    ~Map();

    void AddIsland(std::shared_ptr<Island> island);
    void Draw();
    void DrawIslandWires(const std::shared_ptr<Island>& selectedIsland);
    void Update();
    std::shared_ptr<Island> GetIslandByXY(int x, int y);
    std::vector<std::shared_ptr<Island>> GetIslands() const;
    std::string GetMapSize() const;

private:
    std::vector<std::shared_ptr<Island>> islands;
    int width;
    int height;
};

#endif // MAP_HPP_

