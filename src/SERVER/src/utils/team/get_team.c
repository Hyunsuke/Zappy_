/*
** EPITECH PROJECT, 2024
** get_team.c
** File description:
** Function get_team
*/

#include "all.h"

team_t *get_team_by_id(struct_t *s, int team_id)
{
    team_t *current_team = s->head_team;

    while (current_team != NULL) {
        if (current_team->team_id == team_id)
            return current_team;
        current_team = current_team->next;
    }
    return NULL;
}

team_t *get_team_by_name(struct_t *s, const char *name)
{
    team_t *current_team = s->head_team;

    while (current_team != NULL) {
        if (strcmp(current_team->name, name) == 0) {
            return current_team;
        }
        current_team = current_team->next;
    }
    return NULL;
}
