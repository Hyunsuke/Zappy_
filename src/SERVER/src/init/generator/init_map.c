/*
** EPITECH PROJECT, 2024
** init_map.c
** File description:
** Function init_map
*/

#include <stdlib.h>
#include <stdbool.h>
#include "all.h"

static void init_map_element(map_element_t *element)
{
    element->food = 0;
    element->linemate = 0;
    element->deraumere = 0;
    element->sibur = 0;
    element->mendiane = 0;
    element->phiras = 0;
    element->thystame = 0;
    element->nb_mob = 0;
    element->id_mob = NULL;
}

void init_map(struct_t *s)
{
    s->map = my_malloc(s->map_height * sizeof(map_element_t *) + 2);
    if (s->map == NULL)
        return;
    for (int i = 0; i < s->map_height; i++) {
        s->map[i] = my_malloc(s->map_width * sizeof(map_element_t) + 2);
        for (int j = 0; j < s->map_width; j++)
            init_map_element(&(s->map[i][j]));
    }
}
