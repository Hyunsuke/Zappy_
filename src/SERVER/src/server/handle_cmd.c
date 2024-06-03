/*
** EPITECH PROJECT, 2024
** handle_cmd.c
** File description:
** handle command
*/

#include "all.h"

void gestion_team_name(server_t *server, struct_t *s, char *buffer,
    int client_fd)
{
    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n' && buffer[len - 2] == '\r') {
        buffer[len - 2] = '\0';
    }
    for (int i = 0; s->list_names[i] != NULL; i++) {
        if (strcmp(buffer, s->list_names[i]) == 0) {
            printf("It's AI\n");
            print_response("Server: You're an AI\n", client_fd);
            add_player(s, client_fd, s->id_teams[i]);
            print_players(s);
            server->round[client_fd]++;
            return;
        }
    }
    print_response("Team name that you gave don't exist\n", client_fd);
}

void gestion_cmd(server_t *server, struct_t *s, char *buffer, int client_fd)
{
    if (server->round[client_fd] == 0) {
        if (strcmp(buffer, "GRAPHIC\r\n") == 0) {
            printf("It's GUI\n");
            print_response("Server: You're a GUI\n", client_fd);
            server->round[client_fd]++;
        } else {
            gestion_team_name(server, s, buffer, client_fd);
        }
    } else {
        print_response("Command: ", client_fd);
        print_response(buffer, client_fd);
    }
}

int receive_cmd(server_t *server, struct_t *s, char *buffer, int i)
{
    server->valread = read(i, buffer, 1024 - 1);
    if (server->valread == 0) {
        close(i);
        FD_CLR(i, &server->fd_tab);
        return i;
    } else {
        buffer[server->valread] = '\0';
        printf("-> %s", buffer);
        gestion_cmd(server, s, buffer, i);
        printf("\n");
        return i;
    }
}

void handling_cmd(server_t *server, struct_t *s)
{
    char buffer[1024] = { 0 };

    for (int i = server->server_fd + 1; i <= server->last_cli; i++) {
        if (FD_ISSET(i, &server->tmp_fdtab)) {
            i = receive_cmd(server, s, buffer, i);
        }
    }
}
