/*
** EPITECH PROJECT, 2024
** get_team.c
** File description:
** Function get_team
*/

#include "all.h"

int add_position_egg_to_team(struct_t *s, int team_id, int x, int y)
{
    team_t *team = get_team_by_id(s, team_id);
    position_t *new_position;
    int pos_count = 0;

    if (!team)
        return -1;
    new_position = my_malloc(sizeof(position_t));
    new_position->x = x;
    new_position->y = y;
    if (team->position_egg != NULL) {
        while (team->position_egg[pos_count] != NULL)
            pos_count++;
    }
    team->position_egg = my_realloc(team->position_egg,
        sizeof(position_t *) * (pos_count + 2));
    team->position_egg[pos_count] = new_position;
    team->position_egg[pos_count + 1] = NULL;
    return 0;
}

// Function to get and remove the first egg position from a team
position_t *get_and_remove_first_egg_position(struct_t *s,
    int team_id)
{
    team_t *team = get_team_by_id(s, team_id);
    position_t *first_position;
    int i = 0;

    if (!team || !team->position_egg || !team->position_egg[0])
        return NULL;
    first_position = team->position_egg[0];
    while (team->position_egg[i] != NULL) {
        team->position_egg[i] = team->position_egg[i + 1];
        i++;
    }
    return first_position;
}
