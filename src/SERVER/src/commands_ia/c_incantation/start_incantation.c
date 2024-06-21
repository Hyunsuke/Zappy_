/*
** EPITECH PROJECT, 2024
** start_incantation.c
** File description:
** Function start incantation
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
    map_element_t *element = &s->map[position->y][position->x];

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
    position_t position)
{
    player_t *current_player = s->head_player;
    int count = 0;

    while (current_player != NULL) {
        if (current_player->x == position.x && current_player->y == position.y
            && current_player->level_player == elevation->level_from)
            count++;
        current_player = current_player->next;
    }
    if (count < elevation->nb_players)
        return false;
    else
        return true;
}

static int collect_player_ids(player_t *current_player,
    position_t *player_position, int level, int *player_ids)
{
    int count = 0;

    while (current_player != NULL) {
        if (current_player->x == player_position->x &&
            current_player->y == player_position->y &&
                current_player->level_player == level) {
            player_ids[count] = current_player->id_player;
            count++;
        }
        current_player = current_player->next;
    }
    player_ids[count] = -1;
    return count;
}

bool start_incantation(struct_t *s, player_t *player)
{
    elevation_t *eleva = get_elevation_by_level_to(s,
        (player->level_player + 1));
    position_t p_pos = { .x = player->x, .y = player->y };
    int *p_id =
        (int *)my_malloc((s->map[p_pos.y][p_pos.x].nb_mob + 1) * sizeof(int));
    int nb = 0;

    if (eleva == NULL ||
        check_items_for_incantation(s, eleva, &p_pos) == false ||
        get_number_of_players_on_case(s, p_pos.x, p_pos.y)
        < eleva->nb_players || check_level_player(s, eleva, p_pos) == false) {
        printf("Start Incantation -> ko\n");
        dprintf(player->fd, "ko\n");
        return false;
    }
    nb = collect_player_ids(s->head_player, &p_pos, eleva->level_from, p_id);
    add_incantation(s, player->fd, p_id, nb);
    dprintf(player->fd, "Elevation underway\n");
    c_pic(s, p_pos, eleva->level_to, p_id);
    return true;
}
