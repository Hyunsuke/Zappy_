/*
** EPITECH PROJECT, 2024
** pex.c
** File description:
** Function pex
*/

#include "all.h"

int c_pex(struct_t *s, int id_player)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pex %d\n", id_player);
    return 0;
}
