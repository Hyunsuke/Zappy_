/*
** EPITECH PROJECT, 2024
** incantation.c
** File description:
** Function incantation
*/

#include "all.h"

static bool check_items_for_incantation(struct_t *s, elevation_t *elevation,
    position_t *position)
{
    map_element_t *element = &s->map[position->y][position->y];

    if (element->linemate < elevation->resources.linemate)
        return false;
    if (element->deraumere < elevation->resources.deraumere)
        return false;
    if (element->sibur < elevation->resources.sibur)
        return false;
    if (element->mendiane < elevation->resources.mendiane)
        return false;
    if (element->phiras < elevation->resources.phiras)
        return false;
    if (element->thystame < elevation->resources.thystame)
        return false;
    return true;
}

static bool check_level_player(struct_t *s, elevation_t *elevation,
    position_t *position)
{
    player_t *current_player = s->head_player;
    int count = 0;

    while (current_player != NULL) {
        if (current_player->x == position->x &&
            current_player->y == position->y
                && current_player->level_player == elevation->level_from)
            count++;
        current_player = current_player->next;
    }
    if (count < elevation->nb_players)
        return false;
    else
        return true;
}

static void change_level_elevation(struct_t *s, elevation_t *elevation,
    position_t *position)
{
    player_t *current_player = s->head_player;
    int count = 0;

    while (current_player != NULL) {
        if (current_player->x == position->x && current_player->y
            == position->y && current_player->level_player ==
                elevation->level_from && count <= elevation->nb_players) {
                current_player->level_player++;
                count++;
                dprintf(current_player->fd, "Current level: %d\n",
                    current_player->level_player);
            }
        current_player = current_player->next;
    }
}

static bool check_incantation_conditions(struct_t *s, elevation_t *elevation,
    incantation_t *incantation, position_t *position)
{
    printf("Position: %d-%d\n", position->x, position->y);
    if (elevation == NULL)
        return false;
    if (check_items_for_incantation(s, elevation, position) == false) {
        printf("Not enough items for incantation\n");
        return false;
    }
    if (check_level_player(s, elevation, position) == false) {
        printf("Not enough level or number player for incantation\n");
        return false;
    }
    return true;
}

static int print_incantation_ko(struct_t *s, int fd)
{
    printf("Incantation -> KO\n");
    dprintf(fd, "KO\n");
    return -1;
}

int c_incantation(struct_t *s, int fd)
{
    player_t *player = get_player_by_fd(s, fd);
    elevation_t *elevation = get_elevation_by_level_to(s,
        (player->level_player + 1));
    incantation_t *incantation = get_incantation(s, fd);
    position_t *pos_incant;

    if (incantation == NULL)
        return print_incantation_ko(s, fd);
    else
        pos_incant = &incantation->position;
    if (!check_incantation_conditions(s, elevation, incantation, pos_incant)) {
        remove_incantation(s, fd);
        return print_incantation_ko(s, fd);
    }
    change_level_elevation(s, elevation, pos_incant);
    printf("Incantation -> OK\n");
    remove_incantation(s, fd);
    return 0;
}
