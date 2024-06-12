/*
** EPITECH PROJECT, 2024
** moove.c
** File description:
** moove
*/

#include "all.h"

void moove_top(struct_t *s, player_t *mob, int x, int y)
{
    int save = y - 1;

    if (mob->view_direction == 0) {
        printf("top\n");
        mob->y--;
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        if (y == 0) {
            add_id_to_map_element(&s->map[s->map_height][x].id_mob,
                &s->map[s->map_height][x].nb_mob, mob->id_player);
        } else {
            add_id_to_map_element(&s->map[save][x].id_mob,
                &s->map[save][x].nb_mob, mob->id_player);
        }
    }
}

void moove_bottom(struct_t *s, player_t *mob, int x, int y)
{
    int save = y + 1;

    if (mob->view_direction == 2) {
        printf("bottom\n");
        mob->y++;
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        if (y == s->map_height) {
            add_id_to_map_element(&s->map[0][x].id_mob,
                &s->map[0][x].nb_mob, mob->id_player);
        } else {
            add_id_to_map_element(&s->map[save][x].id_mob,
                &s->map[save][x].nb_mob, mob->id_player);
        }
    }
}

void moove_right(struct_t *s, player_t *mob, int x, int y)
{
    int save = x + 1;

    if (mob->view_direction == 1) {
        printf("right\n");
        mob->x++;
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        if (x == s->map_width) {
            add_id_to_map_element(&s->map[y][0].id_mob,
                &s->map[y][0].nb_mob, mob->id_player);
        } else {
            add_id_to_map_element(&s->map[y][save].id_mob,
                &s->map[y][save].nb_mob, mob->id_player);
        }
    }
}

void moove_left(struct_t *s, player_t *mob, int x, int y)
{
    int save = x - 1;

    if (mob->view_direction == 3) {
        printf("left\n");
        mob->x--;
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        if (x == 0) {
            add_id_to_map_element(&s->map[y][s->map_width].id_mob,
                &s->map[y][s->map_width].nb_mob, mob->id_player);
        } else {
            add_id_to_map_element(&s->map[y][save].id_mob,
                &s->map[y][save].nb_mob, mob->id_player);
        }
    }
}
