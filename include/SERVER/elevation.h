/*
** EPITECH PROJECT, 2024
** elevation.h
** File description:
** elevation include
*/

#ifndef ELEVATION_H
    #define ELEVATION_H
    #include "struct.h"

////////////////////////////////////
////// ELEVATION //////////////////
//////////////////////////////////

typedef struct resources_s {
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} resources_t;

typedef struct elevation_s {
    int level_from;
    int level_to;
    int nb_players;
    resources_t resources;
    struct elevation_s *next;
} elevation_t;

////////////////////////////////


void add_elevation(elevation_t **head, int level_final, int nb_players,
    resources_t resources);
elevation_t *init_elevation(void);
void print_elevations(struct_t *s);
elevation_t *get_elevation_by_level_to(struct_t *s, int level_to);

#endif /* !ELEVATION_H */
