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
    result = sscanf(input, "ppo %d", n);
    if (result < 1)
        *n = 0;
}

int c_ppo(struct_t *s, char *buffer)
{
    int id_player = 0;
    player_t *player;

    if (s->fd_gui == -1)
        return -1;
    parse_ppo(buffer, &id_player);
    player = get_player_by_id(s, id_player);
    if (player == NULL) {
        dprintf(s->fd_gui, "ko\n");
        return -1;
    }
    dprintf(s->fd_gui, "ppo %d %d %d %d\n", id_player, player->x, player->y,
        player->view_direction);
    return 0;
}

int c_ppo_rotate(struct_t *s, int fd_player)
{
    player_t *player = get_player_by_fd(s, fd_player);

    if (s->fd_gui == -1)
        return -1;
    if (player == NULL) {
        dprintf(s->fd_gui, "ko\n");
        return -1;
    }
    dprintf(s->fd_gui, "ppo %d %d %d %d\n", fd_player, player->x, player->y,
        player->view_direction);
    return 0;
}
