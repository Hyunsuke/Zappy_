/*
** EPITECH PROJECT, 2024
** print_command.c
** File description:
** print command
*/

#include "all.h"

void print_all_commands(player_t *player)
{
    int index = player->command_start;

    if (player->command_count == 0) {
        printf("No commands available\n");
        return;
    }
    for (int i = 0; i < player->command_count; i++) {
        printf("Command %d: %s (TICK: %d)\n",
            i + 1, player->commands[index].command,
                player->commands[index].tick);
        index = (index + 1) % MAX_COMMANDS;
    }
}
