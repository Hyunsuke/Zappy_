/*
** EPITECH PROJECT, 2024
** broadcast.c
** File description:
** Function broadcast
*/

#include "all.h"

int get_direct_from_angle(double angle)
{
    if (angle >= 22.5 && angle < 67.5)
        return 8;
    if (angle >= 67.5 && angle < 112.5)
        return 7;
    if (angle >= 112.5 && angle < 157.5)
        return 6;
    if (angle >= 157.5 && angle < 202.5)
        return 5;
    if (angle >= 202.5 && angle < 247.5)
        return 4;
    if (angle >= 247.5 && angle < 292.5)
        return 3;
    if (angle >= 292.5 && angle < 337.5)
        return 2;
    return 1;
}

static double findAngle(struct_t *s, int x1, int y1, int x2, int y2, double orientation1)
{
    int vect[2];
    double angle;
    int x_diff = x1 - x2;
    int y_diff = y1 - y2;

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

void send_to_all_players(struct_t *s, int fd)
{
    player_t *receiver = s->head_player;
    player_t *sender = get_player_by_fd(s, fd);
    int place = 0;
    double orientation = 0.00;

    while (receiver != NULL) {
        if (receiver != sender) {
            if (receiver->x == sender->x && receiver->y == sender->y) {
                place = 0;
            } else {
                if (receiver->view_direction == 0) {
                    orientation = 0.00;
                }
                if (receiver->view_direction == 1) {
                    orientation = 90.00;
                }
                if (receiver->view_direction == 2) {
                    orientation = 180.00;
                }
                if (receiver->view_direction == 3) {
                    orientation = 270.00;
                }
                place = get_direct_from_angle(findAngle(s, sender->x, sender->y, receiver->x, receiver->y, orientation));
            }
            dprintf(receiver->fd, "message %d, %s\n", place, s->obj);
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
