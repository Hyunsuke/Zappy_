/*
** EPITECH PROJECT, 2024
** pdr.c
** File description:
** Function pdr
*/

#include "all.h"

int c_pdr(struct_t *s, int id_player, int id_rsc)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pdr %d %d\n", id_player, id_rsc);
    return 0;
}
