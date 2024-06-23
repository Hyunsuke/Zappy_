/*
** EPITECH PROJECT, 2024
** handle_cmd.c
** File description:
** handle command
*/

#include "all.h"

static void add_multiple_command(void *s, int client_fd, const char *buffer)
{
    int count = 0;
    char **buffers = split_buffer(buffer, &count);
    void *player = get_player_by_fd(s, client_fd);

    printf("Add command: %s\n", buffer);
    for (int i = 0; i < count; i++) {
        add_command(player, buffers[i], get_tick_for_command(s, buffers[i]));
        my_free(buffers[i]);
    }
    my_free(buffers);
}

static void gestion_function(struct_t *s, char *buffer, int client_fd)
{
    if (client_fd == s->fd_gui && s->fd_gui != -1)
        run_commands_gui(s, client_fd, buffer);
    else if (s->fd_dashboard == client_fd)
        c_sst(s, buffer);
    else
        add_multiple_command(s, client_fd, buffer);
}

static void list_actions(server_t *server, struct_t *s, int client_fd,
    team_t *team)
{
    player_t *mob;

    add_player(s, client_fd, team->team_id);
    mob = get_player_by_fd(s, client_fd);
    if (add_player_to_team(s, team->team_id, mob->id_player,
        client_fd) == -1) {
        printf("Error not enough slot in the requested team\n");
        close(client_fd);
        FD_CLR(client_fd, &server->fd_tab);
        return;
    }
    print_players(s);
    server->round[client_fd]++;
    if (s->fd_gui != -1) {
        c_pnw(s, mob->id_player, mob->level_player);
        c_pin_send(s, mob);
        dprintf(s->fd_gui,
            "plv %d %d\n", mob->id_player, mob->level_player);
    }
}

static bool sanitize_buffer(char *buffer)
{
    size_t len = strlen(buffer);

    if (len > 1 && buffer[len - 1] == '\n' && buffer[len - 2] == '\r') {
        buffer[len - 2] = '\0';
        buffer[len - 1] = '\0';
    }
    if (strlen(buffer) == 0) {
        dprintf(2, "Buffer is empty after processing\n");
        return false;
    }
    return true;
}

static void gestion_team_name(server_t *server, struct_t *s, char *buffer,
    int client_fd)
{
    team_t *team = NULL;
    char *team_name;

    if (!sanitize_buffer(buffer))
        return;
    team_name = strtok(buffer, "\n");
    if (team_name == NULL) {
        dprintf(2, "No team name provided\n");
        return;
    }
    team = get_team_by_name(s, team_name);
    if (team == NULL) {
        dprintf(2, "Team name unknown: %s\n", team_name);
        return;
    }
    list_actions(server, s, client_fd, team);
}

static void send_info_gui(struct_t *s)
{
    player_t *current = s->head_player;

    printf("It's GUI\n");
    if (s->fd_gui != -1)
        dprintf(s->fd_gui, "Server: You're a GUI\n");
    c_msz(s, "");
    c_sgt(s, "");
    c_mct(s, "");
    c_tna(s, "");
    while (current != NULL) {
        c_pnw(s, current->id_player, current->level_player);
        c_pin_send(s, current);
        dprintf(s->fd_gui,
            "plv %d %d\n", current->id_player, current->level_player);
        current = current->next;
    }
}

static void gestion_cmd(server_t *server, struct_t *s, char *buffer,
    int client_fd)
{
    if (server->round[client_fd] == 0) {
        if (strcmp(buffer, "GRAPHIC\n") == 0) {
            s->fd_gui = client_fd;
            send_info_gui(s);
            server->round[client_fd]++;
            return;
        }
        if (strcmp(buffer, "DASHBOARD\n") == 0) {
            s->fd_dashboard = client_fd;
            return;
        }
        if (client_fd == s->fd_dashboard) {
            c_sst_dashboard(s, buffer);
        } else {
            gestion_team_name(server, s, buffer, client_fd);
        }
    } else {
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
        gestion_cmd(server, s, buffer, i);
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
