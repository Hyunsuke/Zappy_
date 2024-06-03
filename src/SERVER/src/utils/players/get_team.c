/*
** EPITECH PROJECT, 2024
** get_team.c
** File description:
** get team name by id
*/

#include "all.h"

char *get_team_by_id(struct_t *s, int id)
{
    for (int i = 0; s->id_teams[i]; i++) {
        if (s->id_teams[i] == id) {
            return s->list_names[i];
        }
    }
    return NULL;
}
