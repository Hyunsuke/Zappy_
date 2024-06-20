/*
** EPITECH PROJECT, 2024
** sbp.c
** File description:
** Function sbp
*/

#include "all.h"

int c_sbp(struct_t *s)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "sbp\n");
    return 0;
}
