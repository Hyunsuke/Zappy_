/*
** EPITECH PROJECT, 2024
** create_player.c
** File description:
** create
*/

#include "all.h"

void add_player(struct_t *list, int fd, int id_team)
{
    player_t *new_player = my_malloc(sizeof(player_t));

    new_player->food = 0;
    new_player->linemate = 0;
    new_player->deraumere = 0;
    new_player->sibur = 0;
    new_player->mendiane = 0;
    new_player->phiras = 0;
    new_player->thystame = 0;
    new_player->fd = fd;
    list->next_id++;
    new_player->id_player = list->next_id;
    new_player->id_team = id_team;
    new_player->next = list->head_player;
    list->head_player = new_player;
    // Function for add player in map
}
