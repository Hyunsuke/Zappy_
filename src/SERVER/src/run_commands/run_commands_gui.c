/*
** EPITECH PROJECT, 2024
** run_commands.c
** File description:
** Function run_commands
*/

#include "all.h"

static int execute_command_gui(struct_t *s, char *command, char *buffer)
{
    int check_sst = 0;
    command_struct_gui_t commands[] = {
        {"msz", c_msz}, {"bct", c_bct}, {"mct", c_mct},
        {"tna", c_tna}, {"ppo", c_ppo}, {"plv", c_plv},
        {"pin", c_pin}, {"sgt", c_sgt},
        {"sst", c_sst}, {NULL, NULL}
    };

    if (strncmp(buffer, "sst", 3) == 0) {
        check_sst++;
    }
    for (int i = 0; commands[i].command != NULL; i++) {
        if (strcmp(commands[i].command, command) == 0 || (check_sst == 1 &&
            strncmp(commands[i].command, "sst", 3) == 0)) {
            return commands[i].func(s, buffer);
        }
    }
    printf("Run_commands_GUI -> Unknown command: %s\n", command);
    c_suc(s);
    return -1;
}

int run_commands_gui(struct_t *s, int fd, char *buffer)
{
    char *command;

    if (fd != s->fd_gui) {
        printf("Error FD GUI not good\n");
        return -1;
    }
    command = strtok(buffer, "\n");
    if (command == NULL) {
        printf("Command not found -> run_commands_GUI\n");
        return -1;
    }
    return execute_command_gui(s, command, buffer);
}
