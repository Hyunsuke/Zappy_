/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ChatManager
*/

#include "gui.hpp"

ChatManager::ChatManager(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {
    UpdateChatBoxAndTextSize();
}

void ChatManager::AddMessage(int playerNumber, const std::string& teamName, const std::string& message) {
    if (messages.size() >= static_cast<std::vector<ChatMessage>::size_type>(maxMessages)) {
        messages.erase(messages.begin());
    }
    ChatMessage newMessage = { playerNumber, teamName, message, std::time(nullptr) };
    messages.push_back(newMessage);
}

void ChatManager::Draw() {
    rlText.DrawRectangleRec(chatBox, rlText.Fade(DARKGRAY, 0.5f));
    int yOffset = chatBox.y + chatBox.height - textSize - 10;

    if (!messages.empty()) {
        for (auto it = messages.rbegin(); it != messages.rend(); ++it) {
            char timeBuffer[9];
            std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", std::localtime(&it->timestamp));
            std::string fullMessage = std::string(timeBuffer) + " [" + it->teamName + "] Player " + std::to_string(it->playerNumber) + ": " + it->message;

            if (rlText.MeasureText(fullMessage.c_str(), textSize) > chatBox.width - 20)
                fullMessage = fullMessage.substr(0, fullMessage.size() - 3) + "...";

            rlText.DrawText(fullMessage.c_str(), chatBox.x + 10, yOffset, textSize, RAYWHITE);
            yOffset -= textSize + 5;
        }
    }
}

void ChatManager::OnWindowResized(int newWidth, int newHeight) {
    screenWidth = newWidth;
    screenHeight = newHeight;
    UpdateChatBoxAndTextSize();
}

void ChatManager::UpdateChatBoxAndTextSize() {
    float widthRatio = screenWidth / 1920.0f;
    float heightRatio = screenHeight / 1080.0f;

    textSize = static_cast<int>(20 * std::min(widthRatio, heightRatio));

    chatBox.x = 10.0f;
    chatBox.y = static_cast<float>(screenHeight - 210 * heightRatio);
    chatBox.width = 500.0f * widthRatio;
    chatBox.height = 200.0f * heightRatio;
}
