/*
** EPITECH PROJECT, 2024
** struct.h
** File description:
** struct include
*/

#ifndef STRUCT_H
    #define STRUCT_H

////////////////////////////////////
////// PLAYERS && TEAMS ///////////
//////////////////////////////////

    #define MAX_COMMANDS 10

typedef struct player_s player_t;
typedef struct position_s position_t;
typedef struct team_s team_t;
typedef struct incantation_s incantation_t;

typedef struct command_s {
    char *command;
    int tick;
} command_t;

typedef struct player_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int fd;
    int id_player;
    int id_team;
    int level_player;
    int view_direction; // 0 = top; 1 = right; 2 = bottom; 3 = left
    int x;
    int y;
    player_t *next;
    command_t commands[MAX_COMMANDS];
    int command_count;
    int command_start;
    int command_end;
} player_t;

typedef struct team_s {
    char *name;
    int team_id;
    int *players_id;
    int max_cli;
    position_t **position_egg;
    team_t *next;
} team_t;


////////////////////////////////////
////// MAP ////////////////////////
//////////////////////////////////

typedef struct map_element_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int nb_mob;
    int *id_mob;
} map_element_t;

typedef struct position_s {
    int x;
    int y;
} position_t;


////////////////////////////////////
////// ALL ////////////////////////
//////////////////////////////////

typedef struct elevation_s elevation_t;
typedef struct dashboard_s dashboard_t;

typedef struct struct_s {
    int port;
    int map_width;
    int map_height;
    int client_nb;
    int time;
    int fd_gui;
    int fd_dashboard;
    char *obj;
    bool stop_server;
    bool start_game;
    char *look_str;
    int nb_tick_refill;
    int len_view;
    int view_num;
    map_element_t **map;
    player_t *head_player;
    int next_id_player; // For incrementation id_player
    team_t *head_team;
    int next_id_team; // For incrementation id_team
    elevation_t *head_elevation; // Information about incantation (INFO)
    clock_t clock;  // Time for runner commands
    command_t *command_ticks; // Command with tick (INFO)
    incantation_t *head_progress_incantation; // Incantation in progress
    dashboard_t *dashboard;
} struct_t;


#endif /* !STRUCT_H */
