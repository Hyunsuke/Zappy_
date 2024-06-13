/*
** EPITECH PROJECT, 2024
** tiredness.c
** File description:
** tiredness food
*/

#include "all.h"

static void dead_player(struct_t *s, player_t *player)
{
    dprintf(player->fd, "dead\n");
    c_pdi(s, player->id_player);
    close(player->fd);
    remove_player(s, player->fd);
}

static void process_player_food(struct_t *s, player_t **current,
    player_t **prev)
{
    player_t *next = (*current)->next;

    (*current)->food--;
    printf("FOOD -> %d\n", (*current)->food);
    if ((*current)->food <= 0) {
        dead_player(s, *current);
        if (*prev == NULL)
            s->head_player = next;
        else
            (*prev)->next = next;
    } else {
        *prev = *current;
    }
    *current = next;
}

void tiredness(struct_t *s)
{
    player_t *current = s->head_player;
    player_t *prev = NULL;

    while (current != NULL)
        process_player_food(s, &current, &prev);
}
