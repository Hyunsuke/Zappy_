/*
** EPITECH PROJECT, 2024
** ppo.c
** File description:
** Function ppo
*/

#include "all.h"

static void parse_ppo(const char *input, int *n)
{
    int result;

    *n = 0;
    result = sscanf(input, "ppo #%d", n);
    if (result < 1)
        *n = 0;
}

int c_ppo(struct_t *s, char *buffer)
{
    int nb_player = 0;
    player_t *player;

    parse_ppo(buffer, &nb_player);
    player = get_player_by_id(s, nb_player);
    dprintf(s->fd_gui, "ppo #%d %d %d %d\n", nb_player, player->x, player->y,
        player->view_direction);
    return 0;
}
