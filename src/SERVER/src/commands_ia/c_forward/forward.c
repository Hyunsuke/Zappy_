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

void moove_top(struct_t *s, player_t *mob, int x, int y)
{
    if (mob->view_direction == 0) {
        printf("top\n");
        mob->y--;
        remove_id_from_map_element(&s->map[y][x], mob->id_player);
        if (y == 0) {
            add_id_to_map_element(&s->map[s->map_height][x], mob->id_player);
        } else {
            add_id_to_map_element(&s->map[y--][x], mob->id_player);
        }
    }
}

void moove_bottom(struct_t *s, player_t *mob, int x, int y)
{
    if (mob->view_direction == 2) {
        printf("bottom\n");
        mob->y++;
        remove_id_from_map_element(&s->map[y][x], mob->id_player);
        if (y == s->map_height)
            add_id_to_map_element(&s->map[0][x], mob->id_player);
        else
            add_id_to_map_element(&s->map[y++][x], mob->id_player);
    }
}

void moove_right(struct_t *s, player_t *mob, int x, int y)
{
    if (mob->view_direction == 1) {
        printf("right\n");
        mob->x++;
        remove_id_from_map_element(&s->map[y][x], mob->id_player);
        if (x == s->map_width) {
            add_id_to_map_element(&s->map[y][0], mob->id_player);
        } else {
            add_id_to_map_element(&s->map[y][x++], mob->id_player);
        }
    }
}

void moove_left(struct_t *s, player_t *mob, int x, int y)
{
    if (mob->view_direction == 3) {
        printf("left\n");
        mob->x--;
        remove_id_from_map_element(&s->map[y][x], mob->id_player);
        if (x == 0)
            add_id_to_map_element(&s->map[y][s->map_width], mob->id_player);
        else
            add_id_to_map_element(&s->map[y][x--], mob->id_player);
    }
}

int c_forward(struct_t *s, int fd)
{
    player_t *mob = get_mob(s, fd);
    int x = 0;
    int y = 0;
    int top = 0;

    printf("c_forward\n");
    if (mob == NULL)
        return 0;
    x = mob->x;
    y = mob->y;
    moove_top(s, mob, x, y);
    moove_right(s, mob, x, y);
    moove_bottom(s, mob, x, y);
    moove_left(s, mob, x, y);
    return 0;
}
