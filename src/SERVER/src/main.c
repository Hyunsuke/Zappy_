/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main.c
*/

#include "server.h"

int main(int ac, char **av)
{
    struct_t *s = my_malloc(sizeof(struct_t));

    parsing(ac, av, s);
    generator_map(s);
}
