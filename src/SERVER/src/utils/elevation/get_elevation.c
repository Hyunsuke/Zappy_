/*
** EPITECH PROJECT, 2024
** get_elevation.c
** File description:
** initialize_elevations
*/

#include "all.h"

elevation_t *get_elevation_by_level_to(struct_t *s, int level_to)
{
    elevation_t *current = s->head_elevation;

    while (current != NULL) {
        if (current->level_to == level_to)
            return current;
        current = current->next;
    }
    return NULL;
}
