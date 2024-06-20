/*
** EPITECH PROJECT, 2024
** pfk.c
** File description:
** Function pfk
*/

#include "all.h"

int c_pfk(struct_t *s, int id_player)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pfk %d\n", id_player);
    return 0;
}
