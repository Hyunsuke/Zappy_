/*
** EPITECH PROJECT, 2024
** B4 - Network Programming
** File description:
** commands.c
*/

#ifndef PROGRESS_INCANTATION_H_
    #define PROGRESS_INCANTATION_H_

    #include "struct.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// FUNCTION //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void add_incantation(struct_t *s, int fd, int *player_ids, int num_players);
bool is_player_in_incantation(struct_t *s, int player_id);
incantation_t *get_incantation(struct_t *s, int fd);
void remove_incantation(struct_t *s, int fd);


///////////////////////////////////////////////////////////////////////////////
/////////////////////// STRUCT ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct incantation_s {
    int *player_ids;  // Tableau des IDs des joueurs concernés
    int num_players;  // Nombre de joueurs concernés
    int fd;           // File descriptor du joueur réalisant l'incantation
    position_t *position; // Position Incantation
    struct incantation_s *next;
} incantation_t;

#endif /* !PROGRESS_INCANTATION_H_ */
