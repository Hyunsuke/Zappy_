/*
** EPITECH PROJECT, 2024
** server_usage.c
** File description:
** server usage
*/

#include "all.h"

static void update_ticks_and_check_tiredness(struct_t *s, double *start_time,
    int *nb_tick, double tick_interval)
{
    double current_time = (double)clock() / CLOCKS_PER_SEC;
    double elapsed_time = current_time - *start_time;

    if (elapsed_time >= tick_interval) {
        new_tick(s);
        *start_time = current_time;
        (*nb_tick)++;
    }
    if (*nb_tick >= 126) {
        *nb_tick = 0;
        tiredness(s);
    }
}

void server_usage(server_t *server, struct_t *s)
{
    double tick_interval = 1.0 / s->time;
    double start_time = (double)clock() / CLOCKS_PER_SEC;
    int nb_tick = 0;

    server->addrlen = sizeof(server->serv_adr);
    while (s->stop_server == false) {
        server->tmp_fdtab = server->fd_tab;
        handle_activity(server);
        handle_new_client(server);
        handling_cmd(server, s);
        update_ticks_and_check_tiredness(s, &start_time, &nb_tick,
            tick_interval);
    }
}
