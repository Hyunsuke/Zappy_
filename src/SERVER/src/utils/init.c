/*
** EPITECH PROJECT, 2024
** init.c
** File description:
** Function
*/

#include "all.h"

void init_struct(struct_t *s)
{
    s->head_player = NULL;
    s->next_id_player = 0;
    s->fd_gui = -1;
}
