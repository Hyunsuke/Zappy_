/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** CameraManager
*/

#include "gui.hpp"

CameraManager::CameraManager(CameraController& cameraController, Map& gameMap)
    : cameraController(cameraController), gameMap(gameMap), isCameraLocked(false), currentPlayerIndex(0), lastKeyPressedP(false) {}

void CameraManager::Update(std::shared_ptr<Player>& selectedPlayer, std::shared_ptr<Island>& selectedIsland) {
    auto players = gameMap.GetPlayers();

    if (IsKeyPressed(KEY_P)) {
        if (!players.empty()) {
            if (isCameraLocked) {
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            } else {
                isCameraLocked = true;
                if (!lastKeyPressedP) {
                    cameraController.SetOriginalCameraPosition(cameraController.GetCamera().position, cameraController.GetCamera().target);
                }
            }
            cameraController.LockCameraOnPlayer(players[currentPlayerIndex]);
            selectedPlayer = players[currentPlayerIndex];
            if (players[currentPlayerIndex]->GetIsland())
                selectedIsland = players[currentPlayerIndex]->GetIsland();
            lastKeyPressedP = true;
        }
    }

    if (IsKeyPressed(KEY_O)) {
        if (isCameraLocked) {
            lastKeyPressedP = false;
            cameraController.UnlockCamera();
            isCameraLocked = false;
        }
    }

    if (isCameraLocked) {
        if (!players.empty()) {
            cameraController.UpdateLockedCamera(players[currentPlayerIndex]);
        }
    } else {
        cameraController.Update();
    }
}