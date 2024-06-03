/*
** EPITECH PROJECT, 2024
** add_team.c
** File description:
** Function add_team
*/

#include "all.h"

int add_player_to_team(struct_t *game_struct, int team_id, int player_id)
{
    team_t *team = get_team_by_id(game_struct, team_id);
    int player_count = 0;

    if (!team)
        return -1;
    if (team->players_id != NULL) {
        while (team->players_id[player_count] != 0)
            player_count++;
    }
    team->players_id = my_realloc(team->players_id,
        sizeof(int) * (player_count + 2));
    if (!team->players_id)
        return -1;
    team->players_id[player_count] = player_id;
    team->players_id[player_count + 1] = 0;
    return 0;
}
