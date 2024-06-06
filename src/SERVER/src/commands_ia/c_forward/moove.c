/*
** EPITECH PROJECT, 2024
** moove.c
** File description:
** moove
*/

#include "all.h"

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
