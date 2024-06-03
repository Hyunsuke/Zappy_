/*
** EPITECH PROJECT, 2024
** displayer_player.c
** File description:
** display
*/

#include "all.h"

void print_players(struct_t *list)
{
    player_t *current = list->head_player;

    while (current != NULL) {
        printf("ID: %d, FD: %d\n", current->id_player, current->fd);
        current = current->next;
    }
}
