/*
** EPITECH PROJECT, 2024
** eject.c
** File description:
** Function eject
*/

#include "all.h"

int c_eject(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);

    for (int n = 0; n < s->map[player->x][player->y].nb_mob; n++) { //boucle inf à corriger normalement
        if (s->map[player->x][player->y].id_mob[n] != player->fd)
            c_forward(s, get_player_by_id(s,
                s->map[player->x][player->y].id_mob[n])->fd);
    }
    remove_all_eggs_at_position_for_all_teams(s, player->x, player->y);
    print_response("ok\n", fd);
    return 0;
}
