/*
** EPITECH PROJECT, 2024
** msz.c
** File description:
** Function msz
*/

#include "all.h"

int c_msz(struct_t *s, char *buffer)
{
    (void)buffer;
    dprintf(s->fd_gui, "msz %d %d\n", s->map_width, s->map_height);
    return 0;
}
