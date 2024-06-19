/*
** EPITECH PROJECT, 2024
** fork.c
** File description:
** Function fork
*/

#include "all.h"

int c_fork(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    team_t *team = get_team_by_id(s, player->id_team);
    int nb_egg =
        add_position_egg_to_team(s, player->id_team, player->x, player->y);
    int position[2] = {player->x, player->y};

    c_enw(s, nb_egg, player->id_player, position);
    team->max_cli++;
    dprintf(fd, "ok\n");
    return 0;
}
