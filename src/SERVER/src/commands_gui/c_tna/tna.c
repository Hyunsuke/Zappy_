/*
** EPITECH PROJECT, 2024
** tna.c
** File description:
** Function tna
*/

#include "all.h"

int c_tna(struct_t *s, char *buffer)
{
    (void)buffer;
    for (int n = 0; s->list_names[n]; n++)
        dprintf(s->fd_gui, "tna %s\n", s->list_names[n]);
    return 0;
}
