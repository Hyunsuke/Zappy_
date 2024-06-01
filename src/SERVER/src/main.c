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

    if (parsing(ac, av, s) == 84)
        return 84;
    s->head_player = NULL;
    s->next_id = 0;
    s->fd_gui = -1;
    generator_map(s);
    server_gestion(server, s);
}
