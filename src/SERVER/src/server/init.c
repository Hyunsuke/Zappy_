/*
** EPITECH PROJECT, 2024
** init.c
** File description:
** init fd table
*/

#include "all.h"

static void def_data_tab(server_t *server)
{
    server->round = my_malloc(sizeof(int) * FD_SETSIZE);
    if (server->round == NULL) {
        full_free();
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < FD_SETSIZE; i++)
        server->round[i] = 0;
}

void init_fd_table(server_t *server)
{
    FD_ZERO(&server->fd_tab);
    FD_SET(server->server_fd, &server->fd_tab);
    server->last_cli = server->server_fd;
    def_data_tab(server);
}
