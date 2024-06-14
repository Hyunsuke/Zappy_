/*
** EPITECH PROJECT, 2024
** add_elevation.c
** File description:
** add_elevation
*/

#include "all.h"

static elevation_t *create_elevation(int level_from, int level_to,
    int nb_players, resources_t resources)
{
    elevation_t *new_elevation = my_malloc(sizeof(elevation_t));

    if (!new_elevation)
        return NULL;
    new_elevation->level_from = level_from;
    new_elevation->level_to = level_to;
    new_elevation->nb_players = nb_players;
    new_elevation->resources = resources;
    new_elevation->next = NULL;
    return new_elevation;
}

void add_elevation(elevation_t **head, int level_final, int nb_players,
    resources_t resources)
{
    elevation_t *new_elevation = create_elevation((level_final - 1),
        level_final, nb_players, resources);

    if (!new_elevation)
        return;
    new_elevation->next = *head;
    *head = new_elevation;
}
