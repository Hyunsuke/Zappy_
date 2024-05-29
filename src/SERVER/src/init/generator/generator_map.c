/*
** EPITECH PROJECT, 2024
** generator_map.c
** File description:
** Function generator_map
*/

#include "server.h"

static void add_resource_to_map(struct_t *s, int quantity, bool *resource_ptr)
{
    int remaining = quantity;
    int x = 0;
    int y = 0;
    bool *resource;
    map_element_t *element;

    while (remaining > 0) {
        x = rand() % s->map_width;
        y = rand() % s->map_height;
        element = &(s->map[y][x]);
        resource = (bool *)((char *)element +
            ((char *)resource_ptr - (char *)&s->map[0][0].food));
        if (!*resource) {
            *resource = true;
            remaining--;
        }
    }
}

static bool is_resource_in_row(map_element_t *row, int map_width,
    bool *resource_ptr, bool *resource_base)
{
    map_element_t *element;
    bool *ressource;

    for (int x = 0; x < map_width; x++) {
        element = &(row[x]);
        ressource = (bool *)((char *)element +
            ((char *)resource_ptr - (char *)resource_base));
        if (*ressource)
            return true;
    }
    return false;
}

static bool is_resource_present(struct_t *s, bool *resource_ptr)
{
    for (int y = 0; y < s->map_height; y++) {
        if (is_resource_in_row(s->map[y], s->map_width, resource_ptr,
            &s->map[0][0].food)) {
            return true;
        }
    }
    return false;
}

static void ensure_minimum_resources(struct_t *s, bool **resources)
{
    map_element_t *element;
    bool *resource;
    int x;
    int y;

    for (int i = 0; i < 7; i++) {
        if (!is_resource_present(s, resources[i])) {
            x = rand() % s->map_width;
            y = rand() % s->map_height;
            element = &(s->map[y][x]);
            resource = (bool *)((char *)element +
                ((char *)resources[i] - (char *)&s->map[0][0].food));
            *resource = true;
        }
    }
}

void add_resources(struct_t *s)
{
    int quantities[7];
    float densities[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};
    bool *resources[] = {
        &s->map[0][0].food,
        &s->map[0][0].linemate,
        &s->map[0][0].deraumere,
        &s->map[0][0].sibur,
        &s->map[0][0].mendiane,
        &s->map[0][0].phiras,
        &s->map[0][0].thystame
    };

    for (int i = 0; i < 7; i++)
        quantities[i] = (int)(s->map_width * s->map_height * densities[i]);
    srand(time(NULL));
    for (int i = 0; i < 7; i++)
        add_resource_to_map(s, quantities[i], resources[i]);
    ensure_minimum_resources(s, resources);
}

void generator_map(struct_t *s)
{
    init_map(s);
    add_resources(s);
    print_map(s);
}
