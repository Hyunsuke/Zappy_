/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main.cpp
*/

#include "gui.hpp"

void init_Window(int screenWidth, int screenHeight, const char* title) {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
}

bool runMenu(int& screenWidth, int& screenHeight, std::string& host, int& port) {
    Menu menu(screenWidth, screenHeight);
    menu.Run();
    if (menu.ShouldStartGame()) {
        host = menu.GetHost();
        port = menu.GetPort();
        screenHeight = menu.GetScreenHeight();
        screenWidth = menu.GetScreenWidth();
        return true;
    }
    return false;
}

bool connectToServer(const std::string& host, int port, std::unique_ptr<SocketManager>& socketManager) {
    socketManager = std::make_unique<SocketManager>(host, port);
    socketManager->Connect();
    if (!socketManager->IsRunning()) {
        std::cerr << "Failed to connect to the server" << std::endl;
        return false;
    }
    return true;
}

bool processInitialServerMessages(SocketManager& socketManager, std::string& mapSize, int& timeUnit, std::vector<std::string>& teamNames, std::vector<std::string>& mapContent, std::vector<std::string>& eggs, int timeoutSeconds = 5) {
    auto start = std::chrono::steady_clock::now();

    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        if (elapsed > timeoutSeconds) {
            throw GameException("Timeout waiting for initial server messages");
            return false;
        }

        std::string message = socketManager.ReceiveMessage();
        std::istringstream iss(message);
        std::string command;
        iss >> command;

        if (command == "msz") {
            mapSize = message;
        } else if (command == "sgt") {
            iss >> timeUnit;
        } else if (command == "tna") {
            std::string teamName;
            iss >> teamName;
            teamNames.push_back(teamName);
        } else if (command == "bct") {
            mapContent.push_back(message);
        } else if (command == "enw") {
            eggs.push_back(message);
        }

        if (!mapSize.empty() && timeUnit > 0 && !teamNames.empty() && !mapContent.empty() && elapsed > 1) {
            Utils::removeDuplicates(mapContent);
            Utils::removeDuplicates(eggs);
            Utils::removeDuplicates(teamNames);
            break;
        }

    }
    return true;
}

void runGame(int screenWidth, int screenHeight, const std::string& mapSize, int timeUnit, const std::vector<std::string>& teamNames, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs, std::unique_ptr<SocketManager>& socketManager) {
    Game game(screenWidth, screenHeight, mapSize, timeUnit, teamNames, mapContent, eggs);
    game.SetSocketManager(std::move(socketManager));
    game.Run();
}

int main() {
    try {
        int screenWidth = 1920;
        int screenHeight = 1080;
        init_Window(screenWidth, screenHeight, "Zappy GUI");

        std::string host;
        int port;

        if (runMenu(screenWidth, screenHeight, host, port)) {
            std::unique_ptr<SocketManager> socketManager;

            if (connectToServer(host, port, socketManager)) {
                std::string mapSize;
                int timeUnit = 0;
                std::vector<std::string> teamNames;
                std::vector<std::string> mapContent;
                std::vector<std::string> eggs;

                if (processInitialServerMessages(*socketManager, mapSize, timeUnit, teamNames, mapContent, eggs)) {
                    runGame(screenWidth, screenHeight, mapSize, timeUnit, teamNames, mapContent, eggs, socketManager);
                }
            }
        }
    } catch (const GameException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        CloseWindow();
        return 84;
    }
    CloseWindow();
    return 0;
}