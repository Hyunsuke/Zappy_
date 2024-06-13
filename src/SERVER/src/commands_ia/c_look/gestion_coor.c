/*
** EPITECH PROJECT, 2024
** gestion_coor.c
** File description:
** gestion coor in case loop
*/

#include "all.h"

static void adjust_up(int *y, int map_height)
{
    if (*y - 1 < 0)
        *y = map_height - 1;
    else
        (*y)--;
}

static void adjust_down(int *y, int map_height)
{
    if (*y + 1 >= map_height)
        *y = 0;
    else
        (*y)++;
}

static void adjust_right(int *x, int map_width)
{
    if (*x + 1 >= map_width)
        *x = 0;
    else
        (*x)++;
}

static void adjust_left(int *x, int map_width)
{
    if (*x - 1 < 0)
        *x = map_width - 1;
    else
        (*x)--;
}

void adjust_new_coor(struct_t *s, player_t *mob, int *x, int *y)
{
    switch (mob->view_direction) {
        case 0:
            adjust_up(y, s->map_height);
            break;
        case 1:
            adjust_right(x, s->map_width);
            break;
        case 2:
            adjust_down(y, s->map_height);
            break;
        case 3:
            adjust_left(x, s->map_width);
            break;
    }
}
