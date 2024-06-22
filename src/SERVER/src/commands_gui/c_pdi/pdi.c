/*
** EPITECH PROJECT, 2024
** pdi.c
** File description:
** Function pdi
*/

#include "all.h"

int c_pdi(struct_t *s, int id_player)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pdi %d\n", id_player);
    return 0;
}
