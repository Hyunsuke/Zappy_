/*
** EPITECH PROJECT, 2024
** tick.c
** File description:
** tick
*/

#include "all.h"

static void decrement_first_command_tick(struct_t *s)
{
    player_t *current_player = s->head_player;
    command_t *command = NULL;

    while (current_player != NULL) {
        command = get_oldest_command(current_player);
        if (command != NULL)
            command->tick--;
        current_player = current_player->next;
    }
}

static void new_tick_for_player(struct_t *s, player_t *current_player)
{
    command_t *command = get_oldest_command(current_player);

    if (command == NULL)
        return;
    print_all_commands(current_player);
    if (command->tick <= 0) {
        run_commands_ia(s, current_player->fd, command->command);
        remove_oldest_command(current_player);
        return;
    }
    if (command->tick == 299) {
        if (start_incantation(s, current_player) == false)
            remove_oldest_command(current_player);
    }
}

void new_tick(struct_t *s)
{
    player_t *current_player = s->head_player;

    decrement_first_command_tick(s);
    while (current_player != NULL) {
        new_tick_for_player(s, current_player);
        current_player = current_player->next;
    }
}
