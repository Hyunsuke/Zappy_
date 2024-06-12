/*
** EPITECH PROJECT, 2024
** seg.c
** File description:
** Function seg
*/

#include "all.h"

int c_seg(struct_t *s, char *name_team)
{
    dprintf(s->fd_gui, "seg %s\n", name_team);
    return 0;
}
