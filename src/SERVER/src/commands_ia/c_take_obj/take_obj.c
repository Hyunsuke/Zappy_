/*
** EPITECH PROJECT, 2024
** take_obj.c
** File description:
** Function take_obj
*/

#include "all.h"

static void remove_obj_map(map_element_t *map_element, int id_obj)
{
    switch (id_obj) {
        case 0:
            map_element->food--;
            break;
        case 1:
            map_element->linemate--;
            break;
        case 2:
            map_element->deraumere--;
            break;
        case 3:
            map_element->sibur--;
            break;
        case 4:
            map_element->mendiane--;
            break;
        case 5:
            map_element->phiras--;
            break;
        case 6:
            map_element->thystame--;
            break;
        default:
            printf("Unknown resource: %d\n", id_obj);
            break;
    }
}

static void add_obj_inventory_player(player_t *player, int id_obj)
{
    switch (id_obj) {
        case 0:
            player->food++;
            break;
        case 1:
            player->linemate++;
            break;
        case 2:
            player->deraumere++;
            break;
        case 3:
            player->sibur++;
            break;
        case 4:
            player->mendiane++;
            break;
        case 5:
            player->phiras++;
            break;
        case 6:
            player->thystame++;
            break;
        default:
            printf("Unknown resource: %d\n", id_obj);
            break;
    }
}

int c_take_obj(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    int id_obj = get_resource_code(s->obj);

    remove_obj_map(&s->map[player->y][player->x], id_obj);
    add_obj_inventory_player(player, id_obj);
    return 0;
}
