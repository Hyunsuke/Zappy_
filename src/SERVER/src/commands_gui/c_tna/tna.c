/*
** EPITECH PROJECT, 2024
** tna.c
** File description:
** Function tna
*/

#include "all.h"

int c_tna(struct_t *s, char *buffer)
{
    team_t *current_team = s->head_team;

    (void)buffer;
    if (s->fd_gui == -1)
        return -1;
    while (current_team != NULL) {
        dprintf(s->fd_gui, "tna %s\n", current_team->name);
        current_team = current_team->next;
    }
    return 0;
}
