/*
** EPITECH PROJECT, 2024
** pdr.c
** File description:
** Function pdr
*/

#include "all.h"

int c_pdr(struct_t *s, int id_player, int nb_rsc)
{
    dprintf(s->fd_gui, "pdr #%d %d\n", id_player, nb_rsc);
    return 0;
}
