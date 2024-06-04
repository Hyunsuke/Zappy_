/*
** EPITECH PROJECT, 2024
** map.c
** File description:
** Function
*/

#include "all.h"

void add_id_to_map_element(map_element_t *map_element, int id_player)
{
    int count = 0;
    int *new_id_mob;

    if (map_element->id_mob == NULL) {
        map_element->id_mob = my_malloc(sizeof(int));
        map_element->id_mob[0] = id_player;
    } else {
        while (map_element->id_mob[count] != 0)
            count++;
        new_id_mob = my_realloc(map_element->id_mob,
            (count + 2) * sizeof(int));
        map_element->id_mob = new_id_mob;
        map_element->id_mob[count] = id_player;
        map_element->id_mob[count + 1] = 0;
    }
}

static void sub_remove_id_from_map_element(int **id_mob, int count,
    int id_player)
{
    int new_count = 0;
    int *new_id_mob;

    new_id_mob = my_malloc(count * sizeof(int));
    if (new_id_mob == NULL)
        return;
    for (int i = 0; i < count; i++) {
        if ((*id_mob)[i] != id_player) {
            new_count++;
            new_id_mob[new_count] = (*id_mob)[i];
        }
    }
    new_id_mob[new_count] = 0;
    my_free(*id_mob);
    *id_mob = new_id_mob;
}

void remove_id_from_map_element(map_element_t *map_element, int id_player)
{
    int count = 0;
    bool found = false;

    if (map_element->id_mob == NULL)
        return;
    while (map_element->id_mob[count] != 0)
        count++;
    for (int i = 0; i < count; i++) {
        if (map_element->id_mob[i] == id_player) {
            found = true;
            break;
        }
    }
    if (!found)
        return;
    sub_remove_id_from_map_element(&map_element->id_mob, count, id_player);
}
