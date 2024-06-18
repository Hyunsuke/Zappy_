/*
** EPITECH PROJECT, 2024
** connect_nbr.c
** File description:
** Function connect_nbr
*/

#include "all.h"

int c_connect_nbr(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    int *list_id_player;
    int nb_player = 0;
    team_t *team = get_team_by_id(s, player->id_team);

    if (team == NULL) {
        return -1;
    } else {
        list_id_player = team->players_id;
    }
    if (list_id_player == NULL) {
        dprintf(fd, "%d\n", team->max_cli);
        return 0;
    }
    for (int n = 0; list_id_player[n] != -1; n++)
        nb_player++;
    dprintf(fd, "%d\n", (team->max_cli - nb_player));
    return 0;
}
