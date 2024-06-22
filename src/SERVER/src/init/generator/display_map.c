/*
** EPITECH PROJECT, 2024
** generator_map.c
** File description:
** Function generator_map
*/

#include "all.h"

void print_map_elem(struct_t *s, int i, int j)
{
    printf("Coor: x->%d y->:%d\n", j, i);
    printf("Food: %d\n", s->map[i][j].food);
    printf("Deraumere: %d\n", s->map[i][j].deraumere);
    printf("Linemate: %d\n", s->map[i][j].linemate);
    printf("Mendiane: %d\n", s->map[i][j].mendiane);
    printf("Phiras: %d\n", s->map[i][j].phiras);
    printf("Sibur: %d\n", s->map[i][j].sibur);
    printf("Thystame: %d\n", s->map[i][j].thystame);
}

void print_map(struct_t *s)
{
    for (int i = 0; i < s->map_height; i++) {
        for (int j = 0; j < s->map_width; j++) {
            print_map_elem(s, i, j);
        }
    }
}
