/*
** EPITECH PROJECT, 2024
** get_team.c
** File description:
** Function get_team
*/

#include "all.h"

team_t* get_team_by_id(struct_t *game_struct, int team_id)
{
    team_t *current_team = game_struct->head_team;

    while (current_team) {
        if (current_team->team_id == team_id)
            return current_team;
        current_team = current_team->next;
    }
    return NULL;
}

team_t* get_team_by_name(struct_t *game_struct, const char *name)
{
    team_t *current_team = game_struct->head_team;

    while (current_team) {
        if (strncmp(current_team->name, name, 254) == 0)
            return current_team;
        current_team = current_team->next;
    }
    return NULL;
}
