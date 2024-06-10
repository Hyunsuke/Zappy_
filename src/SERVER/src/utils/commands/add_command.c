/*
** EPITECH PROJECT, 2024
** add_command.c
** File description:
** add command
*/

#include "all.h"

int add_command(player_t *player, char *command, int tick)
{
    if (player->command_count >= MAX_COMMANDS)
        return -1;
    player->commands[player->command_end].command = my_strdup(command);
    player->commands[player->command_end].tick = tick;
    player->command_end = (player->command_end + 1) % MAX_COMMANDS;
    player->command_count++;
    return 0;
}
