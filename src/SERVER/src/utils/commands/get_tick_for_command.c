/*
** EPITECH PROJECT, 2024
** tick.c
** File description:
** tick
*/

#include "all.h"

command_t *initialize_command_ticks(void)
{
    command_t *command_ticks = (command_t *)my_malloc(12 * sizeof(command_t));
    char *commands[] = {"Forward\n", "Right\n", "Left\n", "Look\n",
                        "Inventory\n", "Broadcast\n", "Fork\n", "Eject\n",
                        "Take\n", "Set\n", "Incantation\n", NULL};
    int ticks[] = {7, 7, 7, 7, 1, 7, 42, 7, 7, 7, 300, 0};

    for (int i = 0; commands[i] != NULL; i++) {
        command_ticks[i].command = commands[i];
        command_ticks[i].tick = ticks[i];
    }
    command_ticks[11].command = NULL;
    command_ticks[11].tick = 1;
    return command_ticks;
}

static bool compare_until_whitespace(const char *str1, const char *str2)
{
    while (*str1 && isspace((unsigned char)*str1))
        str1++;
    while (*str2 && isspace((unsigned char)*str2))
        str2++;
    while (*str1 && *str2) {
        if (isspace((unsigned char)*str1) || isspace((unsigned char)*str2))
            break;
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    while (*str1 && isspace((unsigned char)*str1))
        str1++;
    while (*str2 && isspace((unsigned char)*str2))
        str2++;
    if (*str1 == '\0' && *str2 == '\0')
        return true;
    return false;
}

int get_tick_for_command(struct_t *s, char *command)
{
    command_t *command_ticks = s->command_ticks;
    char *tmp_command = my_strdup(command);

    for (int n = 0; tmp_command[n] != '\0'; n++)
        if (tmp_command[n] == ' ')
            tmp_command[n] = '\0';
    for (int i = 0; command_ticks[i].command != NULL; i++) {
        if (compare_until_whitespace(command, command_ticks[i].command)) {
            printf("Tick found: %d\n", command_ticks[i].tick);
            return command_ticks[i].tick;
        }
    }
    printf("NOT FOUND TICK - search -> .%s.\n", command);
    return 1;
}
