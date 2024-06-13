/*
** EPITECH PROJECT, 2024
** moove.c
** File description:
** moove
*/

#include "all.h"

void moove_top(struct_t *s, player_t *mob, int x, int y)
{
    int save = 0;

    if (mob->view_direction == 0) {
        printf("top\n");
        mob->y--;
        if (mob->y < 0) {
            mob->y = s->map_height - 1;
            save = s->map_height - 1;
        } else {
            save = y - 1;
        }
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        add_id_to_map_element(&s->map[save][x].id_mob,
            &s->map[save][x].nb_mob, mob->id_player);
    }
}

void moove_bottom(struct_t *s, player_t *mob, int x, int y)
{
    int save = 0;

    if (mob->view_direction == 2) {
        printf("bottom\n");
        mob->y++;
        if (mob->y >= s->map_height) {
            mob->y = 0;
            save = 0;
        } else {
            save = y + 1;
        }
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        add_id_to_map_element(&s->map[save][x].id_mob,
            &s->map[save][x].nb_mob, mob->id_player);
    }
}

void moove_right(struct_t *s, player_t *mob, int x, int y)
{
    int save = 0;

    if (mob->view_direction == 1) {
        printf("right\n");
        mob->x++;
        if (mob->x >= s->map_width) {
            mob->x = 0;
            save = 0;
        } else {
            save = x + 1;
        }
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        add_id_to_map_element(&s->map[y][save].id_mob,
            &s->map[y][save].nb_mob, mob->id_player);
    }
}

void moove_left(struct_t *s, player_t *mob, int x, int y)
{
    int save = x - 1;

    if (mob->view_direction == 3) {
        printf("left\n");
        mob->x--;
        if (mob->x < 0) {
            mob->x = s->map_width - 1;
            save = s->map_width - 1;
        } else {
            save = x - 1;
        }
        remove_id_from_map_element(&s->map[y][x].id_mob, &s->map[y][x].nb_mob,
            mob->id_player);
        add_id_to_map_element(&s->map[y][save].id_mob,
            &s->map[y][save].nb_mob, mob->id_player);
    }
}
