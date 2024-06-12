/*
** EPITECH PROJECT, 2024
** error.c
** File description:
** error
*/

#include "all.h"


int my_error(char *message)
{
    fprintf(stderr, message);
    return 84;
}
