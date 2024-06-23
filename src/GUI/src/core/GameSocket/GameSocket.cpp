/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameSocket
*/

#include "gui.hpp"

void Game::HandleServerMessage(const std::string& message) {
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    auto it = commandHandlers.find(command);
    if (it != commandHandlers.end()) {
        it->second(iss);
    } else {
        HandleUnknownCommand();
    }
}

void Game::InitializeCommandHandlers() {
    commandHandlers = {
        {"msz", [this](std::istringstream& iss) { HandleMapSize(iss); }},
        {"bct", [this](std::istringstream& iss) { HandleTileContent(iss); }},
        {"tna", [this](std::istringstream& iss) { HandleTeamName(iss); }},
        {"pnw", [this](std::istringstream& iss) { HandlePlayerNew(iss); }},
        {"ppo", [this](std::istringstream& iss) { HandlePlayerPosition(iss); }},
        {"plv", [this](std::istringstream& iss) { HandlePlayerLevel(iss); }},
        {"pin", [this](std::istringstream& iss) { HandlePlayerInventory(iss); }},
        {"pex", [this](std::istringstream& iss) { HandlePlayerExpulsion(iss); }},
        {"pbc", [this](std::istringstream& iss) { HandlePlayerBroadcast(iss); }},
        {"pic", [this](std::istringstream& iss) { HandleStartIncantation(iss); }},
        {"pie", [this](std::istringstream& iss) { HandleEndIncantation(iss); }},
        {"pfk", [this](std::istringstream& iss) { HandleEggLaying(iss); }},
        {"pdr", [this](std::istringstream& iss) { HandlePlayerDrop(iss); }},
        {"pgt", [this](std::istringstream& iss) { HandlePlayerTake(iss); }},
        {"pdi", [this](std::istringstream& iss) { HandlePlayerDeath(iss); }},
        {"enw", [this](std::istringstream& iss) { HandleEggLayingPlayer(iss); }},
        {"ebo", [this](std::istringstream& iss) { HandleEggConnection(iss); }},
        {"edi", [this](std::istringstream& iss) { HandleEggDeath(iss); }},
        {"sgt", [this](std::istringstream& iss) { HandleTimeUnitChange(iss); }},
        {"sst", [this](std::istringstream& iss) { HandleTimeUnitChange(iss); }},
        {"seg", [this](std::istringstream& iss) { HandleGameOver(iss); }},
    };
}

void Game::SetSocketManager(std::unique_ptr<SocketManager> socketManager) {
    this->socketManager = std::move(socketManager);
    this->socketManager->SetMessageHandler([this](const std::string& message) {
        HandleServerMessage(message);
    });
}

void Game::RequestMapSize() {
    std::string response = socketManager->SendCommand("msz\n");
    HandleServerMessage(response);
}

void Game::RequestTileContent(int x, int y) {
    std::string command = "bct " + std::to_string(x) + " " + std::to_string(y) + "\n";
    std::string response = socketManager->SendCommand(command);
    HandleServerMessage(response);
}

void Game::RequestMapContent() {
    std::string response = socketManager->SendCommand("mct\n");
    HandleServerMessage(response);
}

void Game::RequestTeamNames() {
    std::string response = socketManager->SendCommand("tna\n");
    HandleServerMessage(response);
}

void Game::RequestPlayerPosition(int playerNumber) {
    std::string command = "ppo #" + std::to_string(playerNumber) + "\n";
    std::string response = socketManager->SendCommand(command);
    HandleServerMessage(response);
}

void Game::RequestPlayerLevel(int playerNumber) {
    std::string command = "plv #" + std::to_string(playerNumber) + "\n";
    std::string response = socketManager->SendCommand(command);
    HandleServerMessage(response);
}

void Game::RequestPlayerInventory(int playerNumber) {
    std::string command = "pin #" + std::to_string(playerNumber) + "\n";
    std::string response = socketManager->SendCommand(command);
    HandleServerMessage(response);
}

void Game::RequestTimeUnit() {
    std::string response = socketManager->SendCommand("sgt\n");
    HandleServerMessage(response);
}

void Game::SetTimeUnit(int timeUnit) {
    std::string command = "sst " + std::to_string(timeUnit) + "\n";
    socketManager->SendMessage(command);
}

int Game::GetTimeUnit() const {
    return timeUnit;
}
