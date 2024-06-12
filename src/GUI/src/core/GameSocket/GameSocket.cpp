/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameSocket
*/

#include "gui.hpp"

void Game::HandleServerMessage(const std::string& message) {
    // std::cout << "Received message: " << message << std::endl;
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    if (command == "msz") {
        int x, y;
        iss >> x >> y;
    } else if (command == "bct") {
        int x, y, q0, q1, q2, q3, q4, q5, q6;
        iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
        UpdateIslandResources(x, y, q0, q1, q2, q3, q4, q5, q6);
    } else if (command == "tna") {
        std::string teamName;
        iss >> teamName;
        this->teamNames.push_back(teamName);
        Utils::removeDuplicates(teamNames);
    } else if (command == "pnw") {
        int n, x, y, o, l;
        std::string teamName;
        iss >> n >> x >> y >> o >> l >> teamName;
        auto island = gameMap.GetIslandByXY(x, y);
        if (island) {
            std::cout << "Player created x: " << x << " y: " << y << std::endl;
            std::cout << "Player number: " << n << " team name: " << teamName << " orientation: " << o << " level: " << l << std::endl;
            auto player = std::make_shared<Player>(n, teamName, x, y, o, l, "src/GUI/assets/Player/robot.glb", island);
            gameMap.AddPlayer(player);
        }
    } else if (command == "ppo") {
        int n, x, y, o;
        iss >> n >> x >> y >> o;
        std::cout << "Player moved x: " << x << " y: " << y << std::endl;
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetOrientation(o);
            player->SetAnimation(Player::Animation::Jump);
            auto newIsland = gameMap.GetIslandByXY(x, y);
            if (newIsland) {
                player->JumpTo(x, y, newIsland, timeUnit * (41.0f / GetFPS())); // Assuming 41 frames at 60 FPS
            }
        }
    } else if (command == "plv") {
        int n, l;
        iss >> n >> l;
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetLevel(l);
        }
    } else if (command == "pin") {
        int n, x, y, q0, q1, q2, q3, q4, q5, q6;
        iss >> n >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
        std::cout << "Player inventory x: " << x << " y: " << y << std::endl;
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->setOBJquantity("food", q0);
            player->setOBJquantity("linemate", q1);
            player->setOBJquantity("deraumere", q2);
            player->setOBJquantity("sibur", q3);
            player->setOBJquantity("mendiane", q4);
            player->setOBJquantity("phiras", q5);
            player->setOBJquantity("thystame", q6);
        }

    } else if (command == "pex") {
        int n;
        iss >> n;
        // Handle player expulsion
    } else if (command == "pbc") {
        int n;
        std::string message;
        iss >> n >> message;
        // Handle broadcast message
    } else if (command == "pic") {
        int x, y, l;
        std::vector<int> players;
        iss >> x >> y >> l;
        int player;
        while (iss >> player) {
            players.push_back(player);
        }
        // Handle start of an incantation
    } else if (command == "pie") {
        int x, y;
        char r;
        iss >> x >> y >> r;
        // Handle end of an incantation
    } else if (command == "pfk") {
        int n;
        iss >> n;
        // Handle egg laying by the player
    } else if (command == "pdr") {
        int n, i;
        iss >> n >> i;
        // Handle resource dropping
    } else if (command == "pgt") {
        int n, i;
        iss >> n >> i;
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetAnimation(Player::Animation::Sit);
            player->WaitForAnimationEnd();
        }
    } else if (command == "pdi") {
        int n;
        iss >> n;
        // Handle player death
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetAnimation(Player::Animation::Death);
            gameMap.GetPlayers().erase(std::remove(gameMap.GetPlayers().begin(), gameMap.GetPlayers().end(), player), gameMap.GetPlayers().end());
        }
    } else if (command == "enw") {
        int e, n, x, y;
        iss >> e >> n >> x >> y;
        // Handle egg was laid by a player
    } else if (command == "ebo") {
        int e;
        iss >> e;
        // Handle player connection for an egg
    } else if (command == "edi") {
        int e;
        iss >> e;
        // Handle death of an egg
    } else if (command == "sgt") {
        int t;
        iss >> t;
        this->timeUnit = t;
    } else if (command == "sst") {
        int t;
        iss >> t;
        this->timeUnit = t;
    } else if (command == "seg") {
        std::string teamName;
        iss >> teamName;
        // Handle end of game
    } else if (command == "smg") {
        std::string message;
        iss >> message;
        // Handle message from the server
    } else if (command == "suc") {
        // Handle unknown command
    } else if (command == "sbp") {
        // Handle command parameter
    }
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
    std::string response = socketManager->SendCommand(command);
    HandleServerMessage(response);
}