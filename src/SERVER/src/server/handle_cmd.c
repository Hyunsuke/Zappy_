/*
** EPITECH PROJECT, 2024
** handle_cmd.c
** File description:
** handle command
*/

#include "all.h"

static void gestion_function(struct_t *s, char *buffer, int client_fd)
{
    if (client_fd == s->fd_gui && s->fd_gui != -1)
        run_commands_gui(s, client_fd, buffer);
    else
        add_command(get_player_by_fd(s, client_fd), buffer,
            get_tick_for_command(s, buffer));
}

static void list_actions(server_t *server, struct_t *s, int client_fd,
    team_t *team)
{
    player_t *mob;

    add_player(s, client_fd, team->team_id);
    mob = get_player_by_fd(s, client_fd);
    if (add_player_to_team(s, team->team_id, mob->id_player,
        client_fd) != -1) {
        print_players(s);
        server->round[client_fd]++;
        return;
    }
    // Remove le player de la liste player
    printf("Error not enough slot in the requested team\n");
}

static void gestion_team_name(server_t *server, struct_t *s, char *buffer,
    int client_fd)
{
    size_t len = strlen(buffer);
    team_t *team = NULL;
    char *team_name;

    if (len > 0 && buffer[len - 1] == '\n' && buffer[len - 2] == '\r')
        buffer[len - 2] = '\0';
    team_name = strtok(buffer, "\r\n");
    team = get_team_by_name(s, team_name);
    if (team == NULL) {
        printf("Name team unknown\n");
        return;
    }
    list_actions(server, s, client_fd, team);
}

static void send_info_gui(struct_t *s)
{
    player_t *current = s->head_player;

    printf("It's GUI\n");
    print_response("Server: You're a GUI\n", s->fd_gui);
    c_msz(s, "");
    c_mct(s, "");
    c_tna(s, "");
    s_sgt(s, "");
    while (current != NULL) {
        dprintf(s->fd_gui, "ppo #%d %d %d %d\n", current->id_player,
            current->x, current->y, current->view_direction);
        current = current->next;
    }
}

static void gestion_cmd(server_t *server, struct_t *s, char *buffer,
    int client_fd)
{
    if (server->round[client_fd] == 0) {
        if (strcmp(buffer, "GRAPHIC\r\n") == 0) {
            s->fd_gui = client_fd;
            send_info_gui(s);
            server->round[client_fd]++;
        } else {
            gestion_team_name(server, s, buffer, client_fd);
        }
    } else {
        print_response(buffer, client_fd);
        gestion_function(s, buffer, client_fd);
    }
}

static int receive_cmd(server_t *server, struct_t *s, char *buffer, int i)
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
        if (FD_ISSET(i, &server->tmp_fdtab))
            i = receive_cmd(server, s, buffer, i);
    }
}
