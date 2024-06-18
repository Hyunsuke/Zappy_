/*
** EPITECH PROJECT, 2024
** broadcast.c
** File description:
** Function broadcast
*/

#include "all.h"

int get_direct_from_angle(double angle) {
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

double calculate_angle(int x1, int y1, int x2, int y2) {
    double deltaY = y2 - y1;
    double deltaX = x2 - x1;
    double angle = atan2(deltaY, deltaX) * 180 / M_PI;
    if (angle < 0) {
        angle += 360;
    }
    return angle;
}

int adjust_direction_for_view(int direction, int view_direction) {
    int adjusted_direction = direction - view_direction * 2;
    if (adjusted_direction < 1) {
        adjusted_direction += 8;
    }
    return adjusted_direction;
}

void send_to_all_players(struct_t *s, int fd)
{
    player_t *receiver = s->head_player;
    player_t *sender = get_player_by_fd(s, fd);

    while (receiver != NULL) {
        if (receiver != sender) {
            double angle = calculate_angle(sender->x, sender->y, receiver->x, receiver->y);
            int direction = get_direct_from_angle(angle);
            int adjusted_direction = adjust_direction_for_view(direction, receiver->view_direction);
            dprintf(receiver->fd, "Message reçu de la direction %d: %s\n", adjusted_direction, s->obj);
        }
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
