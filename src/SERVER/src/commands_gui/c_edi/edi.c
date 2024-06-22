/*
** EPITECH PROJECT, 2024
** edi.c
** File description:
** Function edi
*/

#include "all.h"

int c_edi(struct_t *s, int nb_egg)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "edi %d\n", nb_egg);
    return 0;
}
