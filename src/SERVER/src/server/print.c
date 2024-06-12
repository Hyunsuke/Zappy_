/*
** EPITECH PROJECT, 2024
** print.c
** File description:
** print function
*/

#include "all.h"

void print_response(char *buffer, int client_fd)
{
    size_t length = strlen(buffer);

    write(client_fd, buffer, length);
}
