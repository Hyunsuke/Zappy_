/*
** EPITECH PROJECT, 2024
** pnw.c
** File description:
** Function pnw
*/

#include "all.h"

// Position x;y;
int c_pnw(struct_t *s, int id_player, int *position, int incantation_level)
{
    dprintf(s->fd_gui, "pwn #%d %d %d %d %d %d\n",
        id_player,
        position[0], position[1],
        get_player_by_id(s, id_player)->view_direction,
        incantation_level,
        get_team_by_id(s, get_player_by_id(s, id_player)->id_team));
    return 0;
}
