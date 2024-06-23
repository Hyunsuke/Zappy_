/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** SocketManager
*/

#ifndef SOCKET_MANAGER_HPP_
#define SOCKET_MANAGER_HPP_

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <netinet/in.h>
#include <condition_variable>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstddef>
#include "../Wrapper/SocketWrapper.hpp"

class SocketManager {
public:
    using MessageHandler = std::function<void(const std::string&)>;

    SocketManager();
    SocketManager(const std::string& host, int port);
    ~SocketManager();

    void Connect();
    void Disconnect();
    void SendMessage(const std::string& message);
    std::string SendCommand(const std::string& command);
    std::string ReceiveMessage();
    bool TryReceiveMessage(std::string& message);
    void SetMessageHandler(MessageHandler handler);
    bool IsRunning() const;
    void Setwin();

private:
    void ReceiveMessages();

    std::string host;
    int port;
    int sockfd;
    std::thread receiveThread;
    std::mutex messageMutex;
    std::queue<std::string> messageQueue;
    std::condition_variable messageCondition;
    MessageHandler messageHandler;
    bool running;
    bool waitingForResponse;
    std::string response;
    bool iswin = false;
    SocketWrapper socketWrapper;
};

#endif // SOCKET_MANAGER_HPP_

