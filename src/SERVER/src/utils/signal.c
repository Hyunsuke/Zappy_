/*
** EPITECH PROJECT, 2024
** client.c
** File description:
** main -> client
*/

#include "all.h"

void signal_handler(int signum)
{
    (void)signum;
    full_free();
    exit(EXIT_SUCCESS);
}
