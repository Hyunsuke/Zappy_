/*
** EPITECH PROJECT, 2024
** error.c
** File description:
** error
*/

#include "../../../include/server/server.h"


int my_error(char *message)
{
    fprintf(stderr, message);
    return 84;
}
