/*
** EPITECH PROJECT, 2024
** server_usage.c
** File description:
** server usage
*/

#include "all.h"

void server_usage(server_t *server, struct_t *s)
{
    double tick_interval = 1.0 / s->time;
    clock_t start_time = clock();
    clock_t current_time;
    double elapsed_time;
    int nb_tick = 0;

    server->addrlen = sizeof(server->serv_adr);
    while (s->stop_server == false) {
        current_time = clock();
        elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
        server->tmp_fdtab = server->fd_tab;
        handle_activity(server);
        handle_new_client(server);
        handling_cmd(server, s);
        if (elapsed_time >= tick_interval) {
            new_tick(s);
            start_time = current_time;
        }
    }
}
