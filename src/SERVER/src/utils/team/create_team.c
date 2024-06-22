/*
** EPITECH PROJECT, 2024
** create_team.c
** File description:
** Function create_team
*/

#include "all.h"

team_t *create_team(struct_t *s, const char *name)
{
    team_t *new_team = my_malloc(sizeof(team_t));

    if (!new_team)
        return NULL;
    new_team->name = my_strdup(name);
    new_team->team_id = s->next_id_team;
    s->next_id_team++;
    new_team->max_cli = 0;
    new_team->players_id = NULL;
    new_team->position_egg = NULL;
    new_team->next = s->head_team;
    s->head_team = new_team;
    return new_team;
}
