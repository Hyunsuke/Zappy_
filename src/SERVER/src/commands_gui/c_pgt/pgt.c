/*
** EPITECH PROJECT, 2024
** pgt.c
** File description:
** Function pgt
*/

#include "all.h"

int c_pgt(struct_t *s, int id_player, int id_rsc)
{
    dprintf(s->fd_gui, "pgt %d %d\n", id_player, id_rsc);
    return 0;
}
