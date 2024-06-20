/*
** EPITECH PROJECT, 2024
** suc.c
** File description:
** Function suc
*/

#include "all.h"

int c_suc(struct_t *s)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "suc\n");
    return 0;
}
