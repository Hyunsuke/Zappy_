/*
** EPITECH PROJECT, 2024
** gestion_first_coor.c
** File description:
** gestion coor after 1st case
*/

#include "all.h"

static void adjust_left_up(struct_t *s, int *x, int *y)
{
    if (*x - 1 < 0)
        *x = s->map_width - 1;
    else
        (*x)--;
    if (*y - 1 < 0)
        *y = s->map_height - 1;
    else
        (*y)--;
}

static void adjust_right_up(struct_t *s, int *x, int *y)
{
    if (*x + 1 >= s->map_width)
        *x = 0;
    else
        (*x)++;
    if (*y - 1 < 0)
        *y = s->map_height - 1;
    else
        (*y)--;
}

static void adjust_right_down(struct_t *s, int *x, int *y)
{
    if (*x + 1 >= s->map_width)
        *x = 0;
    else
        (*x)++;
    if (*y + 1 >= s->map_height)
        *y = 0;
    else
        (*y)++;
}

static void adjust_left_down(struct_t *s, int *x, int *y)
{
    if (*x - 1 < 0)
        *x = s->map_width - 1;
    else
        (*x)--;
    if (*y + 1 >= s->map_height)
        *y = 0;
    else
        (*y)++;
}

void adjust_first_coor(struct_t *s, player_t *mob, int *x, int *y)
{
    if (mob->view_direction == 0) {
        adjust_left_up(s, x, y);
    }
    if (mob->view_direction == 3) {
        adjust_left_down(s, x, y);
    }
    if (mob->view_direction == 1) {
        adjust_right_up(s, x, y);
    }
    if (mob->view_direction == 2) {
        adjust_right_down(s, x, y);
    }
}
