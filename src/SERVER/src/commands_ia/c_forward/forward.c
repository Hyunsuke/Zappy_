/*
** EPITECH PROJECT, 2024
** forward.c
** File description:
** Function forward
*/

#include "all.h"

player_t *get_mob(struct_t *s, int fd)
{
    while (s->head_player != NULL) {
        if (s->head_player->fd == fd) {
            return s->head_player;
        }
        s->head_player = s->head_player->next;
    }
}

int c_forward(struct_t *s, int fd)
{
    player_t *mob = get_player_by_fd(s, fd);
    int x = 0;
    int y = 0;

    printf("c_forward\n");
    if (mob == NULL)
        return 0;
    x = mob->x;
    y = mob->y;
    moove_top(s, mob, x, y);
    moove_right(s, mob, x, y);
    moove_bottom(s, mob, x, y);
    moove_left(s, mob, x, y);
    printf("x position: %d: y position: %d\n", mob->x, mob->y);
    return 0;
}
