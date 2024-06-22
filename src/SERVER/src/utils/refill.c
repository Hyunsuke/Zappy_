/*
** EPITECH PROJECT, 2024
** refill.c
** File description:
** refill map
*/

#include "all.h"

static map_rsc_t *get_nb_rsc_map(struct_t *s)
{
    map_rsc_t *rsc = my_malloc(sizeof(map_rsc_t));

    rsc->food = s->map_width * s->map_height * 0.5;
    rsc->linemate = s->map_width * s->map_height * 0.3;
    rsc->deraumere = s->map_width * s->map_height * 0.15;
    rsc->sibur = s->map_width * s->map_height * 0.1;
    rsc->mendiane = s->map_width * s->map_height * 0.1;
    rsc->phiras = s->map_width * s->map_height * 0.08;
    rsc->thystame = s->map_width * s->map_height * 0.05;
    return rsc;
}

static void remove_nb_item_map(struct_t *s, map_rsc_t *rsc_map)
{
    for (int y = 0; y < s->map_height; y++) {
        for (int x = 0; x < s->map_width; x++) {
            rsc_map->food -= s->map[y][x].food;
            rsc_map->linemate -= s->map[y][x].linemate;
            rsc_map->deraumere -= s->map[y][x].deraumere;
            rsc_map->sibur -= s->map[y][x].sibur;
            rsc_map->mendiane -= s->map[y][x].mendiane;
            rsc_map->phiras -= s->map[y][x].phiras;
            rsc_map->thystame -= s->map[y][x].thystame;
        }
    }
}

static void add_item_map(struct_t *s, map_rsc_t *rsc_map)
{
    for (; rsc_map->food > 0; rsc_map->food--)
        s->map[rand() % (s->map_height)][rand() % (s->map_width)].food++;
    for (; rsc_map->linemate > 0; rsc_map->linemate--)
        s->map[rand() % (s->map_height)][rand() % (s->map_width)].linemate++;
    for (; rsc_map->deraumere > 0; rsc_map->deraumere--)
        s->map[rand() % (s->map_height)][rand() % (s->map_width)].deraumere++;
    for (; rsc_map->sibur > 0; rsc_map->sibur--)
        s->map[rand() % (s->map_height)][rand() % (s->map_width)].sibur++;
    for (; rsc_map->mendiane > 0; rsc_map->mendiane--)
        s->map[rand() % (s->map_height)][rand() % (s->map_width)].mendiane++;
    for (; rsc_map->phiras > 0; rsc_map->phiras--)
        s->map[rand() % (s->map_height)][rand() % (s->map_width)].phiras++;
    for (; rsc_map->thystame > 0; rsc_map->thystame--)
        s->map[rand() % (s->map_height)][rand() % (s->map_width)].thystame++;
}

void refill_map(struct_t *s)
{
    map_rsc_t *rsc_map = get_nb_rsc_map(s);

    s->nb_tick_refill = 0;
    remove_nb_item_map(s, rsc_map);
    add_item_map(s, rsc_map);
}
