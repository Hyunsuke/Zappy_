/*
** EPITECH PROJECT, 2024
** pbc.c
** File description:
** Function pbc
*/

#include "all.h"

int c_pbc(struct_t *s, int id_player, char *name_team)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pbc: %d %s\n", id_player, name_team);
    return 0;
}
