/*
** EPITECH PROJECT, 2024
** run_commands.c
** File description:
** Function run_commands
*/

#include "all.h"

static int execute_command_dashboard(struct_t *s, char *command, char *buffer)
{
    command_struct_gui_t commands[] = {
        {"sst", c_sst_dashboard}, {NULL, NULL}
    };

    for (int i = 0; commands[i].command != NULL; i++) {
        if (strcmp(commands[i].command, command) == 0) {
            return commands[i].func(s, buffer);
        }
    }
    printf("Run_commands_dashboard -> Unknown command: %s\n", command);
    c_suc(s);
    return -1;
}

int run_commands_dashboard(struct_t *s, int fd, char *buffer)
{
    char *command;

    if (fd != s->fd_dashboard) {
        printf("Error FD dashboard not good\n");
        return -1;
    }
    command = strtok(buffer, "\n");
    if (command == NULL) {
        printf("Command not found -> run_commands_dashboard\n");
        return -1;
    }
    return execute_command_dashboard(s, command, buffer);
}
