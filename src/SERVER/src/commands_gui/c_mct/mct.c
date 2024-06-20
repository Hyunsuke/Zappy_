/*
** EPITECH PROJECT, 2024
** mct.c
** File description:
** Function mct
*/

#include "all.h"

int c_mct(struct_t *s, char *buffer)
{
    map_element_t *element;

    (void)buffer;
    if (s->fd_gui == -1)
        return -1;
    for (int y = 0; y < s->map_height; y++) {
        for (int x = 0; x < s->map_width; x++) {
            element = &s->map[y][x];
            dprintf(s->fd_gui, "bct %d %d %d %d %d %d %d %d %d\n",
                    x, y,
                    element->food,
                    element->linemate,
                    element->deraumere,
                    element->sibur,
                    element->mendiane,
                    element->phiras,
                    element->thystame);
        }
    }
    return 0;
}
