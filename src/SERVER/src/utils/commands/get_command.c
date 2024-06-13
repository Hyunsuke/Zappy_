/*
** EPITECH PROJECT, 2024
** get_command.c
** File description:
** get command
*/

#include "all.h"

command_t *get_oldest_command(player_t *player)
{
    if (player->command_count == 0)
        return NULL;
    return &player->commands[0];
}

int get_command_count(player_t *player)
{
    return player->command_count;
}
