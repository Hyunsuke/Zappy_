/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** SocketManager
*/

#include "gui.hpp"

SocketManager::SocketManager()
    : port(0), sockfd(-1), running(false), waitingForResponse(false), iswin(false) {}

SocketManager::SocketManager(const std::string& host, int port)
    : host(host), port(port), sockfd(-1), running(false), waitingForResponse(false) {
        if (host == "localhost")
            this->host = "127.0.0.1";
    }

SocketManager::~SocketManager() {
    Disconnect();
}

void SocketManager::Connect() {
    struct sockaddr_in serv_addr;
    sockfd = socketWrapper.Socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw GameException("Error creating socket");
        return;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = socketWrapper.Htons(port);
    if (socketWrapper.InetPton(AF_INET, host.c_str(), &serv_addr.sin_addr) <= 0) {
        throw GameException("Invalid address/ Address not supported");
        return;
    }

    if (socketWrapper.Connect(sockfd, serv_addr, sizeof(serv_addr)) < 0) {
        throw GameException("Connection Failed");
        return;
    }

    running = true;
    receiveThread = std::thread(&SocketManager::ReceiveMessages, this);
    SendMessage("GRAPHIC\n");
}

bool SocketManager::IsRunning() const {
    return running;
}

void SocketManager::Disconnect() {
    running = false;
    socketWrapper.Close(sockfd);
    if (receiveThread.joinable()) {
        receiveThread.join();
    }
}

void SocketManager::SendMessage(const std::string& message) {
    send(sockfd, message.c_str(), message.size(), 0);
}

std::string SocketManager::SendCommand(const std::string& command) {
    std::unique_lock<std::mutex> lock(messageMutex);
    waitingForResponse = true;
    SendMessage(command);
    messageCondition.wait(lock, [this] { return !waitingForResponse; });
    return response;
}

std::string SocketManager::ReceiveMessage() {
    std::unique_lock<std::mutex> lock(messageMutex);
    while (messageQueue.empty()) {
        messageCondition.wait(lock);
    }
    std::string message = messageQueue.front();
    messageQueue.pop();
    return message;
}

bool SocketManager::TryReceiveMessage(std::string& message) {
    std::unique_lock<std::mutex> lock(messageMutex);
    if (messageQueue.empty()) {
        return false;
    }
    message = messageQueue.front();
    messageQueue.pop();
    return true;
}


void SocketManager::SetMessageHandler(MessageHandler handler) {
    messageHandler = handler;
}

void SocketManager::ReceiveMessages() {
    char buffer[1024] = {0};
    std::string partialMessage;
    while (running) {
        int bytesReceived = recv(sockfd, buffer, 1024, 0);
        if (bytesReceived > 0) {
            std::string data(buffer, bytesReceived);
            partialMessage += data;
            std::size_t pos;
            while ((pos = partialMessage.find('\n')) != std::string::npos) {
                std::string message = partialMessage.substr(0, pos);
                partialMessage.erase(0, pos + 1);
                std::lock_guard<std::mutex> lock(messageMutex);
                messageQueue.push(message);
                messageCondition.notify_all();
                if (waitingForResponse) {
                    response = message;
                    waitingForResponse = false;
                    messageCondition.notify_all();
                } else if (messageHandler) {
                    messageHandler(message);
                }
            }
        } else if (bytesReceived == 0 && !iswin) {
            running = false;
            std::cerr << "Disconnected from server" << std::endl;
        }
    }
}

void SocketManager::Setwin()
{
    iswin = true;
}
