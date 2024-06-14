/*
** EPITECH PROJECT, 2024
** pie.c
** File description:
** Function pie
*/

#include "all.h"

int c_pie(struct_t *s, int x, int y, char *incantation_result)
{
    dprintf(s->fd_gui, "pie %d %d %s\n", x, y, incantation_result);
    return 0;
}
