/*
** EPITECH PROJECT, 2024
** broadcast.c
** File description:
** Function broadcast
*/

#include "all.h"

int get_sound_from_angle(double angle)
{
    if (angle >= 292.5 && angle < 337.5)
        return 2;
    if (angle >= 247.5 && angle < 292.5)
        return 3;
    if (angle >= 202.5 && angle < 247.5)
        return 4;
    if (angle >= 157.5 && angle < 202.5)
        return 5;
    if (angle >= 112.5 && angle < 157.5)
        return 6;
    if (angle >= 67.5 && angle < 112.5)
        return 7;
    if (angle >= 22.5 && angle < 67.5)
        return 8;
    return 1;
}

static double define_angle(int *part, double orientation1)
{
    double angle;

    angle = atan2(part[1], part[0]) * (180 / M_PI);
    angle += 90;
    if (angle < 0)
        angle += 360;
    angle -= orientation1;
    if (angle < 0)
        angle += 360;
    return angle;
}

static double find_angle(struct_t *s, player_t *sender, player_t *receiver,
    double orientation1)
{
    double angle;
    int inter_x = sender->x - receiver->x;
    int inter_y = sender->y - receiver->y;
    int *part = my_malloc(sizeof(int) * 2);

    if (abs(inter_x) > s->map_width / 2) {
        part[0] = inter_x - (s->map_width * (inter_x / abs(inter_x)));
    } else {
        part[0] = inter_x;
    }
    if (abs(inter_y) > s->map_height / 2) {
        part[1] = inter_y - (s->map_height * (inter_y / abs(inter_y)));
    } else {
        part[1] = inter_y;
    }
    angle = define_angle(part, orientation1);
    return angle;
}

static int rec_place(struct_t *s, player_t *receiver, player_t *sender)
{
    int place = 0;
    double orientation = 0.00;

    if (receiver->x == sender->x && receiver->y == sender->y) {
        place = 0;
    } else {
        if (receiver->view_direction == 0)
            orientation = 0.00;
        if (receiver->view_direction == 1)
            orientation = 90.00;
        if (receiver->view_direction == 2)
            orientation = 180.00;
        if (receiver->view_direction == 3)
            orientation = 270.00;
        place = get_sound_from_angle(find_angle(s, sender, receiver,
        orientation));
    }
    return place;
}

static void send_to_all_players(struct_t *s, int fd)
{
    player_t *receiver = s->head_player;
    player_t *sender = get_player_by_fd(s, fd);
    int nb = 0;

    while (receiver != NULL) {
        if (receiver != sender) {
            nb = rec_place(s, receiver, sender);
            dprintf(receiver->fd, "message %d, %s\n", nb, s->obj);
        }
        receiver = receiver->next;
    }
    if (s->fd_gui != -1)
        dprintf(s->fd_gui, "pbc %d %s\n", sender->id_player, s->obj);
}

int c_broadcast_txt(struct_t *s, int fd)
{
    for (int i = 0; s->obj[i] != '\0'; i++) {
        if (s->obj[i] == ' ') {
            dprintf(fd, "ko\n");
            return 84;
        }
    }
    send_to_all_players(s, fd);
    dprintf(fd, "ok\n");
    return 0;
}
