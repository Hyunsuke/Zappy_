
/*
** EPITECH PROJECT, 2024
** struct.h
** File description:
** struct include
*/

#ifndef STRUCT_H
    #define STRUCT_H

////////////////////////////////////
////// PLAYERS ////////////////////
//////////////////////////////////

    typedef struct player_s player_t;

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


////////////////////////////////////
////// MAP ////////////////////////
//////////////////////////////////

    typedef struct map_element_s {
        bool food;
        bool linemate;
        bool deraumere;
        bool sibur;
        bool mendiane;
        bool phiras;
        bool thystame;
        int *id_mob;
    } map_element_t;


////////////////////////////////////
////// ALL ////////////////////////
//////////////////////////////////

    typedef struct struct_s {
        int port;
        int map_width;
        int map_height;
        int client_nb;
        int time;
        int *id_teams;
        char **list_names;
        int fd_gui;
        map_element_t **map;
        player_t *head_player;
        int next_id; // For incrementation id_player
    } struct_t;


#endif /* !STRUCT_H */
