/*
** EPITECH PROJECT, 2024
** pgt.c
** File description:
** Function pgt
*/

#include "all.h"

int c_pgt(struct_t *s, int id_player, int id_rsc)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pgt %d %d\n", id_player, id_rsc);
    return 0;
}
