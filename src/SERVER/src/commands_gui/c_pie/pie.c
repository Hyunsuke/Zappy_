/*
** EPITECH PROJECT, 2024
** pie.c
** File description:
** Function pie
*/

#include "all.h"

int c_pie(struct_t *s, int x, int y, int incantation_result)
{
    dprintf(s->fd_gui, "pie %d %d %d\n", x, y, incantation_result);
    return 0;
}
