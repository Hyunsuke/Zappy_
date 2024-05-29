/*
** EPITECH PROJECT, 2024
** server.h
** File description:
** server include
*/

#ifndef SERVER_H
#define SERVER_H

typedef struct server_s {
    int server_fd;
    socklen_t addrlen;
    struct sockaddr_in serv_adr;
    fd_set tmp_fdtab;
    fd_set fd_tab;
    int last_cli;
    int activity;
    ssize_t valread;
} server_t;

void server_gestion(server_t *server, struct_t *s);
void server_usage(server_t *server);
void create_and_config_serv(server_t *server, struct_t *s);
void init_fd_table(server_t *server);
void handle_new_client(server_t *server);
void handle_activity(server_t *server);
void handling_cmd(server_t *server);
void print_response(char *buffer, int client_fd);

#endif /* !SERVER_H */
