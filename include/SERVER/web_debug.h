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

#define INITIAL_BUFFER_SIZE 10000

typedef struct buffer_info_s {
    size_t buffer_size;
    size_t remaining_size;
    char *json_buffer;
    char *current_position;
} buffer_info_t;

#endif /* !DASHBOARD_H_ */
