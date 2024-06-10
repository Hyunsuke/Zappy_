/*
** EPITECH PROJECT, 2024
** server_usage.c
** File description:
** server usage
*/

#include "all.h"

void server_usage(server_t *server, struct_t *s)
{
    double tick_interval = CLOCKS_PER_SEC / s->time;
    clock_t start_time = s->clock;
    double elapsed_time;

    s->clock = clock();
    server->addrlen = sizeof(server->serv_adr);
    while (1) {
        s->clock = clock();
        elapsed_time = (double)(s->clock - start_time) / CLOCKS_PER_SEC;
        server->tmp_fdtab = server->fd_tab;
        handle_activity(server);
        handle_new_client(server);
        handling_cmd(server, s);
        if (elapsed_time >= tick_interval) {
            new_tick(s);
            start_time = s->clock;
        }
    }
}
