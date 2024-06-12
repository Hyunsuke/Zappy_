/*
** EPITECH PROJECT, 2024
** sgt.c
** File description:
** Function sgt
*/

#include "all.h"

int c_sgt(struct_t *s, char *buffer)
{
    (void)buffer;
    dprintf(s->fd_gui, "sgt %d\n", s->time);
    return 0;
}
