/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ReactionFunc
*/

#include "gui.hpp"

void Game::UpdateIslandResources(int x, int y, int q0, int q1, int q2, int q3, int q4, int q5, int q6) {
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        island->food->SetQuantity(q0);
        island->linemate->SetQuantity(q1);
        island->deraumere->SetQuantity(q2);
        island->sibur->SetQuantity(q3);
        island->mendiane->SetQuantity(q4);
        island->phiras->SetQuantity(q5);
        island->thystame->SetQuantity(q6);
    }
}

void Game::HandleMapSize(std::istringstream& iss) {
    int x, y;
    iss >> x >> y;
}

void Game::HandleTileContent(std::istringstream& iss) {
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    UpdateIslandResources(x, y, q0, q1, q2, q3, q4, q5, q6);
}

void Game::HandleTeamName(std::istringstream& iss) {
    std::string teamName;
    iss >> teamName;
    this->teamNames.push_back(teamName);
    Utils::removeDuplicates(teamNames);
}

void Game::HandlePlayerNew(std::istringstream& iss) {
    int n, x, y, o, l;
    std::string teamName;
    iss >> n >> x >> y >> o >> l >> teamName;
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        auto player = std::make_shared<Player>(n, teamName, x, y, o, l, "src/GUI/assets/Player/robot.glb", island);
        gameMap.AddPlayer(player);
        island->AddPlayer(player);
    }
}

void Game::HandlePlayerPosition(std::istringstream& iss) {
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
                player->JumpTo(newIsland, 7.0f / timeUnit);
                newIsland->AddPlayer(player);
            }
        }
    }
}

void Game::HandlePlayerLevel(std::istringstream& iss) {
    int n, l;
    iss >> n >> l;
    auto player = gameMap.GetPlayerByNumber(n);
    if (player) {
        player->SetLevel(l);
    }
}

void Game::HandlePlayerInventory(std::istringstream& iss) {
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
}


void Game::HandlePlayerExpulsion(std::istringstream& iss) {
    int n;
    iss >> n;
    auto player = gameMap.GetPlayerByNumber(n);
    if (player) {
        player->SetAnimation(Player::Animation::Punch);
        player->WaitForAnimationEnd(Player::Animation::Idle);
    }
}

void Game::HandlePlayerBroadcast(std::istringstream& iss) {
    int n;
    std::string message;
    iss >> n >> message;
    auto player = gameMap.GetPlayerByNumber(n);
    if (player) {
        settings->SendMessage(n, player, message);
    }
}

void Game::HandleStartIncantation(std::istringstream& iss) {
    int x, y, l;
    iss >> x >> y >> l;
    int playerNumber;
    while (iss >> playerNumber) {
        auto currentPlayer = gameMap.GetPlayerByNumber(playerNumber);
        if (currentPlayer) {
            currentPlayer->SetAnimation(Player::Animation::Dance);
        }
    }
}

void Game::HandleEndIncantation(std::istringstream& iss) {
    int x, y;
    char r;
    iss >> x >> y >> r;
}

void Game::HandleEggLaying(std::istringstream& iss) {
    int n;
    iss >> n;
}

void Game::HandlePlayerDrop(std::istringstream& iss) {
    int n, i;
    iss >> n >> i;
    auto player = gameMap.GetPlayerByNumber(n);
    if (player) {
        player->SetAnimation(Player::Animation::ThumbsUp);
        player->WaitForAnimationEnd(Player::Animation::Idle);
    }
}

void Game::HandlePlayerTake(std::istringstream& iss) {
    int n, i;
    iss >> n >> i;
    auto player = gameMap.GetPlayerByNumber(n);
    if (player) {
        player->SetAnimation(Player::Animation::Sit);
        player->WaitForAnimationEnd(Player::Animation::Idle);
    }
}

void Game::HandlePlayerDeath(std::istringstream& iss) {
    int n;
    iss >> n;
    auto player = gameMap.GetPlayerByNumber(n);
    if (player) {
        player->SetDead();
        player->WaitForAnimationEnd(Player::Animation::Idle);
    }
}

void Game::HandleEggLayingPlayer(std::istringstream& iss) {
    int e, n, x, y;
    iss >> e >> n >> x >> y;
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        auto egg = std::make_shared<Egg>(e, n);
        island->AddEgg(egg);
    }
}

void Game::HandleEggConnection(std::istringstream& iss) {
    int e;
    iss >> e;
    gameMap.RemoveEgg(e);
}

void Game::HandleEggDeath(std::istringstream& iss) {
    int e;
    iss >> e;
    gameMap.RemoveEgg(e);
}

void Game::HandleTimeUnitChange(std::istringstream& iss) {
    int t;
    iss >> t;
    this->timeUnit = t;
}

void Game::HandleGameOver(std::istringstream& iss) {
    socketManager->Setwin();
    std::string teamName;
    iss >> teamName;
    gameOver = true;
    winningTeam = teamName;
}

void Game::HandleServerMessage(std::istringstream& iss) {
    std::string message;
    iss >> message;
}

void Game::HandleUnknownCommand() {}

void Game::HandleBadParameter() {}
