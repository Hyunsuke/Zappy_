/*
** EPITECH PROJECT, 2024
** forward.c
** File description:
** Function forward
*/

#include "all.h"

void define_orientation(player_t *mob, int *orientation)
{
    if (mob->view_direction == 0)
        *orientation = 3;
    if (mob->view_direction == 1)
        *orientation = 2;
    if (mob->view_direction == 2)
        *orientation = 1;
    if (mob->view_direction == 3)
        *orientation = 4;
}

int c_forward(struct_t *s, int fd)
{
    player_t *mob = get_player_by_fd(s, fd);
    int x = 0;
    int y = 0;
    int orientation = 0;

    if (mob == NULL)
        return 0;
    x = mob->x;
    y = mob->y;
    moove_top(s, mob, x, y);
    moove_right(s, mob, x, y);
    moove_bottom(s, mob, x, y);
    moove_left(s, mob, x, y);
    dprintf(fd, "ok\n");
    define_orientation(mob, &orientation);
    if (s->fd_gui != -1)
        dprintf(s->fd_gui, "ppo %d %d %d %d\n", mob->id_player, mob->x, mob->y,
            orientation);
    return 0;
}
