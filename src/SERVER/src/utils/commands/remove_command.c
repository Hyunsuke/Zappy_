/*
** EPITECH PROJECT, 2024
** remove_command.c
** File description:
** remove command
*/

#include "all.h"

int remove_oldest_command(player_t *player)
{
    if (player->command_count == 0)
        return -1;
    my_free(player->commands[0].command);
    for (int i = 1; i < player->command_count; i++)
        player->commands[i - 1] = player->commands[i];
    player->command_count--;
    return 0;
}
