/*
** EPITECH PROJECT, 2024
** init_server.c
** File description:
** init server values
*/

#include "all.h"

void server_gestion(server_t *server, struct_t *s)
{
    create_and_config_serv(server, s);
    init_fd_table(server);
    server_usage(server, s);
    close(server->server_fd);
}
