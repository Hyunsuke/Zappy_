/*
** EPITECH PROJECT, 2024
** set_obj.c
** File description:
** Function set_obj
*/

#include "all.h"

static int remove_one_obj(player_t *player, int id_obj)
{
    if (id_obj == 4 && player->mendiane > 0) {
        player->mendiane--;
        return true;
    }
    if (id_obj == 5 && player->phiras > 0) {
        player->phiras--;
        return true;
    }
    if (id_obj == 6 && player->thystame > 0) {
        player->thystame--;
        return true;
    }
    return false;
}

static int remove_obj_from_player(player_t *player, int id_obj)
{
    if (id_obj == 0 && player->food > 0) {
        player->food--;
        return true;
    }
    if (id_obj == 1 && player->linemate > 0) {
        player->linemate--;
        return true;
    }
    if (id_obj == 2 && player->deraumere > 0) {
        player->deraumere--;
        return true;
    }
    if (id_obj == 3 && player->sibur > 0) {
        player->sibur--;
        return true;
    }
    if (remove_one_obj(player, id_obj) == false)
        return false;
    else
        return true;
}

static void add_one_obj(struct_t *s, int id_obj, int x, int y)
{
    if (id_obj == 4) {
        s->map[y][x].mendiane++;
        return;
    }
    if (id_obj == 5) {
        s->map[y][x].phiras++;
        return;
    }
    if (id_obj == 6) {
        s->map[y][x].thystame++;
        return;
    }
}

static void add_obj_to_map(struct_t *s, player_t *player, int id_obj)
{
    int x = player->x;
    int y = player->y;

    if (id_obj == 0) {
        s->map[y][x].food++;
        return;
    }
    if (id_obj == 1) {
        s->map[y][x].linemate++;
        return;
    }
    if (id_obj == 2) {
        s->map[y][x].deraumere++;
        return;
    }
    if (id_obj == 3) {
        s->map[y][x].sibur++;
        return;
    }
    add_one_obj(s, id_obj, x, y);
}

int c_set_obj(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    int id_obj = get_resource_code(s->obj);

    if (remove_obj_from_player(player, id_obj) == false) {
        dprintf(fd, "ko\n");
        return -1;
    }
    add_obj_to_map(s, player, id_obj);
    c_pdr(s, player->id_player, id_obj);
    dprintf(fd, "ok\n");
    return 0;
}
