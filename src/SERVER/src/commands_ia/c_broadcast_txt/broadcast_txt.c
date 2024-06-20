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

double find_angle(struct_t *s, player_t *sender, player_t *receiver,
    double orientation1)
{
    int vect[2];
    double angle;
    int x_diff = sender->x - receiver->x;
    int y_diff = sender->y - receiver->y;

    vect[0] = (abs(x_diff) > s->map_width / 2) ?
                (x_diff - (s->map_width * (x_diff / abs(x_diff)))) : x_diff;
    vect[1] = (abs(y_diff) > s->map_height / 2) ?
                (y_diff - (s->map_height * (y_diff / abs(y_diff)))) : y_diff;
    angle = atan2(vect[1], vect[0]) * (180 / M_PI);
    angle += 90;
    if (angle < 0)
        angle += 360;
    angle -= orientation1;
    if (angle < 0)
        angle += 360;
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

void send_to_all_players(struct_t *s, int fd)
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
