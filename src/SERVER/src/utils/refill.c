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
}
