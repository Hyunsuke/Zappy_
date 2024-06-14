/*
** EPITECH PROJECT, 2024
** add_command.c
** File description:
** add command
*/

#include "all.h"

int add_command(player_t *player, char *command, int tick)
{
    if (player == NULL)
        return -1;
    if (player->command_count >= MAX_COMMANDS)
        return -1;
    player->commands[player->command_count].command = my_strdup(command);
    player->commands[player->command_count].tick = tick;
    player->command_count++;
    return 0;
}
