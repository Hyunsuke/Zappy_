/*
** EPITECH PROJECT, 2023
** progress_incantation.c
** File description:
** incantation
*/

#include "all.h"

incantation_t *get_incantation(struct_t *s, int fd)
{
    incantation_t *current = s->head_progress_incantation;

    while (current != NULL) {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    printf("NOT FOUND INCANTATION\n");
    return NULL;
}
