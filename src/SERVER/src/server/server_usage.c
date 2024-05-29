/*
** EPITECH PROJECT, 2024
** server_usage.c
** File description:
** server usage
*/

#include "all.h"

void server_usage(server_t *server)
{
    server->addrlen = sizeof(server->serv_adr);
    while (1) {
        server->tmp_fdtab = server->fd_tab;
        handle_activity(server);
        handle_new_client(server);
        handling_cmd(server);
    }
}
