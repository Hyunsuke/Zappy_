/*
** EPITECH PROJECT, 2024
** run_commands.c
** File description:
** Function run_commands
*/

#include "all.h"

static int execute_command_ia(struct_t *s, int fd, char *buffer, char *command)
{
    command_struct commands[] = {
        {"Forward", c_forward}, {"Right", c_right}, {"Left", c_left},
        {"Look", c_look}, {"Inventory", c_inventory}, {"Broadcast text", c_broadcast_txt},
        {"Connect_nbr", c_connect_nbr}, {"Fork", c_fork}, {"Eject", c_eject},
        {"Take object", c_take_obj}, {"Set object", c_set_obj},
        {"Incantation", c_incantation}, {NULL, NULL}
    };

    for (int i = 0; commands[i].command != NULL; i++) {
        if (strcmp(commands[i].command, command) == 0)
            return commands[i].func(s, fd);
    }
    printf("Run_commands_IA -> Unknown command: %s\n", command);
    return -1;
}

int run_commands_ia(struct_t *s, int fd, char *buffer)
{
    char *command;

    command = strtok(buffer, " ");
    if (command == NULL) {
        printf("Command not found -> run_commands_IA\n");
        return -1;
    }
    return execute_command_ia(s, fd, buffer, command);
}
