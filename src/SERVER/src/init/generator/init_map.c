/*
** EPITECH PROJECT, 2024
** init_map.c
** File description:
** Function init_map
*/

#include <stdlib.h>
#include <stdbool.h>
#include "all.h"

static void init_map_element(map_element_t *element, int client_nb)
{
    element->food = false;
    element->linemate = false;
    element->deraumere = false;
    element->sibur = false;
    element->mendiane = false;
    element->phiras = false;
    element->thystame = false;
    element->id_mob = my_malloc(client_nb * sizeof(int) + 2);
    if (element->id_mob == NULL)
        return;
    for (int i = 0; i < client_nb; i++) {
        element->id_mob[i] = -1;
    }
}

void init_map(struct_t *s)
{
    s->map = my_malloc(s->map_height * sizeof(map_element_t *) + 2);
    if (s->map == NULL)
        return;
    for (int i = 0; i < s->map_height; i++) {
        s->map[i] = my_malloc(s->map_width * sizeof(map_element_t) + 2);
        for (int j = 0; j < s->map_width; j++)
            init_map_element(&(s->map[i][j]), s->client_nb);
    }
}
