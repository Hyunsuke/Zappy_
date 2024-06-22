/*
** EPITECH PROJECT, 2024
** tiredness.c
** File description:
** tiredness food
*/

#include "all.h"

static void dead_player(struct_t *s, server_t *server, player_t *player)
{
    printf("Dead player: %d [ID team -> %d]\n", player->id_player,
        player->id_team);
    dprintf(player->fd, "dead\n");
    c_pdi(s, player->id_player);
    close(player->fd);
    FD_CLR(player->fd, &server->fd_tab);
    remove_player_from_team(s, player->id_team, player->id_player);
    remove_player(s, player->fd);
}

static void process_player_food(struct_t *s, server_t *server,
    player_t **current, player_t **prev)
{
    player_t *next = (*current)->next;

    (*current)->food--;
    if ((*current)->food <= 0) {
        dead_player(s, server, *current);
        if (*prev == NULL)
            s->head_player = next;
        else
            (*prev)->next = next;
    } else {
        *prev = *current;
    }
    *current = next;
}

void tiredness(struct_t *s, server_t *server)
{
    player_t *current = s->head_player;
    player_t *prev = NULL;

    while (current != NULL)
        process_player_food(s, server, &current, &prev);
}
