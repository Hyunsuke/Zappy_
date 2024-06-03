/*
** EPITECH PROJECT, 2024
** run_commands.c
** File description:
** Function run_commands
*/

#include "all.h"

static int execute_command_ia(struct_t *s, int fd, char *command)
{
    command_struct_ia_t commands[] = {
        {"Forward\r\n", c_forward}, {"Right\r\n", c_right}, {"Left\r\n", c_left},
        {"Look\r\n", c_look}, {"Inventory\r\n", c_inventory},
        {"Broadcast text\r\n", c_broadcast_txt},
        {"Connect_nbr\r\n", c_connect_nbr}, {"Fork\r\n", c_fork},
        {"Eject\r\n", c_eject}, {"Take object\r\n", c_take_obj},
        {"Set object\r\n", c_set_obj},
        {"Incantation\r\n", c_incantation}, {NULL, NULL}
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

    command = strtok(buffer, "\n");
    if (command == NULL) {
        printf("Command not found -> run_commands_IA\n");
        return -1;
    }
    return execute_command_ia(s, fd, command);
}
