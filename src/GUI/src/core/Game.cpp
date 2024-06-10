/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Game.cpp
*/

#include "gui.hpp"

Game::Game(int screenWidth, int screenHeight, const std::string& mapSize, int timeUnit, const std::vector<std::string>& teamNames, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs)
    : screenWidth(screenWidth),
      screenHeight(screenHeight),
      timeUnit(timeUnit),
      teamNames(teamNames),
      sky(screenWidth, screenHeight),
      uiManager(screenWidth, screenHeight),
      settings(screenWidth, screenHeight) {

    shaderManager = std::make_unique<ShaderManager>("src/GUI/assets/shaders/lighting.vs", "src/GUI/assets/shaders/lighting.fs");
    Vector3 lightPosition = { 10.0f, 10.0f, 10.0f };
    Vector3 viewPosition = { 0.0f, 10.0f, 10.0f };
    Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    Vector3 ambientColor = { 0.2f, 0.2f, 0.2f };
    shaderManager->SetShaderValue("lightPosition", &lightPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("viewPosition", &viewPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("lightColor", &lightColor, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("ambientColor", &ambientColor, SHADER_UNIFORM_VEC3);

    InitializeMap(mapSize, mapContent, eggs);
}

Game::~Game() {
    if (socketManager) {
        socketManager->Disconnect();
    }
}

void Game::InitializeMap(const std::string& mapSize, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs) {
    int width, height;
    sscanf(mapSize.c_str(), "msz %d %d", &width, &height);
    gameMap = Map(width, height);

    for (const auto& content : mapContent) {
        int x, y, q0, q1, q2, q3, q4, q5, q6;
        sscanf(content.c_str(), "bct %d %d %d %d %d %d %d %d %d", &x, &y, &q0, &q1, &q2, &q3, &q4, &q5, &q6);
        auto island = std::make_shared<Island>(x, y, Vector3{(float)x * 15.0f, 0.0f, (float)y * 15.0f}, "src/GUI/assets/Island/Island01.obj", "src/GUI/assets/Island/TextIsland.png", 0.7f, Vector3{0.0f, 1.0f, 0.0f}, 0.0f);
        island->SetShader(shaderManager->GetShader());
        island->food->SetQuantity(q0);
        island->linemate->SetQuantity(q1);
        island->deraumere->SetQuantity(q2);
        island->sibur->SetQuantity(q3);
        island->mendiane->SetQuantity(q4);
        island->phiras->SetQuantity(q5);
        island->thystame->SetQuantity(q6);
        gameMap.AddIsland(island);
    }

    for (const auto& egg : eggs) {
        int e, n, x, y;
        sscanf(egg.c_str(), "enw %d %d %d %d", &e, &n, &x, &y);
        auto island = gameMap.GetIslandByXY(x, y);
        if (island) {
            // Add egg to the island
        }
    }
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void Game::Update() {
    cameraController.Update();
    gameMap.Update();

    sky.Update();

    Vector3 lightPos = sky.GetLightPosition();
    Vector3 lightCol = sky.GetLightColor();
    shaderManager->SetShaderValue("lightPosition", &lightPos, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("lightColor", &lightCol, SHADER_UNIFORM_VEC3);

    rayManager.UpdateRay(cameraController.GetCamera());
    selectedIsland = rayManager.GetIslandUnderMouse(gameMap.GetIslands());
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    sky.DrawBackground();

    BeginMode3D(cameraController.GetCamera());

    sky.DrawSunAndMoon();
    gameMap.Draw();
    gameMap.DrawIslandWires(selectedIsland);

    EndMode3D();
    uiManager.DrawUI(selectedIsland, GetFPS());
    EndDrawing();
}

void Game::ToggleObjectActive(int x, int y, const std::string& objectType, int value) {
    auto island = gameMap.GetIslandByXY(x, y);
    if (island) {
        if (objectType == "food") {
            island->food->SetQuantity(island->food->GetQuantity() + value);
        } else if (objectType == "linemate") {
            island->linemate->SetQuantity(island->linemate->GetQuantity() + value);
        } else if (objectType == "deraumere") {
            island->deraumere->SetQuantity(island->deraumere->GetQuantity() + value);
        } else if (objectType == "sibur") {
            island->sibur->SetQuantity(island->sibur->GetQuantity() + value);
        } else if (objectType == "mendiane") {
            island->mendiane->SetQuantity(island->mendiane->GetQuantity() + value);
        } else if (objectType == "phiras") {
            island->phiras->SetQuantity(island->phiras->GetQuantity() + value);
        } else if (objectType == "thystame") {
            island->thystame->SetQuantity(island->thystame->GetQuantity() + value);
        }
    }
}

void Game::HandleServerMessage(const std::string& message) {
    // std::cout << "Received message: " << message << std::endl;
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    if (command == "msz") {
        int x, y;
        iss >> x >> y;
        // Handle map size
    } else if (command == "bct") {
        int x, y, q0, q1, q2, q3, q4, q5, q6;
        iss >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
        // Handle content of a tile
    } else if (command == "tna") {
        std::string teamName;
        iss >> teamName;
        // Handle team name
    } else if (command == "pnw") {
        int n, x, y, o, l;
        std::string teamName;
        iss >> n >> x >> y >> o >> l >> teamName;
        // Handle new player connection
    } else if (command == "ppo") {
        int n, x, y, o;
        iss >> n >> x >> y >> o;
        // Handle player position
    } else if (command == "plv") {
        int n, l;
        iss >> n >> l;
        // Handle player level
    } else if (command == "pin") {
        int n, x, y, q0, q1, q2, q3, q4, q5, q6;
        iss >> n >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
        // Handle player inventory
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
        // Handle resource collecting
    } else if (command == "pdi") {
        int n;
        iss >> n;
        // Handle player death
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
        // Handle time unit request
    } else if (command == "sst") {
        int t;
        iss >> t;
        // Handle time unit modification
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

// Implement command methods to send specific requests to the server

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