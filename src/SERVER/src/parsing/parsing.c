/*
** EPITECH PROJECT, 2024
** parsing.c
** File description:
** parsing file
*/

#include "server.h"

void parsing(int ac, char **av, struct_t *s)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./zappy_server -p port -x width -y height -n name1 ");
        printf("name2 ... -c clientsNb -f freq\n");
    }
}
