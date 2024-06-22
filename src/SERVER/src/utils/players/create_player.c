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
    new_player->x = rand() % (s->map_width);
    new_player->y = rand() % (s->map_height);
    add_id_to_map_element(&s->map[new_player->y][new_player->x].id_mob,
        &s->map[new_player->y][new_player->x].nb_mob, new_player->id_player);
}

static void add_position_egg_player(struct_t *s, player_t *new_player)
{
    position_t *position = get_and_remove_first_egg_position(s,
        new_player->id_team);

    if (position != NULL) {
        add_id_to_map_element(&s->map[position->y][position->x].id_mob,
            &s->map[position->y][position->x].nb_mob, new_player->id_player);
    } else {
        add_random_position_player(s, new_player);
    }
}

static void add_position_player(struct_t *s, player_t *new_player)
{
    team_t *team_p = get_team_by_id(s, new_player->id_team);

    if (team_p == NULL)
        add_random_position_player(s, new_player);
    else
        add_position_egg_player(s, new_player);
}

static void init_ressource_player(player_t *new_player)
{
    new_player->food = 10;
    new_player->linemate = 0;
    new_player->deraumere = 0;
    new_player->sibur = 0;
    new_player->mendiane = 0;
    new_player->phiras = 0;
    new_player->thystame = 0;
}

static void init_command_player(player_t *new_player)
{
    new_player->command_count = 0;
    new_player->command_start = 0;
    new_player->command_end = 0;
    for (int i = 0; i < MAX_COMMANDS; i++) {
        new_player->commands[i].command = NULL;
        new_player->commands[i].tick = 0;
    }
}

void add_player(struct_t *s, int fd, int id_team)
{
    player_t *new_player = my_malloc(sizeof(player_t));

    srand(time(NULL));
    init_ressource_player(new_player);
    init_command_player(new_player);
    new_player->fd = fd;
    new_player->view_direction = rand() % 4;
    s->next_id_player++;
    new_player->id_player = s->next_id_player;
    new_player->id_team = id_team;
    new_player->x = 0;
    new_player->y = 0;
    new_player->level_player = 1;
    new_player->next = s->head_player;
    new_player->level_player = 1;
    s->head_player = new_player;
    add_position_player(s, new_player);
}
