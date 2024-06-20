/*
** EPITECH PROJECT, 2024
** pin.c
** File description:
** Function pin
*/

#include "all.h"

static void parse_pin(const char *input, int *n)
{
    int result;

    *n = 0;
    result = sscanf(input, "pin %d", n);
    if (result < 1)
        *n = 0;
}

int c_pin(struct_t *s, char *buffer)
{
    int nb_player;
    player_t *player;

    if (s->fd_gui == -1)
        return -1;
    parse_pin(buffer, &nb_player);
    player = get_player_by_id(s, nb_player);
    dprintf(s->fd_gui, "pin %d %d %d %d %d %d %d %d %d %d\n",
        nb_player,
        player->x,
        player->y,
        player->food,
        player->linemate,
        player->deraumere,
        player->sibur,
        player->mendiane,
        player->phiras,
        player->thystame);
    return 0;
}

int c_pin_send(struct_t *s, player_t *player)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pin %d %d %d %d %d %d %d %d %d %d\n",
        player->id_player,
        player->x,
        player->y,
        player->food,
        player->linemate,
        player->deraumere,
        player->sibur,
        player->mendiane,
        player->phiras,
        player->thystame);
    return 0;
}
