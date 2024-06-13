/*
** EPITECH PROJECT, 2024
** print_elevations.c
** File description:
** print_elevations
*/

#include "all.h"

void print_elevations(struct_t *s)
{
    elevation_t *current = s->head_elevation;

    printf("Level From -> Level To | Nb Players | Linemate");
    printf(" | Deraumere | Sibur | Mendiane | Phiras | Thystame\n");
    while (current != NULL) {
        printf("      \t%d->%d                  %d            %d          %d",
                current->level_from, current->level_to,
                current->nb_players, current->resources.linemate,
                current->resources.deraumere);
        printf("          %d       %d         %d      %d\n",
            current->resources.sibur, current->resources.mendiane,
                current->resources.phiras, current->resources.thystame);
        current = current->next;
    }
}
