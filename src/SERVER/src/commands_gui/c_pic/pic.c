/*
** EPITECH PROJECT, 2024
** pic.c
** File description:
** Function pic
*/

#include "all.h"

int c_pic(struct_t *s, position_t position, int level, int *player)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "pic %d %d %d", position.x, position.y, level);
    for (int n = 0; player[n] != -1; n++)
        dprintf(s->fd_gui, " %d", player[n]);
    dprintf(s->fd_gui, "\n");
    return 0;
}
