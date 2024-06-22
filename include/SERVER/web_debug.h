/*
** EPITECH PROJECT, 2024
** B4 - Network Programming
** File description:
** UTILS
*/

#ifndef DASHBOARD_H_
    #define DASHBOARD_H_
    #include "struct.h"
    #include <json-c/json.h>

///////////////////////////////////////////////////////////////////////////////
///////////////////////  WEB DEBUG  ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void send_info_web_debug(struct_t *s);
int c_sst_dashboard(struct_t *s, char *buffer);
int run_commands_dashboard(struct_t *s, int fd, char *buffer);
void get_usage(struct_t *s);


    #define INITIAL_BUFFER_SIZE 10000


typedef struct buffer_info_s {
    size_t buffer_size;
    size_t remaining_size;
    char *json_buffer;
    char *current_position;
} buffer_info_t;

typedef struct dashboard_s {
    int cpu_usage;
    int ram_usage;
    time_t clock;
} dashboard_t;

typedef struct {
    long user;
    long nice;
    long system;
    long idle;
    long prev_user;
    long prev_nice;
    long prev_system;
    long prev_idle;
} cpu_values_t;

#endif /* !DASHBOARD_H_ */
