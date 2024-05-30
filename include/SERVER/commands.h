/*
** EPITECH PROJECT, 2024
** B4 - Network Programming
** File description:
** UTILS
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "struct.h"


///////////////////////////////////////////////////////////////////////////////
/////////////////////////// COMMANDS IA ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int c_forward (struct_t *s, int fd);
int c_right (struct_t *s, int fd);
int c_left (struct_t *s, int fd);
int c_look (struct_t *s, int fd);
int c_inventory (struct_t *s, int fd);
int c_broadcast_txt (struct_t *s, int fd);
int c_connect_nbr (struct_t *s, int fd);
int c_fork (struct_t *s, int fd);
int c_eject (struct_t *s, int fd);
int c_take_obj (struct_t *s, int fd);
int c_set_obj (struct_t *s, int fd);
int c_incantation (struct_t *s, int fd);


///////////////////////////////////////////////////////////////////////////////
///////////////////////  STRUCT ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


typedef struct {
    char *command;
    int (*func)(struct_t *s, int fd);
} command_struct;


#endif /* !COMMANDS_H_ */
