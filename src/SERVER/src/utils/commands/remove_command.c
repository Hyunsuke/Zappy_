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
    my_free(player->commands[player->command_start].command);
    player->commands[player->command_start].command = NULL;
    player->commands[player->command_start].tick = 0;
    player->command_start = (player->command_start + 1) % MAX_COMMANDS;
    player->command_count--;
    return 0;
}
