/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "CameraController.hpp"
#include "Object3D.hpp"
#include "ModelLoader.hpp"
#include <vector>
#include <iostream>

class Game {
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    void Run();

private:
    void Update();
    void Draw();

    int screenWidth;
    int screenHeight;
    CameraController cameraController;
    std::vector<Object3D> objects;
    ModelLoader* modelLoader;
};

#endif /* !GAME_HPP_ */
