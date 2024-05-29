/*
** EPITECH PROJECT, 2024
** handle_cmd.c
** File description:
** handle command
*/

#include "all.h"

void gestion_cmd(char *buffer, int client_fd)
{
    print_response(buffer, client_fd);
}

int receive_cmd(server_t *server, char *buffer, int i)
{
    server->valread = read(i, buffer, 1024 - 1);
    if (server->valread == 0) {
        close(i);
        FD_CLR(i, &server->fd_tab);
        return i;
    } else {
        buffer[server->valread] = '\0';
        printf("-> %s", buffer);
        gestion_cmd(buffer, i);
        printf("\n");
        return i;
    }
}

void handling_cmd(server_t *server)
{
    char buffer[1024] = { 0 };

    for (int i = server->server_fd + 1; i <= server->last_cli; i++) {
        if (FD_ISSET(i, &server->tmp_fdtab)) {
            i = receive_cmd(server, buffer, i);
        }
    }
}
