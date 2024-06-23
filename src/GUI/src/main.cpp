/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main.cpp
*/

#include "gui.hpp"
#include <future>
#include <chrono>

void init_Window(int screenWidth, int screenHeight, const char* title, RLWindow& window) {
    window.InitWindow(screenWidth, screenHeight, title);
    window.SetTargetFPS(60);
}

bool runMenu(int& screenWidth, int& screenHeight, std::string& host, int& port) {
    Menu menu(screenWidth, screenHeight, host, port);
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

    auto connectFuture = std::async(std::launch::async, [&socketManager]() {
        socketManager->Connect();
        return socketManager->IsRunning();
    });

    if (connectFuture.wait_for(std::chrono::seconds(2)) == std::future_status::timeout) {
        std::cerr << "Failed to connect to the server: timeout" << std::endl;
        socketManager->Disconnect();
        std::exit(84);
    }

    if (!connectFuture.get()) {
        std::cerr << "Failed to connect to the server" << std::endl;
        return false;
    }

    return true;
}

bool processInitialServerMessages(std::unique_ptr<SocketManager>& socketManager, std::string& mapSize, int& timeUnit, std::vector<std::string>& teamNames, std::vector<std::string>& mapContent, std::vector<std::string>& eggs, LoadingScreen& loadingScreen, int timeoutSeconds = 15) {
    auto start = std::chrono::steady_clock::now();

    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

        float progress = std::min(1.0f, static_cast<float>(elapsed) / 1500.0f);
        loadingScreen.Draw("Loading...", progress);

        if (elapsed > timeoutSeconds * 1000) {
            std::exit(84);
            throw GameException("Timeout waiting for initial server messages");
        }

        std::string message;
        if (!socketManager->TryReceiveMessage(message)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
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

        if (!mapSize.empty() && timeUnit > 0 && !teamNames.empty() && !mapContent.empty() && elapsed > 1000) {
            Utils::removeDuplicates(mapContent);
            Utils::removeDuplicates(eggs);
            Utils::removeDuplicates(teamNames);
            break;
        }
    }
    return true;
}

void runGame(int screenWidth, int screenHeight, const std::string& mapSize, int timeUnit, const std::vector<std::string>& teamNames, const std::vector<std::string>& mapContent, const std::vector<std::string>& eggs, std::unique_ptr<SocketManager>& socketManager) {
    auto settings = std::make_shared<Settings>(screenWidth, screenHeight, "game");
    auto game = std::make_shared<Game>(screenWidth, screenHeight, mapSize, timeUnit, teamNames, mapContent, eggs, settings);
    settings->SetGameInstance(game);
    game->SetSocketManager(std::move(socketManager));
    game->Run();
}

void printUsage() {
    std::cerr << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cerr << "option description" << std::endl;
    std::cerr << "-p port       port number" << std::endl;
    std::cerr << "-h machine    hostname of the server" << std::endl;
}

void parseArguments(int ac, char** av, std::string& host, int& port) {
    for (int i = 1; i < ac; ++i) {
        if (std::strcmp(av[i], "-p") == 0) {
            if (i + 1 < ac) {
                port = std::stoi(av[++i]);
            } else {
                throw ArgumentException("Missing port number");
            }
        } else if (std::strcmp(av[i], "-h") == 0) {
            if (i + 1 < ac) {
                host = av[++i];
            } else {
                throw ArgumentException("Missing hostname");
            }
        } else {
            throw ArgumentException("Invalid argument");
        }
    }

    if (host.empty() || port == 0) {
        throw ArgumentException("Host and port must be specified");
    }
}

int main(int ac, char** av) {
    RLWindow window;
    try {
        std::string host;
        int port;

        parseArguments(ac, av, host, port);

        int screenWidth = 1920;
        int screenHeight = 1080;
        init_Window(screenWidth, screenHeight, "Zappy GUI", window);

        LoadingMenu loadingMenu(screenWidth, screenHeight);
        const float minimumDisplayTime = 1.0f;
        float elapsedTime = 0.0f;

        while (!window.WindowShouldClose() && elapsedTime < minimumDisplayTime) {
            window.BeginDrawing();
            window.ClearBackground(RAYWHITE);
            loadingMenu.Draw();
            window.EndDrawing();
            elapsedTime += window.GetFrameTime();
        }

        if (runMenu(screenWidth, screenHeight, host, port)) {
            std::unique_ptr<SocketManager> socketManager;

            if (connectToServer(host, port, socketManager)) {
                LoadingScreen loadingScreen(screenWidth, screenHeight);

                std::string mapSize;
                int timeUnit = 0;
                std::vector<std::string> teamNames;
                std::vector<std::string> mapContent;
                std::vector<std::string> eggs;

                if (processInitialServerMessages(socketManager, mapSize, timeUnit, teamNames, mapContent, eggs, loadingScreen)) {
                    runGame(screenWidth, screenHeight, mapSize, timeUnit, teamNames, mapContent, eggs, socketManager);
                } else {
                    std::cout << "Failed to process initial server messages" << std::endl;
                }
            }
        }
    } catch (const ArgumentException& e) {
        std::cerr << "Argument error: " << e.what() << std::endl;
        printUsage();
        return 84;
    } catch (const GameException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        window.CloseWindow();
        return 84;
    }
    window.CloseWindow();
    return 0;
}
