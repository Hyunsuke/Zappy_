/*
** EPITECH PROJECT, 2024
** displayer_player.c
** File description:
**
*/

#include "all.h"

void print_players(struct_t *list)
{
    Player *current = list->head_player;

    while (current != NULL) {
        printf("ID: %d, FD: %d, Name: %s\n", current->id_player,
            current->fd, current->name_player);
        current = current->next;
    }
}
