/*
** EPITECH PROJECT, 2024
** pic.c
** File description:
** Function pic
*/

#include "all.h"

int c_pic(position_t position, int level, int *player)
{
    printf("pic %d %d %d", position.x, position.y, level);
    for (int n = 0; player[n] != -1; n++)
        printf(" #%d", player[n]);
    printf("\n");
    return 0;
}
