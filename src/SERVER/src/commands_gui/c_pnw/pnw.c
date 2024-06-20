/*
** EPITECH PROJECT, 2024
** pnw.c
** File description:
** Function pnw
*/

#include "all.h"

// Position x;y;
int c_pnw(struct_t *s, int id_player, int incantation_level)
{
    player_t *player = get_player_by_id(s, id_player);

    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pnw %d %d %d %d %d %s\n",
        id_player,
        player->x, player->y,
        player->view_direction,
        incantation_level,
        get_team_by_id(s, player->id_team)->name);
    return 0;
}
