/*
** EPITECH PROJECT, 2024
** B4 - Network Programming
** File description:
** commands.c
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "struct.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// TICK //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void new_tick(struct_t *s);


///////////////////////////////////////////////////////////////////////////////
/////////////////////////// COMMANDS IA ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int c_forward(struct_t *s, int fd);
void moove_left(struct_t *s, player_t *mob, int x, int y);
void moove_right(struct_t *s, player_t *mob, int x, int y);
void moove_bottom(struct_t *s, player_t *mob, int x, int y);
void moove_top(struct_t *s, player_t *mob, int x, int y);
int c_right(struct_t *s, int fd);
int c_left(struct_t *s, int fd);
int c_look(struct_t *s, int fd);
void save_elements(struct_t *s, int x, int y);
void add_in_str(struct_t *s, const char *element);
void adjust_new_coor(struct_t *s, player_t *mob, int *x, int *y);
void adjust_first_coor(struct_t *s, player_t *mob, int *x, int *y);
int c_inventory(struct_t *s, int fd);
int c_broadcast_txt(struct_t *s, int fd);
int c_connect_nbr(struct_t *s, int fd);
int c_fork(struct_t *s, int fd);
int c_eject(struct_t *s, int fd);
int c_take_obj(struct_t *s, int fd);
int c_set_obj(struct_t *s, int fd);
int c_incantation(struct_t *s, int fd);
bool start_incantation(struct_t *s, player_t *player);


////// Command functions ////
void print_all_commands(player_t *player);
int add_command(player_t *player, char *command, int tick);
command_t *get_oldest_command(player_t *player);
int get_command_count(player_t *player);
int remove_oldest_command(player_t *player);
int get_tick_for_command(struct_t *s, char *command);
command_t *initialize_command_ticks(void);


///////////////////////////////////////////////////////////////////////////////
/////////////////////////// COMMANDS GUI //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int c_msz(struct_t *s, char *buffer);
int c_bct(struct_t *s, char *buffer);
int c_mct(struct_t *s, char *buffer);
int c_tna(struct_t *s, char *buffer);
int c_ppo(struct_t *s, char *buffer);
int c_ppo_rotate(struct_t *s, int fd_player);
int c_plv(struct_t *s, char *buffer);
int c_pin(struct_t *s, char *buffer);
int c_pin_send(struct_t *s, player_t *player);
int c_sgt(struct_t *s, char *buffer);
int c_sst(struct_t *s, char *buffer);

int c_pnw(struct_t *s, int id_player, int incantation_level);
int c_pex(struct_t *s, int id_player);
int c_pbc(struct_t *s, int id_player, char *name_team);
int c_pic(struct_t *s, position_t position, int level, int *player);
int c_pie(struct_t *s, int x, int y, char *incantation_result);
int c_pfk(struct_t *s, int id_player);
int c_pdr(struct_t *s, int id_player, int id_rsc);
int c_pgt(struct_t *s, int id_player, int id_rsc);
int c_pdi(struct_t *s, int id_player);
int c_enw(struct_t *s, int nb_egg, int nb_player, int *pos);
int c_ebo(struct_t *s, int nb_egg);
int c_edi(struct_t *s, int nb_egg);
int c_seg(struct_t *s, char *name_team);
int c_smg(struct_t *s, char *msg);
int c_suc(struct_t *s);
int c_sbp(struct_t *s);

int run_commands_gui(struct_t *s, int fd, char *buffer);
int run_commands_ia(struct_t *s, int fd, char *buffer);


///////////////////////////////////////////////////////////////////////////////
/////////////////////// STRUCT ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct {
    char *command;
    int (*func)(struct_t *s, char *buffer);
} command_struct_gui_t;

typedef struct {
    char *command;
    int (*func)(struct_t *s, int fd);
} command_struct_ia_t;

#endif /* !COMMANDS_H_ */
