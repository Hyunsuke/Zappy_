/*
** EPITECH PROJECT, 2023
** progress_incantation.c
** File description:
** incantation
*/

#include "all.h"

static void remove_current_incantation(struct_t *s, incantation_t *current,
    incantation_t *previous)
{
    if (previous == NULL)
        s->head_progress_incantation = current->next;
    else
        previous->next = current->next;
    my_free(current->player_ids);
    my_free(current);
}

void remove_incantation(struct_t *s, int fd)
{
    incantation_t *current = s->head_progress_incantation;
    incantation_t *previous = NULL;

    while (current != NULL) {
        if (current->fd == fd) {
            remove_current_incantation(s, current, previous);
            return;
        }
        previous = current;
        current = current->next;
    }
}
