/*
** EPITECH PROJECT, 2024
** broadcast.c
** File description:
** Function broadcast
*/

#include "all.h"

int c_broadcast_txt(struct_t *s, int fd)
{
    printf("c_broadcast_txt\n");
    for (int i = 0; s->obj[i] != '\0'; i++) {
        if (s->obj[i] == ' ') {
            dprintf(fd, "ko\n");
            return 84;
        }
    }
    dprintf(fd, "ok\n");
    return 0;
}
