/*
** EPITECH PROJECT, 2024
** parsing.c
** File description:
** parsing file
*/

#include "all.h"

static void parse_names(int ac, char **av, int i, struct_t *s)
{
    int names_start = i + 1;
    int names_end = names_start;
    int name_count = 0;

    s->head_team = NULL;
    s->next_id_team = 0;
    while (names_end < ac && av[names_end][0] != '-') {
        create_team(s, my_strdup(av[names_start + name_count]));
        name_count++;
        names_end++;
    }
    i = names_end - 1;
}

static void check_map_dimension(int nb)
{
    if (nb < 10 || nb > 30) {
        dprintf(2, "Invalid dimension: should be between 10 and 30\n");
        full_free();
        exit(84);
    }
}

static void check_port(int port)
{
    if (port < 0 || port > 65535) {
        dprintf(2, "Invalid port: should be between 0 and 65535\n");
        full_free();
        exit(84);
    }
}

static void def_int_values(int ac, char **av, struct_t *s, int i)
{
    if (strcmp(av[i], "-p") == 0 && i + 1 < ac) {
        i++;
        s->port = atoi(av[i]);
        check_port(s->port);
    }
    if (strcmp(av[i], "-x") == 0 && i + 1 < ac) {
        i++;
        s->map_width = atoi(av[i]);
        check_map_dimension(s->map_width);
    }
    if (strcmp(av[i], "-y") == 0 && i + 1 < ac) {
        i++;
        s->map_height = atoi(av[i]);
        check_map_dimension(s->map_height);
    }
}

static void assign_max_cli(struct_t *s)
{
    team_t *current;

    current = s->head_team;
    while (current != NULL) {
        current->max_cli = s->client_nb;
        current = current->next;
    }
}

static void check_frequency(int frequency)
{
    if (frequency < 1 || frequency > 1000) {
        dprintf(2, "Invalid frequency: should be between 2 and 1000\n");
        full_free();
        exit(84);
    }
}

static void check_client_nbr(int client_nbr)
{
    if (client_nbr < 1 || client_nbr > 200) {
        dprintf(2, "Invalid client_nbr: should be between 1 and 200\n");
        full_free();
        exit(84);
    }
}

static void parse_args(int ac, char **av, struct_t *s)
{
    for (int i = 1; i < ac; i++) {
        def_int_values(ac, av, s, i);
        if (strcmp(av[i], "-n") == 0 && i + 1 < ac) {
            parse_names(ac, av, i, s);
            i++;
        }
        if (strcmp(av[i], "-c") == 0 && i + 1 < ac) {
            i++;
            s->client_nb = atoi(av[i]);
            check_client_nbr(s->client_nb);
        }
        if (strcmp(av[i], "-f") == 0 && i + 1 < ac) {
            i++;
            s->time = atoi(av[i]);
            check_frequency(s->time);
        }
    }
    assign_max_cli(s);
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
