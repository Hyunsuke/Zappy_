/*
** EPITECH PROJECT, 2024
** tick.c
** File description:
** tick
*/

#include "all.h"

command_t* initialize_command_ticks(int *num_commands)
{
    int tmp_num_commands = 11;
    command_t *command_ticks =
        (command_t *)my_malloc(tmp_num_commands * sizeof(command_t));
    char *commands[] = {"Forward", "Right", "Left", "Look", "Inventory",
                                "Broadcast", "Fork", "Eject", "Take", "Set",
                                    "Incantation"};
    int ticks[] = {7, 7, 7, 7, 1, 7, 42, 7, 7, 7, 300};

    *num_commands = tmp_num_commands;
    for (int i = 0; i < *num_commands; i++) {
        command_ticks[i].command = commands[i];
        command_ticks[i].tick = ticks[i];
    }
    return command_ticks;
}

static bool compare_until_whitespace(const char *str1, const char *str2)
{
    while (*str1 && *str2) {
        if (*str1 == ' ' || *str1 == '\n' || *str1 == '\0' ||
            *str2 == ' ' || *str2 == '\n' || *str2 == '\0') {
            break;
        }
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    if ((*str1 == ' ' || *str1 == '\n' || *str1 == '\0') &&
        (*str2 == ' ' || *str2 == '\n' || *str2 == '\0'))
        return true;
    return false;
}

int get_tick_for_command(struct_t *s, char *command)
{
    command_t *command_ticks = s->command_ticks;

    for (int i = 0; i < s->nb_command_ticks; i++) {
        if (compare_until_whitespace(command, command_ticks[i].command)) {
            return command_ticks[i].tick;
        }
    }
    return 1;
}
