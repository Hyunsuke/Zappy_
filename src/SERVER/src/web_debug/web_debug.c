/*
** EPITECH PROJECT, 2024
** web_debug.c
** File description:
** Function
*/

#include "all.h"

static void initialize_struct_defaults(struct_t *s)
{
    s->obj = "";
    s->look_str = "";
    if (!s->obj)
        s->obj = "";
    if (!s->look_str)
        s->look_str = "";
}

static void add_object_map(json_object *json_cell, map_element_t *cell)
{
    json_object_object_add(json_cell, "food",
        json_object_new_int(cell->food));
    json_object_object_add(json_cell, "linemate",
        json_object_new_int(cell->linemate));
    json_object_object_add(json_cell, "deraumere",
        json_object_new_int(cell->deraumere));
    json_object_object_add(json_cell, "sibur",
        json_object_new_int(cell->sibur));
    json_object_object_add(json_cell, "mendiane",
        json_object_new_int(cell->mendiane));
    json_object_object_add(json_cell, "phiras",
        json_object_new_int(cell->phiras));
    json_object_object_add(json_cell, "thystame",
        json_object_new_int(cell->thystame));
}

static json_object *create_json_map(struct_t *s)
{
    json_object *json_map = json_object_new_array();
    json_object *json_row;
    map_element_t *cell;
    json_object *json_cell;

    for (int i = 0; i < s->map_height; i++) {
        json_row = json_object_new_array();
        for (int j = 0; j < s->map_width; j++) {
            cell = &s->map[i][j];
            json_cell = json_object_new_object();
            add_object_map(json_cell, cell);
            json_object_array_add(json_row, json_cell);
        }
        json_object_array_add(json_map, json_row);
    }
    return json_map;
}

static void add_object_players(json_object *json_player, player_t *player)
{
    json_object_object_add(json_player, "thystame",
        json_object_new_int(player->thystame));
    json_object_object_add(json_player, "fd",
        json_object_new_int(player->fd));
    json_object_object_add(json_player, "id_player",
        json_object_new_int(player->id_player));
    json_object_object_add(json_player, "id_team",
        json_object_new_int(player->id_team));
    json_object_object_add(json_player, "level_player",
        json_object_new_int(player->level_player));
    json_object_object_add(json_player, "view_direction",
        json_object_new_int(player->view_direction));
    json_object_object_add(json_player, "x",
        json_object_new_int(player->x));
    json_object_object_add(json_player, "y",
        json_object_new_int(player->y));
    json_object_object_add(json_player, "mendiane",
        json_object_new_int(player->mendiane));
    json_object_object_add(json_player, "phiras",
        json_object_new_int(player->phiras));
}

static json_object *create_json_players(struct_t *s)
{
    json_object *json_players = json_object_new_array();
    player_t *player = s->head_player;
    json_object *json_player;

    while (player) {
        json_player = json_object_new_object();
        json_object_object_add(json_player, "food",
            json_object_new_int(player->food));
        json_object_object_add(json_player, "linemate",
            json_object_new_int(player->linemate));
        json_object_object_add(json_player, "deraumere",
            json_object_new_int(player->deraumere));
        json_object_object_add(json_player, "sibur",
            json_object_new_int(player->sibur));
        add_object_players(json_player, player);
        json_object_array_add(json_players, json_player);
        player = player->next;
    }
    return json_players;
}

static json_object *create_json_teams(struct_t *s)
{
    json_object *json_teams = json_object_new_array();
    json_object *json_team;
    team_t *team = s->head_team;

    while (team) {
        json_team = json_object_new_object();
        json_object_object_add(json_team, "name",
            json_object_new_string(team->name ? team->name : ""));
        json_object_object_add(json_team, "team_id",
            json_object_new_int(team->team_id));
        json_object_array_add(json_teams, json_team);
        team = team->next;
    }
    return json_teams;
}

static void add_object_utils(json_object *json_utils, struct_t *s)
{
    json_object_object_add(json_utils, "fd_dashboard",
        json_object_new_int(s->fd_dashboard));
    json_object_object_add(json_utils, "obj",
        json_object_new_string(s->obj));
    json_object_object_add(json_utils, "stop_server",
        json_object_new_boolean(s->stop_server));
    json_object_object_add(json_utils, "start_game",
        json_object_new_boolean(s->start_game));
    json_object_object_add(json_utils, "look_str",
        json_object_new_string(s->look_str));
    json_object_object_add(json_utils, "ram_usage",
        json_object_new_double(s->dashboard->ram_usage));
    json_object_object_add(json_utils, "cpu_usage",
        json_object_new_double(s->dashboard->cpu_usage));
}

static json_object *create_json_utils(struct_t *s)
{
    json_object *json_utils = json_object_new_object();

    json_object_object_add(json_utils, "port",
        json_object_new_int(s->port));
    json_object_object_add(json_utils, "map_width",
        json_object_new_int(s->map_width));
    json_object_object_add(json_utils, "map_height",
        json_object_new_int(s->map_height));
    json_object_object_add(json_utils, "client_nb",
        json_object_new_int(s->client_nb));
    json_object_object_add(json_utils, "time",
        json_object_new_int(s->time));
    json_object_object_add(json_utils, "fd_gui",
        json_object_new_int(s->fd_gui));
    add_object_utils(json_utils, s);
    return json_utils;
}

void send_info_web_debug(struct_t *s)
{
    json_object *json_root;
    const char *json_str;
    time_t curre_time = time(NULL);

    if (s->fd_dashboard == -1 || difftime(curre_time, s->dashboard->clock) < 1)
        return;
    s->dashboard->clock = curre_time;
    get_usage(s);
    initialize_struct_defaults(s);
    json_root = json_object_new_object();
    json_object_object_add(json_root, "map", create_json_map(s));
    json_object_object_add(json_root, "players", create_json_players(s));
    json_object_object_add(json_root, "teams", create_json_teams(s));
    json_object_object_add(json_root, "utils", create_json_utils(s));
    json_str = json_object_to_json_string(json_root);
    write(s->fd_dashboard, json_str, strlen(json_str));
    json_object_put(json_root);
}
