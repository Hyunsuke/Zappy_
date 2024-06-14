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
    int id_player = 0;
    player_t *player;

    parse_ppo(buffer, &id_player);
    player = get_player_by_id(s, id_player);
    if (player == NULL) {
        dprintf(s->fd_gui, "KO\n");
        return -1;
    }
    dprintf(s->fd_gui, "ppo #%d %d %d %d\n", id_player, player->x, player->y,
        player->view_direction);
    return 0;
}
