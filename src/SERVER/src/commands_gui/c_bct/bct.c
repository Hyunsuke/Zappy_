/*
** EPITECH PROJECT, 2024
** bct.c
** File description:
** Function bct
*/

#include "all.h"

static void parse_bct(const char *input, int *x, int *y)
{
    int result;

    *x = 0;
    *y = 0;
    result = sscanf(input, "bct %d %d", x, y);
    if (result < 2) {
        *x = 0;
        *y = 0;
    }
}

int c_bct(struct_t *s, char *buffer)
{
    int x;
    int y;
    map_element_t *element;

    if (s->fd_gui == -1)
        return -1;
    parse_bct(buffer, &x, &y);
    if (x < 0 || x >= s->map_width || y < 0 || y >= s->map_height)
        return -1;
    element = &s->map[y][x];
    if (s->fd_gui != -1)
        dprintf(s->fd_gui, "bct %d %d %d %d %d %d %d %d %d\n",
            x, y, element->food, element->linemate, element->deraumere,
            element->sibur, element->mendiane, element->phiras,
            element->thystame);
    return 0;
}
