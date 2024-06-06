/*
** EPITECH PROJECT, 2024
** get_resource_code.c
** File description:
** Function get_resource_code
*/

#include "all.h"

int get_resource_code(char *obj)
{
    if (strcmp(obj, "food") == 0)
        return 0;
    if (strcmp(obj, "linemate") == 0)
        return 1;
    if (strcmp(obj, "deraumere") == 0)
        return 2;
    if (strcmp(obj, "sibur") == 0)
        return 3;
    if (strcmp(obj, "mendiane") == 0)
        return 4;
    if (strcmp(obj, "phiras") == 0)
        return 5;
    if (strcmp(obj, "thystame") == 0)
        return 6;
    return -1;
}
