/*
** EPITECH PROJECT, 2024
** gorbage_collector.c
** File description:
** Function my_malloc and my_free
*/

#include "all.h"

char *my_strdup(const char *str)
{
    size_t len;
    char *new_str;

    if (str == NULL)
        return NULL;
    len = strlen(str) + 1;
    new_str = my_malloc(len);
    strcpy(new_str, str);
    return new_str;
}
