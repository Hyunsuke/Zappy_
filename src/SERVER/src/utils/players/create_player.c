/*
** EPITECH PROJECT, 2024
** create_player.c
** File description:
**
*/

#include "all.h"

void add_player(struct_t *list, int fd, int id_team, const char *name_player)
{
    Player *new_player = my_malloc(sizeof(Player));

    new_player->food = 0;
    new_player->linemate = 0;
    new_player->deraumere = 0;
    new_player->sibur = 0;
    new_player->mendiane = 0;
    new_player->phiras = 0;
    new_player->thystame = 0;
    new_player->fd = fd;
    new_player->id_player = list->next_id++;
    new_player->id_team = id_team;
    new_player->name_player = my_strdup(name_player);
    new_player->next = list->head_player;
    list->head_player = new_player;
    // Function for add player in map
}
