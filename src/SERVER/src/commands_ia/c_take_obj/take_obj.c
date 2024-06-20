/*
** EPITECH PROJECT, 2024
** take_obj.c
** File description:
** Function take_obj
*/

#include "all.h"

static bool remove_take_obj(map_element_t *map_element, int id_obj)
{
    if (id_obj == 4 && map_element->mendiane > 0) {
        map_element->mendiane--;
        return true;
    }
    if (id_obj == 5 && map_element->phiras > 0) {
        map_element->phiras--;
        return true;
    }
    if (id_obj == 6 && map_element->thystame > 0) {
        map_element->thystame--;
        return true;
    }
    return false;
}

static bool remove_obj_map(map_element_t *map_element, int id_obj)
{
    if (id_obj == 0 && map_element->food > 0) {
        map_element->food--;
        return true;
    }
    if (id_obj == 1 && map_element->linemate > 0) {
        map_element->linemate--;
        return true;
    }
    if (id_obj == 2 && map_element->deraumere > 0) {
        map_element->deraumere--;
        return true;
    }
    if (id_obj == 3 && map_element->sibur > 0) {
        map_element->sibur--;
        return true;
    }
    if (remove_take_obj(map_element, id_obj) == false)
        return false;
    else
        return true;
}

static void take_one_obj(player_t *player, int id_obj)
{
    if (id_obj == 4) {
        player->mendiane++;
        return;
    }
    if (id_obj == 5) {
        player->phiras++;
        return;
    }
    if (id_obj == 6) {
        player->thystame++;
        return;
    }
}

static void add_obj_inventory_player(player_t *player, int id_obj)
{
    if (id_obj == 0) {
        player->food++;
        return;
    }
    if (id_obj == 1) {
        player->linemate++;
        return;
    }
    if (id_obj == 2) {
        player->deraumere++;
        return;
    }
    if (id_obj == 3) {
        player->sibur++;
        return;
    }
    take_one_obj(player, id_obj);
}

int c_take_obj(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    int id_obj = get_resource_code(s->obj);

    if (remove_obj_map(&s->map[player->y][player->x], id_obj) == false) {
        dprintf(fd, "ko\n");
        return -1;
    }
    add_obj_inventory_player(player, id_obj);
    c_pgt(s, player->id_player, id_obj);
    dprintf(fd, "ok\n");
    return 0;
}
