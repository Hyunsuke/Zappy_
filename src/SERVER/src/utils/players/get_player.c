/*
** EPITECH PROJECT, 2024
** displayer_player.c
** File description:
**
*/

#include "all.h"

Player* get_player_by_fd(struct_t *list, int fd)
{
    Player *current = list->head_player;

    while (current != NULL) {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    return NULL;
}

Player* get_player_by_id(struct_t *list, int id_player)
{
    Player *current = list->head_player;

    while (current != NULL) {
        if (current->id_player == id_player)
            return current;
        current = current->next;
    }
    return NULL;
}
