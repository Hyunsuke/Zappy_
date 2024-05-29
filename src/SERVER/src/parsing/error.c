/*
** EPITECH PROJECT, 2024
** error.c
** File description:
** error in parsing file
*/

#include "all.h"

static int is_num(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return 84;
    }
    return 0;
}

static void init_check(check_t *c)
{
    c->has_p = 0;
    c->has_x = 0;
    c->has_y = 0;
    c->has_n = 0;
    c->has_c = 0;
    c->has_f = 0;
    c->nb_team = 0;
}

static int check_p(int ac, char **av, check_t *c, int i)
{
    if (strcmp(av[i], "-p") == 0 && (i + 1) < ac) {
        if (is_num(av[i + 1]) == 84)
            return 84;
        c->has_p++;
    }
    return 0;
}

static int check_x(int ac, char **av, check_t *c, int i)
{
    if (strcmp(av[i], "-x") == 0 && (i + 1) < ac) {
        if (is_num(av[i + 1]) == 84)
            return 84;
        c->has_x++;
    }
    return 0;
}

static int check_y(int ac, char **av, check_t *c, int i)
{
    if (strcmp(av[i], "-y") == 0 && (i + 1) < ac) {
        if (is_num(av[i + 1]) == 84)
            return 84;
        c->has_y++;
    }
    return 0;
}

static int check_n(int ac, char **av, check_t *c, int *i)
{
    if (strcmp(av[*i], "-n") == 0 && (*i + 1) < ac) {
        while ((*i + 1) < ac && av[*i + 1][0] != '-') {
            c->nb_team++;
            (*i)++;
        }
        if (c->nb_team < 2)
            return 84;
        c->has_n++;
    }
    return 0;
}

static int check_c(int ac, char **av, check_t *c, int i)
{
    if (strcmp(av[i], "-c") == 0 && (i + 1) < ac) {
        if (is_num(av[i + 1]) == 84)
            return 84;
        c->has_c++;
    }
    return 0;
}

static int check_f(int ac, char **av, check_t *c, int i)
{
    if (strcmp(av[i], "-f") == 0 && (i + 1) < ac) {
        if (is_num(av[i + 1]) == 84)
            return 84;
        c->has_f++;
    }
    return 0;
}

static int check_option(int ac, char **av, check_t *c, int i)
{
    if (check_p(ac, av, c, i) == 84)
        return 84;
    if (check_x(ac, av, c, i) == 84)
        return 84;
    if (check_y(ac, av, c, i) == 84)
        return 84;
    if (check_n(ac, av, c, &i) == 84)
        return 84;
    if (check_c(ac, av, c, i) == 84)
        return 84;
    if (check_f(ac, av, c, i) == 84)
        return 84;
    return 0;
}

int check_error(int ac, char **av)
{
    check_t *c = my_malloc(sizeof(check_t));

    if (ac == 0)
        return 84;
    init_check(c);
    for (int i = 1; i < ac; i++) {
        if (check_option(ac, av, c, i) == 84)
            return 84;
    }
    if (c->has_p && c->has_x && c->has_y && c->has_n && c->has_c && c->has_f)
        return 0;
    else
        return 84;
}
