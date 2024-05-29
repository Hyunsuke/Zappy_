/*
** EPITECH PROJECT, 2024
** struct.h
** File description:
** struct include
*/

#ifndef STRUCT_H
    #define STRUCT_H

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

//////////////////////////////////

typedef struct struct_s {
    int port;
    int map_width;
    int map_height;
    int client_nb;
    int time;
    char **list_names;
    map_element_t **map;
} struct_t;

#endif /* !STRUCT_H */
