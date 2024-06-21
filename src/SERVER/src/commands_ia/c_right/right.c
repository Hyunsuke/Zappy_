/*
** EPITECH PROJECT, 2024
** right.c
** File description:
** Function right
*/

#include "all.h"

int c_right(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    int orientation = 0;

    if (player == NULL) {
        printf("Player Not Found with this fd -> %d\n", fd);
        return -1;
    }
    player->view_direction++;
    if (player->view_direction == 4)
        player->view_direction = 0;
    dprintf(fd, "ok\n");
    define_orientation(player, &orientation);
    if (s->fd_gui != -1)
        dprintf(s->fd_gui, "ppo %d %d %d %d\n", player->id_player, player->x,
            player->y, orientation);
    return 0;
}
