/*
** EPITECH PROJECT, 2024
** B4 - Network Programming
** File description:
** UTILS
*/

#ifndef UTILS_H_
    #define UTILS_H_

///////////////////////////////////////////////////////////////////////////////
///////////////////////  LIB  /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

    #include <fcntl.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <ncurses.h>
    #include <signal.h>
    #include <ctype.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <string.h>
    #include <time.h>
    #include <stdbool.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <stdbool.h>
    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <errno.h>
    #include <math.h>

    #include "struct.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////  UTILS  ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

    //////////////////////// PLAYERS ///
void add_player(struct_t *s, int fd, int id_team);
player_t *get_player_by_fd(struct_t *s, int fd);
player_t *get_player_by_id(struct_t *s, int id_player);
void print_players(struct_t *s);
void remove_player(struct_t *s, int fd);
    /////////////////////////////////

    //////////////////////// TEAMS ///
int add_player_to_team(struct_t *s, int team_id, int player_id, int fd);
int remove_player_from_team(struct_t *s, int team_id, int player_id);
team_t *create_team(struct_t *s, const char *name);
int add_position_egg_to_team(struct_t *s, int team_id, int x, int y);
position_t *get_and_remove_first_egg_position(struct_t *s, int team_id);
team_t *get_team_by_id(struct_t *s, int team_id);
team_t *get_team_by_name(struct_t *s, const char *name);
    /////////////////////////////////

void init_struct(struct_t *s);
void signal_handler(int signum);

char **split_buffer(const char *buffer, int *count);

void define_orientation(player_t *mob, int *orientation);

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// STRUCT GORBAGE COLLECTOR //////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct GCNode_t {
    void *pointer;
    struct GCNode_t *next;
} GCNode_t;

typedef struct {
    GCNode_t *head;
} garbage_collector_t;


    //////////////////////// MY_MALLOC and MY_FREE ///
void *my_malloc(size_t size);
void full_free(void);
void my_free(void *ptr);
void *my_realloc(void *ptr, size_t size);
char *my_strdup(const char *str);
    /////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
///////////////////////  COLOR  ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

    // Color:
    #define CDEF  "\x1B[0m"

    #define CBLD  "\x1B[1m"
    #define CFNT  "\x1B[2m"
    #define CITA  "\x1B[3m"
    #define CUND  "\x1B[4m"
    #define CINV  "\x1B[7m"
    #define CTGH  "\x1B[9m"
    #define CBLK  "\x1B[30m"
    #define CRED  "\x1B[31m"
    #define CGRN  "\x1B[32m"
    #define CYEL  "\x1B[33m"
    #define CBLU  "\x1B[34m"
    #define CMAG  "\x1B[35m"
    #define CCYN  "\x1B[36m"
    #define CWHT  "\x1B[37m"

#endif /* !UTILS_H_ */
