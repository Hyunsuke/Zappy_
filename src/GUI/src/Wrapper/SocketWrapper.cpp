/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** socket
*/

#include "gui.hpp"

int SocketWrapper::Socket(int domain, int type, int protocol) {
    return socket(domain, type, protocol);
}

uint16_t SocketWrapper::Htons(uint16_t hostshort) {
    return htons(hostshort);
}

int SocketWrapper::InetPton(int af, const char* src, void* dst) {
    return inet_pton(af, src, dst);
}

int SocketWrapper::Connect(int sockfd, sockaddr_in addr, socklen_t addrlen) {
    return connect(sockfd, (struct sockaddr *)&addr, addrlen);
}

int SocketWrapper::Close(int fd) {
    return close(fd);
}

ssize_t SocketWrapper::Recv(int sockfd, void* buf, std::size_t len, int flags) {
    return recv(sockfd, buf, len, flags);
}
