/*
** EPITECH PROJECT, 2024
** ebo.c
** File description:
** Function ebo
*/

#include "all.h"

int c_ebo(struct_t *s, int nb_egg)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "ebo %d\n", nb_egg);
    return 0;
}
