/*
** EPITECH PROJECT, 2024
** B4 - Network Programming
** File description:
** UTILS
*/

#ifndef MAP_H_
    #define MAP_H_
    #include "struct.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////  MAP  /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//////////// FUNCTIONS //
void add_id_to_map_element(int **id_mob, int *size, int id_player);
void remove_id_from_map_element(int **id_mob, int *size, int id_player);
void remove_all_eggs_at_position_for_all_teams(struct_t *s, int x, int y);
int get_resource_code(char *obj);

void refill_map(struct_t *s);


//////////// STRUCT //

typedef struct map_rsc_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} map_rsc_t;


#endif /* !MAP_H_ */
