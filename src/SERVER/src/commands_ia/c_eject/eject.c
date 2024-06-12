/*
** EPITECH PROJECT, 2024
** eject.c
** File description:
** Function eject
*/

#include "all.h"

int inverse_direction(int digit)
{
    switch (digit) {
        case 1:
            return 3;
        case 3:
            return 1;
        case 2:
            return 4;
        case 4:
            return 2;
        default:
            return digit;
    }
}

static void eject_player_in_direction(struct_t *s, int direction,
    player_t *ejected)
{
    if (direction == 0)
        moove_top(s, ejected, ejected->x, ejected->y);
    if (direction == 1)
        moove_right(s, ejected, ejected->x, ejected->y);
    if (direction == 2)
        moove_bottom(s, ejected, ejected->x, ejected->y);
    if (direction == 3)
        moove_left(s, ejected, ejected->x, ejected->y);
    dprintf(ejected->fd, "eject: %d\n", inverse_direction(direction + 1));
}

int c_eject(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);

    for (int n = 0; n < s->map[player->x][player->y].nb_mob; n++) {
        if (s->map[player->x][player->y].id_mob[n] != player->id_player)
            eject_player_in_direction(s, player->view_direction,
                get_player_by_id(s, s->map[player->x][player->y].id_mob[n]));
    }
    remove_all_eggs_at_position_for_all_teams(s, player->x, player->y);
    print_response("ok\n", fd);
    return 0;
}
