/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ChatManager
*/

#ifndef CHATMANAGER_HPP
#define CHATMANAGER_HPP

#include "raylib.h"
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "../Wrapper/Raylib/RLText.hpp"

class ChatManager {
public:
    ChatManager(int screenWidth, int screenHeight);

    void AddMessage(int playerNumber, const std::string& teamName, const std::string& message);
    void Draw();
    void OnWindowResized(int newWidth, int newHeight);

private:
    struct ChatMessage {
        int playerNumber;
        std::string teamName;
        std::string message;
        std::time_t timestamp;
    };

    Rectangle chatBox;
    int screenWidth;
    int screenHeight;
    int textSize = 20;
    int maxMessages = 7;
    std::vector<ChatMessage> messages;

    void UpdateChatBoxAndTextSize();
    RLText rlText;
};

#endif // CHATMANAGER_HPP