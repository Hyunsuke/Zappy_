/*
** EPITECH PROJECT, 2024
** map.c
** File description:
** Function
*/

#include "all.h"

void add_id_to_map_element(int **id_mob, int *size, int id_player)
{
    (*size)++;
    if ((*id_mob) != NULL)
        *id_mob = my_realloc(*id_mob, (*size) * sizeof(int));
    else
        *id_mob = my_malloc(sizeof(int) * 1);
    (*id_mob)[*size - 1] = id_player;
}

void remove_id_from_map_element(int **id_mob, int *size, int id_player)
{
    int index = -1;

    for (int i = 0; i < *size; i++) {
        if ((*id_mob)[i] == id_player) {
            index = i;
            break;
        }
    }
    if (index == -1)
        return;
    for (int i = index; i < *size - 1; i++)
        (*id_mob)[i] = (*id_mob)[i + 1];
    (*size)--;
    if (*size == 0)
        (*id_mob) = NULL;
    *id_mob = my_realloc(*id_mob, (*size) * sizeof(int));
    if (*id_mob == NULL && *size > 0) {
        full_free();
        exit(1);
    }
}
