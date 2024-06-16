/*
** EPITECH PROJECT, 2024
** look.c
** File description:
** Function look
*/

#include "all.h"

static void moove_hor_ver(struct_t *s, player_t *mob, int *x, int *y)
{
    if (mob->view_direction == 0 || mob->view_direction == 2) {
        if (*x + 1 >= s->map_width)
            *x = 0;
        else
            (*x)++;
    } else {
        if (*y + 1 >= s->map_height)
            *y = 0;
        else
            (*y)++;
    }
}

static void process_cases(struct_t *s, player_t *mob, int *x, int *y)
{
    for (int j = 0; j < s->len_view; j++) {
        save_elements(s, *x, *y);
        moove_hor_ver(s, mob, x, y);
    }
}

static void view_line_loop(struct_t *s, player_t *mob, int *x, int *y)
{
    int save = 0;

    if (mob->view_direction == 0 || mob->view_direction == 2)
        save = *x;
    else
        save = *y;
    for (int i = 0; i < mob->level_player; i++) {
        if (mob->view_direction == 0 || mob->view_direction == 2)
            *x = save;
        else
            *y = save;
        process_cases(s, mob, x, y);
        adjust_new_coor(s, mob, x, y);
        save--;
        s->len_view += 2;
    }
}

static void list_elements(struct_t *s, int fd)
{
    player_t *mob = get_player_by_fd(s, fd);
    int x = mob->x;
    int y = mob->y;

    s->len_view = 3;
    add_in_str(s, "[");
    save_elements(s, x, y);
    adjust_first_coor(s, mob, &x, &y);
    view_line_loop(s, mob, &x, &y);
    add_in_str(s, "]");
    dprintf(fd, "%s\n", s->look_str);
}

int c_look(struct_t *s, int fd)
{
    s->look_str = NULL;
    list_elements(s, fd);
    return 0;
}
