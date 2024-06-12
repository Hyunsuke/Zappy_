/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main.c
*/

#include "all.h"

int main(int ac, char **av)
{
    struct_t *s = my_malloc(sizeof(struct_t));
    server_t *server = my_malloc(sizeof(server_t));

    init_struct(s);
    if (parsing(ac, av, s) == 84)
        return 84;
    generator_map(s);
    server_gestion(server, s);
}
