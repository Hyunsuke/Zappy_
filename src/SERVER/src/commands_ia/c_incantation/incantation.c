/*
** EPITECH PROJECT, 2024
** incantation.c
** File description:
** Function incantation
*/

#include "all.h"

static int get_number_of_players_on_case(struct_t *game_struct, int x, int y)
{
    player_t *current_player = game_struct->head_player;
    int count = 0;

    while (current_player != NULL) {
        if (current_player->x == x && current_player->y == y)
            count++;
        current_player = current_player->next;
    }
    return count;
}

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

int c_incantation(struct_t *s, int fd)
{
    elevation_t *elevation = get_elevation_by_level_to(s, 1);
    player_t *player = get_player_by_fd(s, fd);
    position_t player_position = { .x = player->x, .y = player->y };

    if (check_items_for_incantation(s, elevation, &player_position) == false ||
        get_number_of_players_on_case(s, player_position.x, player_position.y)
            < elevation->nb_players) {
        printf("KO\n");
        return -1;
    }
    // Ajouter function pour compter le temps de l'incantation
    printf("OK\n");
    return 0;
}

// Ajouter function pour pour venir checker si l'incantation est tjr possible
