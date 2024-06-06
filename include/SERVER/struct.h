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

typedef struct player_s player_t;
typedef struct position_s position_t;
typedef struct team_s team_t;

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
} player_t;

typedef struct team_s {
    char name[254];
    int team_id;
    int *players_id;
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
    int *id_mob;
} map_element_t;

typedef struct position_s {
    int x;
    int y;
} position_t;


////////////////////////////////////
////// ALL ////////////////////////
//////////////////////////////////

typedef struct struct_s {
    int port;
    int map_width;
    int map_height;
    int client_nb;
    int time;
    int fd_gui;
    map_element_t **map;
    player_t *head_player;
    int next_id_player; // For incrementation id_player
    team_t *head_team;
    int next_id_team; // For incrementation id_team
} struct_t;


#endif /* !STRUCT_H */
