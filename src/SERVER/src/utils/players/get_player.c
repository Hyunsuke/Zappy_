/*
** EPITECH PROJECT, 2024
** get_player.c
** File description:
** get Player
*/

#include "all.h"

player_t *get_player_by_fd(struct_t *list, int fd)
{
    player_t *current = list->head_player;

    while (current != NULL) {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    return NULL;
}

player_t *get_player_by_id(struct_t *list, int id_player)
{
    player_t *current = list->head_player;

    while (current != NULL) {
        if (current->id_player == id_player)
            return current;
        current = current->next;
    }
    return NULL;
}
