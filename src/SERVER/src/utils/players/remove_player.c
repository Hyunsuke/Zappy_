/*
** EPITECH PROJECT, 2024
** remove_player.c
** File description:
** remove
*/

#include "all.h"

static void remove_current_player(struct_t *s, player_t *current,
    player_t *previous)
{
    if (previous == NULL) {
        s->head_player = current->next;
    } else {
        previous->next = current->next;
    }
    remove_id_from_map_element(&s->map[current->y][current->x].id_mob,
        &s->map[current->y][current->x].nb_mob, current->id_player);
    my_free(current);
}

void remove_player(struct_t *s, int fd)
{
    player_t *current = s->head_player;
    player_t *previous = NULL;

    while (current != NULL) {
        if (current->fd == fd) {
            remove_current_player(s, current, previous);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Player with fd %d not found\n", fd);
}
