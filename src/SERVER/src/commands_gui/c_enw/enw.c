/*
** EPITECH PROJECT, 2024
** enw.c
** File description:
** Function enw
*/

#include "all.h"

// Pos -> x; y
int c_enw(struct_t *s, int nb_egg, int nb_player, int *pos)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "enw %d %d %d %d\n",
        nb_egg, nb_player, pos[0], pos[1]);
    return 0;
}
