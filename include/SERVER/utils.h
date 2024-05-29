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

///////////////////////////////////////////////////////////////////////////////
///////////////////////  UTILS  ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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
