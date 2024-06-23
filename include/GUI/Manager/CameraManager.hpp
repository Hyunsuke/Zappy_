/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** CameraManager
*/


#ifndef CAMERAMANAGER_HPP_
#define CAMERAMANAGER_HPP_

#include "gui.hpp"

class CameraManager {
public:
    CameraManager(CameraController& cameraController, Map& gameMap);
    void Update(std::shared_ptr<Player>& selectedPlayer, std::shared_ptr<Island>& selectedIsland);

private:
    CameraController& cameraController;
    Map& gameMap;
    bool isCameraLocked;
    int currentPlayerIndex;
    bool lastKeyPressedP;
};

#endif // CAMERAMANAGER_HPP_
