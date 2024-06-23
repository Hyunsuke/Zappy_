/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** SocketWrapper
*/

#ifndef SOCKETWRAPPER_HPP_
#define SOCKETWRAPPER_HPP_

#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

class SocketWrapper {
public:
    static int Socket(int domain, int type, int protocol);
    static uint16_t Htons(uint16_t hostshort);
    static int InetPton(int af, const char* src, void* dst);
    static int Connect(int sockfd, sockaddr_in addr, socklen_t addrlen);
    static int Close(int fd);
    static ssize_t Recv(int sockfd, void* buf, std::size_t len, int flags);
};

#endif // SOCKETWRAPPER_HPP_
