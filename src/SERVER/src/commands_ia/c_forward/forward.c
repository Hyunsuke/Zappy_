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
    int x = 0;
    int y = 0;
    player_t *mob = get_mob(s, fd);

    printf("c_forward\n");
    if (mob->view_direction == 0) {
        printf("top\n");
    }
    if (mob->view_direction == 1) {
        printf("right\n");
    }
    if (mob->view_direction == 2) {
        printf("bottom\n");
    }
    if (mob->view_direction == 3) {
        printf("left\n");
    }
    return 0;
}
