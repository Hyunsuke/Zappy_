/*
** EPITECH PROJECT, 2024
** gestion_str.c
** File description:
** gestion look str
*/

#include "all.h"

void add_in_str(struct_t *s, const char *element)
{
    size_t new_len = 0;
    char *new_str;

    if (s->look_str == NULL) {
        new_len = strlen(element) + 1;
        new_str = my_malloc(new_len * sizeof(char));
        new_str[0] = '\0';
    } else {
        new_len = strlen(s->look_str) + strlen(element) + 1;
        new_str = my_realloc(s->look_str, new_len * sizeof(char));
    }
    strcat(new_str, element);
    s->look_str = new_str;
}

void save_elements(struct_t *s, int x, int y)
{
    for (int i = 0; i < s->map[y][x].nb_mob; i++)
        add_in_str(s, " player");
    for (int i = 0; i < s->map[y][x].food; i++)
        add_in_str(s, " food");
    for (int i = 0; i < s->map[y][x].deraumere; i++)
        add_in_str(s, " deraumere");
    for (int i = 0; i < s->map[y][x].phiras; i++)
        add_in_str(s, " phiras");
    for (int i = 0; i < s->map[y][x].mendiane; i++)
        add_in_str(s, " mendiane");
    for (int i = 0; i < s->map[y][x].sibur; i++)
        add_in_str(s, " sibur");
    for (int i = 0; i < s->map[y][x].linemate; i++)
        add_in_str(s, " linemate");
    for (int i = 0; i < s->map[y][x].thystame; i++)
        add_in_str(s, " thystame");
    add_in_str(s, ",");
}
