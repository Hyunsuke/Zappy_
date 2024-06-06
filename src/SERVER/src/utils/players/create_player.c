/*
** EPITECH PROJECT, 2024
** create_player.c
** File description:
** create
*/

#include "all.h"

static void add_random_position_player(struct_t *s, player_t *new_player)
{
    srand(time(NULL));
    new_player->x = rand() % (s->map_width + 1);
    new_player->y = rand() % (s->map_height + 1);
    add_id_to_map_element(&s->map[new_player->x][new_player->y],
        new_player->id_player);
}

static void add_position_egg_player(struct_t *s, player_t *new_player)
{
    position_t *position = get_and_remove_first_egg_position(s,
        new_player->id_team);

    if (position != NULL) {
        add_id_to_map_element(&s->map[position->x][position->y],
            new_player->id_player);
    } else {
        add_random_position_player(s, new_player);
    }
}

static void add_position_player(struct_t *s, player_t *new_player)
{
    team_t *team_p = get_team_by_id(s, new_player->id_team);

    if (team_p == NULL) {
        add_random_position_player(s, new_player);
    } else {
        add_position_egg_player(s, new_player);
    }
}

void add_player(struct_t *s, int fd, int id_team)
{
    player_t *new_player = my_malloc(sizeof(player_t));

    new_player->food = 0;
    new_player->linemate = 0;
    new_player->deraumere = 0;
    new_player->sibur = 0;
    new_player->mendiane = 0;
    new_player->phiras = 0;
    new_player->thystame = 0;
    new_player->fd = fd;
    new_player->view_direction = 0;
    s->next_id_player++;
    new_player->id_player = s->next_id_player;
    printf("---> %d\n", id_team);
    new_player->id_team = id_team;
    new_player->x = 0;
    new_player->y = 0;
    new_player->next = s->head_player;
    s->head_player = new_player;
    add_position_player(s, new_player);
}
