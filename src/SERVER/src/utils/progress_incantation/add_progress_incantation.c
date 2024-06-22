/*
** EPITECH PROJECT, 2023
** progress_incantation.c
** File description:
** incantation
*/

#include "all.h"

void add_incantation(struct_t *s, int fd, int *player_ids, int num_players)
{
    incantation_t *new_incantation =
        (incantation_t *)my_malloc(sizeof(incantation_t));
    player_t *player = get_player_by_fd(s, fd);

    new_incantation->player_ids = my_malloc(sizeof(int *) * (num_players + 2));
    for (int i = 0; i < num_players; i++)
        new_incantation->player_ids[i] = player_ids[i];
    new_incantation->num_players = num_players;
    new_incantation->fd = fd;
    new_incantation->next = s->head_progress_incantation;
    new_incantation->position = my_malloc(sizeof(struct position_s));
    new_incantation->position->x = player->x;
    new_incantation->position->y = player->y;
    s->head_progress_incantation = new_incantation;
}

static bool is_player_in_id_list(int *player_ids, int num_players,
    int player_id)
{
    for (int i = 0; i < num_players; i++) {
        if (player_ids[i] == player_id)
            return true;
    }
    return false;
}

bool is_player_in_incantation(struct_t *s, int player_id)
{
    incantation_t *current = s->head_progress_incantation;

    while (current != NULL) {
        if (is_player_in_id_list(current->player_ids, current->num_players,
            player_id))
            return true;
        current = current->next;
    }
    return false;
}
