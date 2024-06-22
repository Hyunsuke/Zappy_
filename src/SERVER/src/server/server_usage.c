/*
** EPITECH PROJECT, 2024
** server_usage.c
** File description:
** server usage
*/

#include "all.h"

static bool start_game(struct_t *s)
{
    team_t *current_team = s->head_team;

    if (s->fd_gui == -1)
        return false;
    printf("FD CONNECT");
    while (current_team != NULL) {
        if (current_team->players_id == NULL) {
            printf("No players for this team %s\n", current_team->name);
            return false;
        }
        current_team = current_team->next;
    }
    s->start_game = true;
    return true;
}

static void check_remove(struct_t *s, server_t *server, int fd)
{
    if (FD_ISSET(fd, &server->fd_tab)) {
        if (fd != s->fd_gui && fd != server->server_fd) {
            close(fd);
            FD_CLR(fd, &server->fd_tab);
        }
    }
}

static void close_all_fd(struct_t *s, server_t *server)
{
    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        check_remove(s, server, fd);
    }
}

static bool end_game(struct_t *s, server_t *server)
{
    player_t *current_player = s->head_player;

    while (current_player != NULL) {
        if (current_player->level_player >= 8) {
            c_seg(s, get_team_by_id(s, current_player->id_team)->name);
            s->stop_server = true;
            close_all_fd(s, server);
            return true;
        }
        current_player = current_player->next;
    }
    return false;
}

static void update_ticks_and_check_tiredness(struct_t *s, server_t *server,
    double **ticks, double tick_interval)
{
    double *start_time = ticks[0];
    int *nb_tick_tiredness = (int *)ticks[1];
    double current_time = (double)clock() / CLOCKS_PER_SEC;
    double elapsed_time = current_time - *start_time;

    if (elapsed_time >= tick_interval) {
        new_tick(s);
        c_mct(s, "");
        *start_time = current_time;
        (*nb_tick_tiredness)++;
        s->nb_tick_refill++;
        if (end_game(s, server))
            return;
    }
    if (s->nb_tick_refill >= 20)
        refill_map(s);
    if (*nb_tick_tiredness >= 126) {
        *nb_tick_tiredness = 0;
        tiredness(s, server);
    }
}

void server_usage(server_t *server, struct_t *s)
{
    double tick_interval = 1.0 / s->time;
    double start_time = (double)clock() / CLOCKS_PER_SEC;
    int nb_tick_tiredness = 0;
    double **ticks = my_malloc(sizeof(double *) * 2);

    server->addrlen = sizeof(server->serv_adr);
    while (s->stop_server == false) {
        server->tmp_fdtab = server->fd_tab;
        tick_interval = 1.0 / s->time;
        handle_activity(server);
        handle_new_client(server);
        handling_cmd(server, s);
        if (s->start_game == false)
            start_game(s);
        ticks[0] = &start_time;
        ticks[1] = (double *)&nb_tick_tiredness;
        update_ticks_and_check_tiredness(s, server, ticks, tick_interval);
        send_info_web_debug(s);
    }
}
