/*
** EPITECH PROJECT, 2024
** init.c
** File description:
** init fd table
*/

#include "all.h"

void init_fd_table(server_t *server)
{
    FD_ZERO(&server->fd_tab);
    FD_SET(server->server_fd, &server->fd_tab);
    server->last_cli = server->server_fd;
}
