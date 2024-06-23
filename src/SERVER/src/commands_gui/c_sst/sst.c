/*
** EPITECH PROJECT, 2024
** sst.c
** File description:
** Function sst
*/

#include "all.h"

static void parse_sst(const char *input, int *n)
{
    int result;

    *n = 0;
    result = sscanf(input, "sst %d", n);
    if (result < 1)
        *n = -1;
}

int c_sst(struct_t *s, char *buffer)
{
    int unit_time;

    parse_sst(buffer, &unit_time);
    if (unit_time < 0) {
        return -1;
    } else {
        s->time = unit_time;
        dprintf(s->fd_gui, "sst %d\n", s->time);
        printf("New Timer: %d\n", s->time);
    }
    return 0;
}

int c_sst_dashboard(struct_t *s, char *buffer)
{
    int unit_time;

    parse_sst(buffer, &unit_time);
    if (unit_time < 0) {
        return -1;
    } else {
        s->time = unit_time;
        if (s->fd_gui != -1)
            dprintf(s->fd_gui, "sst %d\n", s->time);
    }
    return 0;
}
