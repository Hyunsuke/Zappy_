/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Game.cpp
*/

#include "gui.hpp"

Game::Game(int screenWidth, int screenHeight, const std::string& mapSize, int timeUnit, const std::vector<std::string>& teamNames, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs, std::shared_ptr<Settings> settings)
    : screenWidth(screenWidth),
      screenHeight(screenHeight),
      timeUnit(timeUnit),
      teamNames(teamNames),
      sky(screenWidth, screenHeight),
      uiManager(screenWidth, screenHeight),
      settings(settings),
      cameraManager(cameraController, gameMap),
      endMenu(screenWidth, screenHeight) {

    InitializeCommandHandlers();
    shaderManager = std::make_unique<ShaderManager>("src/GUI/assets/shaders/lighting.vs", "src/GUI/assets/shaders/lighting.fs");
    Vector3 lightPosition = { 10.0f, 10.0f, 10.0f };
    Vector3 viewPosition = { 0.0f, 10.0f, 10.0f };
    Vector3 lightColor = { 1.0f, 1.0f, 1.0f };
    Vector3 ambientColor = { 0.2f, 0.2f, 0.2f };
    shaderManager->SetShaderValue("lightPosition", lightPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("viewPosition", viewPosition, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("lightColor", lightColor, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("ambientColor", ambientColor, SHADER_UNIFORM_VEC3);

    ModelCollector::GetInstance().LoadModel("src/GUI/assets/Player/robot.glb");
    ModelCollector::GetInstance().LoadModel("src/GUI/assets/Egg/egg.obj");
    TextureCollector::GetInstance().LoadTexture("src/GUI/assets/Egg/egg.png");


    InitializeMap(mapSize, mapContent, eggs);
}

Game::~Game() {
    if (socketManager) {
        socketManager->Disconnect();
    }
}

void Game::InitializeMap(const std::string& mapSize, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs) {
    int width, height;
    std::sscanf(mapSize.c_str(), "msz %d %d", &width, &height);
    gameMap = Map(width, height);

    for (const auto& content : mapContent) {
        int x, y, q0, q1, q2, q3, q4, q5, q6;
        std::sscanf(content.c_str(), "bct %d %d %d %d %d %d %d %d %d", &x, &y, &q0, &q1, &q2, &q3, &q4, &q5, &q6);
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
        std::sscanf(egg.c_str(), "enw %d %d %d %d", &e, &n, &x, &y);
        auto island = gameMap.GetIslandByXY(x, y);
        if (island) {
            auto egg = std::make_shared<Egg>(e, n);
            island->AddEgg(egg);
        }
    }
}

void Game::Run() {
    while (!window.WindowShouldClose()) {
        if (!socketManager->IsRunning())
            break;
        Update();
        Draw();
    }
}

void Game::Update() {
    cameraManager.Update(selectedPlayer, selectedIsland);
    gameMap.Update();
    sky.Update(timeUnit);

    Vector3 lightPos = sky.GetLightPosition();
    Vector3 lightCol = sky.GetLightColor();
    shaderManager->SetShaderValue("lightPosition", lightPos, SHADER_UNIFORM_VEC3);
    shaderManager->SetShaderValue("lightColor", lightCol, SHADER_UNIFORM_VEC3);

    rayManager.UpdateRay(cameraController.GetCamera());

    if (rlModel.IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        selectedIsland = rayManager.GetIslandUnderMouse(gameMap.GetIslands());
    if (rlModel.IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        selectedPlayer = rayManager.GetPlayerUnderMouse(gameMap.GetPlayers());

    settings->HandleMouseInput(rlModel.GetMousePosition(), uiManager.settingsButton, uiManager.closeButton);

    settings->Update();

    settings->HandleWindowResize(sky, uiManager);
}

void Game::Draw() {
    window.BeginDrawing();
    window.ClearBackground(WHITE);

    if (gameOver) {
        while (!window.WindowShouldClose()) {
            endMenu.HandleMouseInput();
            endMenu.Draw(winningTeam);
        }
    } else {
        sky.DrawBackground();

        window.BeginMode3D(cameraController.GetCamera());

        sky.DrawSunAndMoon();
        gameMap.Draw();
        gameMap.DrawIslandWires(selectedIsland);
        gameMap.DrawPlayerWires(selectedPlayer);

        window.EndMode3D();
        uiManager.DrawUI(selectedIsland, selectedPlayer, teamNames.size(), gameMap.GetPlayerCount() , timeUnit, gameMap.GetMapSize(), GetFPS());
        settings->Draw();
    }

    window.EndDrawing();
}
