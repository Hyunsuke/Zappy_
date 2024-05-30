/*
** EPITECH PROJECT, 2024
** create_player.c
** File description:
**
*/

#include "all.h"

void add_player(struct_t *list, int fd, const char *name_player)
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
    new_player->name_player = my_strdup(name_player);
    new_player->next = list->head_player;
    list->head_player = new_player;
    // Function for add player in map
}

struct_t* init_player_list()
{
    struct_t *list = my_malloc(sizeof(struct_t));
    list->head_player = NULL;
    list->next_id = 0;
    return list;
}
