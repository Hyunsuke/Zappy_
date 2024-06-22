/*
** EPITECH PROJECT, 2024
** inventory.c
** File description:
** Function inventory
*/

#include "all.h"

int c_inventory(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    int length = snprintf(NULL, 0, "pin %d\n", player->id_player);
    char *command_gui = my_malloc(length + 1);

    snprintf(command_gui, length + 1, "pin %d\n", player->id_player);
    dprintf(fd, "[ food %d, linemate %d, deraumere %d, sibur %d, "
    "mendiane %d, phiras %d, thystame %d ]\n",
    player->food, player->linemate, player->deraumere, player->sibur,
    player->mendiane, player->phiras, player->thystame);
    c_pin(s, command_gui);
    my_free(command_gui);
    return 0;
}
