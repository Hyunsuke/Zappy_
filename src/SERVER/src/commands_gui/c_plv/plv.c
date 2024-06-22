/*
** EPITECH PROJECT, 2024
** plv.c
** File description:
** Function plv
*/

#include "all.h"

static void parse_plv(const char *input, int *n)
{
    int result;

    *n = 0;
    result = sscanf(input, "plv %d", n);
    if (result < 1)
        *n = 0;
}

int c_plv(struct_t *s, char *buffer)
{
    int nb_player = 0;
    player_t *player;

    if (s->fd_gui == -1)
        return -1;
    parse_plv(buffer, &nb_player);
    player = get_player_by_id(s, nb_player);
    dprintf(s->fd_gui, "plv %d %d\n", nb_player, player->level_player);
    return 0;
}
