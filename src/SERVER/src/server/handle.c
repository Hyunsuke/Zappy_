/*
** EPITECH PROJECT, 2024
** handle.c
** File description:
** handle new client + activity
*/

#include "all.h"

void handle_activity(server_t *server)
{
    struct timeval timeout = {0, 0};

    server->activity = select(server->last_cli + 1,
        &server->tmp_fdtab, NULL, NULL, &timeout);
    if ((server->activity < 0) && (errno != EINTR)) {
        perror("select error");
        full_free();
        exit(84);
    }
}

void handle_new_client(server_t *server)
{
    int new_socket;

    if (FD_ISSET(server->server_fd, &server->tmp_fdtab)) {
        new_socket = accept(server->server_fd,
            (struct sockaddr *) &server->serv_adr, &server->addrlen);
        if (new_socket < 0) {
            perror("accept");
            full_free();
            exit(84);
        }
        dprintf(new_socket, "WELCOME\n");
        FD_SET(new_socket, &server->fd_tab);
        if (new_socket > server->last_cli)
            server->last_cli = new_socket;
        server->round[new_socket] = 0;
    }
}
