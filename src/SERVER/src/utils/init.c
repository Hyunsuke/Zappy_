/*
** EPITECH PROJECT, 2024
** init.c
** File description:
** Function
*/

#include "all.h"

void init_struct(struct_t *s)
{
    srand(time(0));
    s->nb_tick_refill = 0;
    s->head_player = NULL;
    s->next_id_player = 0;
    s->fd_gui = -1;
    s->stop_server = false;
    s->start_game = true;
    s->head_elevation = init_elevation();
    s->command_ticks = initialize_command_ticks();
    s->fd_web_debug = -1;
    s->head_progress_incantation = NULL;
}
