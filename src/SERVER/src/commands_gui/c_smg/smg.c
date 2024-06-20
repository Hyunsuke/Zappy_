/*
** EPITECH PROJECT, 2024
** smg.c
** File description:
** Function smg
*/

#include "all.h"

int c_smg(struct_t *s, char *msg)
{
    if (s->fd_gui == -1)
        return -1;
    dprintf(s->fd_gui, "smg %s\n", msg);
    return 0;
}
