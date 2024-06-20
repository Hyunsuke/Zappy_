/*
** EPITECH PROJECT, 2024
** config.c
** File description:
** config
*/

#include "all.h"

void config_socket(server_t *server, struct_t *s)
{
    int opt = 1;

    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd < 0) {
        perror("socket failed");
        full_free();
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,
        sizeof(opt))) {
        perror("setsockopt");
        full_free();
        exit(EXIT_FAILURE);
    }
    server->serv_adr.sin_family = AF_INET;
    server->serv_adr.sin_addr.s_addr = INADDR_ANY;
    server->serv_adr.sin_port = htons(s->port);
}

void create_and_config_serv(server_t *server, struct_t *s)
{
    config_socket(server, s);
    if (bind(server->server_fd, (struct sockaddr*)&server->serv_adr,
        sizeof(server->serv_adr)) < 0) {
        perror("bind failed");
        full_free();
        exit(EXIT_FAILURE);
    }
    if (listen(server->server_fd, 3) < 0) {
        perror("listen");
        full_free();
        exit(EXIT_FAILURE);
    }
}
