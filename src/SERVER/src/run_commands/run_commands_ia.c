/*
** EPITECH PROJECT, 2024
** run_commands.c
** File description:
** Function run_commands
*/

#include "all.h"

static void config_obj(struct_t *s, char *command)
{
    char *part = strchr(command, ' ');
    int len = 0;
    int count = 0;

    if (part == NULL)
        return;
    for (int i = 1; part[i] != '\r'; i++) {
        len++;
    }
    s->obj = my_malloc(sizeof(char) * len + 1);
    for (int i = 1; part[i] != '\r'; i++) {
        s->obj[count] = part[i];
        count++;
    }
    s->obj[count] = '\0';
}

static void check_cmd_with_obj(struct_t *s, char *command)
{
    if (strncmp(command, "Set ", 4) == 0 ||
        strncmp(command, "Broadcast ", 10) == 0 ||
        strncmp(command, "Take ", 5) == 0) {
        config_obj(s, command);
    }
}

static int check_function(struct_t *s, int fd, char *command,
    command_struct_ia_t commands[])
{
    for (int i = 0; commands[i].command != NULL; i++) {
        if (strcmp(commands[i].command, command) == 0)
            return commands[i].func(s, fd);
    }
    printf("Run_commands_IA -> Unknown command: %s\n", command);
    return -1;
}

static int execute_command_ia(struct_t *s, int fd, char *command)
{
    command_struct_ia_t commands[] = {
        {"Forward", c_forward}, {"Right", c_right},
        {"Left", c_left}, {"Look", c_look},
        {"Inventory", c_inventory}, {"Set food", c_set_obj},
        {"Set linemate", c_set_obj}, {"Set deraumere", c_set_obj},
        {"Set sibur", c_set_obj}, {"Set mendiane", c_set_obj},
        {"Set phiras", c_set_obj}, {"Set thystame", c_set_obj},
        {"Broadcast text", c_broadcast_txt}, {"Fork", c_fork},
        {"Connect_nbr", c_connect_nbr}, {"Eject", c_eject},
        {"Take food", c_take_obj}, {"Take linemate", c_take_obj},
        {"Take deraumere", c_take_obj}, {"Take sibur", c_take_obj},
        {"Take mendiane", c_take_obj}, {"Take phiras", c_take_obj},
        {"Take thystame", c_take_obj}, {"Incantation", c_incantation},
        {NULL, NULL}
    };

    check_cmd_with_obj(s, command);
    return check_function(s, fd, command, commands);
}

int run_commands_ia(struct_t *s, int fd, char *buffer)
{
    char *command;

    command = strtok(buffer, "\r\n");
    if (command == NULL) {
        printf("ko\n");
        return -1;
    }
    return execute_command_ia(s, fd, command);
}
