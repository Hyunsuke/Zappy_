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
            auto player = std::make_shared<Player>(n, teamName, x, y, o, l, "src/GUI/assets/Player/robot.glb", island);
            gameMap.AddPlayer(player);
            island->AddPlayer(player);
        }
    } else if (command == "ppo") {
        int n, x, y, o;
        iss >> n >> x >> y >> o;
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetOrientation(o);
            auto currentIsland = player->GetIsland();
            auto newIsland = gameMap.GetIslandByXY(x, y);
            if (currentIsland != newIsland) {
                if (currentIsland) {
                    currentIsland->RemovePlayer(player);
                }
                if (newIsland) {
                    newIsland->AddPlayer(player);
                    player->JumpTo(newIsland, 7.0f / timeUnit);
                }
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
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetAnimation(Player::Animation::Punch);
            player->WaitForAnimationEnd(Player::Animation::Idle);
        }
    } else if (command == "pbc") {
        int n;
        std::string message;
        iss >> n >> message;
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            settings.SendMessage(n, player, message);
        }
    } else if (command == "pic") {
        int x, y, l;
        iss >> x >> y >> l;
        int playerNumber;
        // Handle start of an incantation
        while (iss >> playerNumber) {
            auto currentPlayer = gameMap.GetPlayerByNumber(playerNumber);
            if (currentPlayer) {
                currentPlayer->SetAnimation(Player::Animation::Dance);
            }
        }
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
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetAnimation(Player::Animation::ThumbsUp);
            player->WaitForAnimationEnd(Player::Animation::Idle);
        }
    } else if (command == "pgt") {
        int n, i;
        iss >> n >> i;
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetAnimation(Player::Animation::Sit);
            player->WaitForAnimationEnd(Player::Animation::Idle);
        }
    } else if (command == "pdi") {
        int n;
        iss >> n;
        // Handle player death
        auto player = gameMap.GetPlayerByNumber(n);
        if (player) {
            player->SetDead();
        }
    } else if (command == "enw") {
        int e, n, x, y;
        iss >> e >> n >> x >> y;
        // Handle egg was laid by a player
        auto island = gameMap.GetIslandByXY(x, y);
        if (island) {
            auto egg = std::make_shared<Egg>(e, n);
            island->AddEgg(egg);
        }
    } else if (command == "ebo") {
        int e;
        iss >> e;
        // Handle player connection for an egg
        gameMap.RemoveEgg(e);
    } else if (command == "edi") {
        int e;
        iss >> e;
        gameMap.RemoveEgg(e);
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
    } else if (command == "suc") {
    } else if (command == "sbp") {
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