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
    int orientation = 0;

    moove_top(s, ejected, ejected->x, ejected->y);
    moove_right(s, ejected, ejected->x, ejected->y);
    moove_bottom(s, ejected, ejected->x, ejected->y);
    moove_left(s, ejected, ejected->x, ejected->y);
    define_orientation(ejected, &orientation);
    dprintf(ejected->fd, "eject: %d\n", inverse_direction(direction + 1));
    if (s->fd_gui != -1)
        dprintf(s->fd_gui, "ppo %d %d %d %d\n", ejected->id_player, ejected->x,
        ejected->y, orientation);
}

static void send_eject_to_gui(struct_t *s, player_t *player, bool animation)
{
    if (animation == false)
        return;
    if (s->fd_gui != -1)
        dprintf(s->fd_gui, "pex %d\n", player->id_player);
}

int c_eject(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    bool sendAnimation = false;

    for (int n = 0; n < s->map[player->y][player->x].nb_mob; n++) {
        if (s->map[player->y][player->x].id_mob[n] != player->id_player) {
            sendAnimation = true;
            send_eject_to_gui(s, player, sendAnimation);
            eject_player_in_direction(s, player->view_direction,
                get_player_by_id(s, s->map[player->y][player->x].id_mob[n]));
        }
    }
    remove_all_eggs_at_position_for_all_teams(s, player->y, player->x);
    dprintf(fd, "ok\n");
    return 0;
}
