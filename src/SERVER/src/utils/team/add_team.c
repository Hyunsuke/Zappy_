/*
** EPITECH PROJECT, 2024
** add_team.c
** File description:
** Function add_team
*/

#include "all.h"

int add_in_team_list(int player_id, team_t *team,
    int player_count)
{
    team->players_id = my_realloc(team->players_id,
        sizeof(int) * (player_count + 2));
    if (!team->players_id)
        return -1;
    team->players_id[player_count] = player_id;
    team->players_id[player_count + 1] = -1;
    return 0;
}

int add_player_to_team(struct_t *s, int team_id, int player_id, int fd)
{
    team_t *team = get_team_by_id(s, team_id);
    int player_count = 0;
    int slot_available = 0;

    if (!team)
        return -1;
    if (team->players_id != NULL) {
        while (team->players_id[player_count] != -1)
            player_count++;
    }
    slot_available = team->max_cli - player_count;
    dprintf(fd, "%d\n%d %d\n", slot_available, s->map_width, s->map_height);
    if (player_count >= team->max_cli)
        return -1;
    if (add_in_team_list(player_id, team, player_count) == -1)
        return -1;
    return 0;
}

static void shift_player_list(int *players_id, int start_index)
{
    int i;

    for (i = start_index; players_id[i] != -1; i++)
        players_id[i] = players_id[i + 1];
    players_id[i] = -1;
}

int remove_player_from_team(struct_t *s, int team_id, int player_id)
{
    team_t *team = get_team_by_id(s, team_id);
    int player_count = 0;

    if (!team || !team->players_id)
        return -1;
    if (!team->players_id)
        return -1;
    while (team->players_id[player_count] != -1) {
        if (team->players_id[player_count] == player_id) {
            shift_player_list(team->players_id, player_count);
            return 0;
        }
        player_count++;
    }
    return -1;
}
