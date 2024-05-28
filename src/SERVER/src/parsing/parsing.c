/*
** EPITECH PROJECT, 2024
** parsing.c
** File description:
** parsing file
*/

#include "server.h"

static void parse_names(int ac, char **av, int i, struct_t *s)
{
    int names_start = i + 1;
    int names_end = names_start;
    int name_count = 0;

    while (names_end < ac && av[names_end][0] != '-') {
        names_end++;
    }
    name_count = names_end - names_start;
    s->list_names = my_malloc(name_count * sizeof(char *));
    for (int j = 0; j < name_count; j++) {
        s->list_names[j] = strdup(av[names_start + j]);
    }
    i = names_end - 1;
}

static void def_int_values(int ac, char **av, struct_t *s, int i)
{
    if (strcmp(av[i], "-p") == 0 && i + 1 < ac) {
        i++;
        s->port = atoi(av[i]);
    }
    if (strcmp(av[i], "-x") == 0 && i + 1 < ac) {
        i++;
        s->map_width = atoi(av[i]);
    }
    if (strcmp(av[i], "-y") == 0 && i + 1 < ac) {
        i++;
        s->map_height = atoi(av[i]);
    }
}

void parse_args(int ac, char **av, struct_t *s)
{
    for (int i = 1; i < ac; i++) {
        def_int_values(ac, av, s, i);
        if (strcmp(av[i], "-n") == 0 && i + 1 < ac) {
            i++;
            parse_names(ac, av, i, s);
        }
        if (strcmp(av[i], "-c") == 0 && i + 1 < ac) {
            i++;
            s->client_nb = atoi(av[i]);
        }
        if (strcmp(av[i], "-f") == 0 && i + 1 < ac) {
            i++;
            s->time = atoi(av[i]);
        }
    }
}

int parsing(int ac, char **av, struct_t *s)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./zappy_server -p port -x width -y height -n name1 ");
        printf("name2 ... -c clientsNb -f freq\n");
        return 0;
    }
    if (check_error(ac, av) == 84)
        return 84;
    parse_args(ac, av, s);
    return 0;
}
