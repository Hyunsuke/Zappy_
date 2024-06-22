/*
** EPITECH PROJECT, 2024
** run_commands.c
** File description:
** Function run_commands
*/

#include "all.h"

static void define_obj(struct_t *s, char *command, int inter, int len)
{
    int j = 0;

    s->obj = my_malloc(sizeof(char) * (len + 1));
    if (!s->obj) {
        full_free();
        exit(0);
    }
    for (j = 0; j < len; j++)
        s->obj[j] = command[inter + j];
    s->obj[len] = '\0';
}

static void config_obj(struct_t *s, char *command)
{
    int i = 0;
    int len = 0;
    int inter = 0;

    for (; command[i] != ' ' && command[i] != '\0'; i++);
    if (command[i] == '\0')
        return;
    i++;
    inter = i;
    while (command[i] != '\r' && command[i] != '\0') {
        len++;
        i++;
    }
    define_obj(s, command, inter, len);
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
    int check_bro = 0;

    if (strncmp(command, "Broadcast ", 10) == 0) {
        check_bro++;
    }
    for (int i = 0; commands[i].command != NULL; i++) {
        if (strcmp(commands[i].command, command) == 0 || (check_bro == 1 &&
            strncmp(commands[i].command, "Broadcast ", 11) == 0)) {
            printf("Running command %s for ID player %d\n",
                commands[i].command, get_player_by_fd(s, fd)->id_player);
            return commands[i].func(s, fd);
        }
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
        {"Broadcast ", c_broadcast_txt}, {"Fork", c_fork},
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

    command = strtok(buffer, "\n");
    if (command == NULL) {
        printf("ko\n");
        return -1;
    }
    return execute_command_ia(s, fd, command);
}
